/******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 Élie Michel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

#include "webgpu_utils.h"

#include <cassert>
#include <iostream>
#include <vector>

#include <chrono>
#include <thread>

// For GetModuleHandleA and GetProcAddress
#include <windows.h>

std::string toStdStringView(WGPUStringView wgpuStringView)
{
  return wgpuStringView.length == WGPU_STRLEN
             ? std::string(wgpuStringView.data)
             : std::string(wgpuStringView.data, wgpuStringView.length);
}

WGPUStringView toWgpuStringView(std::string stdStringView)
{
  return {stdStringView.data(), stdStringView.size()};
}

WGPUStringView toWgpuStringView(const char *cString)
{
  return {cString, WGPU_STRLEN};
}

void sleepForMilliseconds(unsigned int milliseconds)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void WebGPUProcs::LoadProcs()
{
  // Load all WebGPU procedures from the same backend as the injected application  
  HMODULE hModule = GetModuleHandleA("webgpu_dawn.dll");
  if(!hModule)
  {
    // NB: This should only happen in replay mode
    // TODO(elie): Unhardcode!
    hModule = LoadLibraryA(R"(G:\SourceCode\LearnWebGPU-Code-folded\build-dawn\Debug\webgpu_dawn.dll)");
  }
  
#define GET_PROC(proc) wgpu##proc = (WGPUProc##proc)GetProcAddress(hModule, "wgpu" #proc);

  FOREACH_WEBGPU_PROC(GET_PROC)
}

WGPUAdapter WebGPUProcs::requestAdapterSync(WGPUInstance instance,
                                            WGPURequestAdapterOptions const *options)
{
  // A simple structure holding the local information shared with the
  // onAdapterRequestEnded callback.
  struct UserData
  {
    WGPUAdapter adapter = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

  // Callback called by wgpuInstanceRequestAdapter when the request returns
  // This is a C++ lambda function, but could be any function defined in the
  // global scope. It must be non-capturing (the brackets [] are empty) so
  // that it behaves like a regular C function pointer, which is what
  // wgpuInstanceRequestAdapter expects (WebGPU being a C API). The workaround
  // is to convey what we want to capture through the userdata1 pointer,
  // provided as the last argument of wgpuInstanceRequestAdapter and received
  // by the callback as its last argument.
  auto onAdapterRequestEnded = [](WGPURequestAdapterStatus status, WGPUAdapter adapter,
                                  WGPUStringView message, void *userdata1, void * /* userdata2 */
                               ) {
    UserData &userData = *reinterpret_cast<UserData *>(userdata1);
    if(status == WGPURequestAdapterStatus_Success)
    {
      userData.adapter = adapter;
    }
    else
    {
      std::cerr << "Error while requesting adapter: " << toStdStringView(message) << std::endl;
    }
    userData.requestEnded = true;
  };

  // Build the callback info
  WGPURequestAdapterCallbackInfo callbackInfo = {/* nextInChain = */ nullptr,
                                                 /* mode = */ WGPUCallbackMode_AllowProcessEvents,
                                                 /* callback = */ onAdapterRequestEnded,
                                                 /* userdata1 = */ &userData,
                                                 /* userdata2 = */ nullptr};

  // Call to the WebGPU request adapter procedure
  wgpuInstanceRequestAdapter(instance, options, callbackInfo);

  // We wait until userData.requestEnded gets true

  // Hand the execution to the WebGPU instance so that it can check for
  // pending async operations, in which case it invokes our callbacks.
  // NB: We test once before the loop not to wait for 200ms in case it is
  // already ready
  wgpuInstanceProcessEvents(instance);

  while(!userData.requestEnded)
  {
    // Waiting for 200 ms to avoid asking too often to process events
    sleepForMilliseconds(200);

    wgpuInstanceProcessEvents(instance);
  }

  return userData.adapter;
}

void WebGPUProcs::inspectAdapter(WGPUAdapter adapter)
{
  WGPULimits supportedLimits = {};
  supportedLimits.nextInChain = nullptr;

  bool success = wgpuAdapterGetLimits(adapter, &supportedLimits) == WGPUStatus_Success;

  if(success)
  {
    std::cout << "Adapter limits:" << std::endl;
    std::cout << " - maxTextureDimension1D: " << supportedLimits.maxTextureDimension1D << std::endl;
    std::cout << " - maxTextureDimension2D: " << supportedLimits.maxTextureDimension2D << std::endl;
    std::cout << " - maxTextureDimension3D: " << supportedLimits.maxTextureDimension3D << std::endl;
    std::cout << " - maxTextureArrayLayers: " << supportedLimits.maxTextureArrayLayers << std::endl;
  }
  // Prepare the struct where features will be listed
  WGPUSupportedFeatures features;

  // Get adapter features. This may allocate memory that we must later free with wgpuSupportedFeaturesFreeMembers()
  wgpuAdapterGetFeatures(adapter, &features);

  std::cout << "Adapter features:" << std::endl;
  std::cout << std::hex;    // Write integers as hexadecimal to ease comparison with webgpu.h literals
  for(size_t i = 0; i < features.featureCount; ++i)
  {
    std::cout << " - 0x" << features.features[i] << std::endl;
  }
  std::cout << std::dec;    // Restore decimal numbers

  // Free the memory that had potentially been allocated by wgpuAdapterGetFeatures()
  wgpuSupportedFeaturesFreeMembers(features);
  // One shall no longer use features beyond this line.
  WGPUAdapterInfo properties;
  properties.nextInChain = nullptr;
  wgpuAdapterGetInfo(adapter, &properties);
  std::cout << "Adapter properties:" << std::endl;
  std::cout << " - vendorID: " << properties.vendorID << std::endl;
  std::cout << " - vendorName: " << toStdStringView(properties.vendor) << std::endl;
  std::cout << " - architecture: " << toStdStringView(properties.architecture) << std::endl;
  std::cout << " - deviceID: " << properties.deviceID << std::endl;
  std::cout << " - name: " << toStdStringView(properties.device) << std::endl;
  std::cout << " - driverDescription: " << toStdStringView(properties.description) << std::endl;
  std::cout << std::hex;
  std::cout << " - adapterType: 0x" << properties.adapterType << std::endl;
  std::cout << " - backendType: 0x" << properties.backendType << std::endl;
  std::cout << std::dec;    // Restore decimal numbers
  wgpuAdapterInfoFreeMembers(properties);
}

WGPUDevice WebGPUProcs::requestDeviceSync(WGPUInstance instance, WGPUAdapter adapter,
                                          WGPUDeviceDescriptor const *descriptor)
{
  struct UserData
  {
    WGPUDevice device = nullptr;
    bool requestEnded = false;
  };
  UserData userData;

  // The callback
  auto onDeviceRequestEnded = [](WGPURequestDeviceStatus status, WGPUDevice device,
                                 WGPUStringView message, void *userdata1, void * /* userdata2 */
                              ) {
    UserData &userData = *reinterpret_cast<UserData *>(userdata1);
    if(status == WGPURequestDeviceStatus_Success)
    {
      userData.device = device;
    }
    else
    {
      std::cerr << "Error while requesting device: " << toStdStringView(message) << std::endl;
    }
    userData.requestEnded = true;
  };

  // Build the callback info
  WGPURequestDeviceCallbackInfo callbackInfo = {/* nextInChain = */ nullptr,
                                                /* mode = */ WGPUCallbackMode_AllowProcessEvents,
                                                /* callback = */ onDeviceRequestEnded,
                                                /* userdata1 = */ &userData,
                                                /* userdata2 = */ nullptr};

  // Call to the WebGPU request adapter procedure
  wgpuAdapterRequestDevice(adapter, descriptor, callbackInfo);

  // Hand the execution to the WebGPU instance until the request ended
  wgpuInstanceProcessEvents(instance);
  while(!userData.requestEnded)
  {
    sleepForMilliseconds(200);
    wgpuInstanceProcessEvents(instance);
  }

  return userData.device;
}

void WebGPUProcs::inspectDevice(WGPUDevice device)
{
  WGPUSupportedFeatures features = WGPU_SUPPORTED_FEATURES_INIT;
  wgpuDeviceGetFeatures(device, &features);
  std::cout << "Device features:" << std::endl;
  std::cout << std::hex;
  for(size_t i = 0; i < features.featureCount; ++i)
  {
    std::cout << " - 0x" << features.features[i] << std::endl;
  }
  std::cout << std::dec;
  wgpuSupportedFeaturesFreeMembers(features);

  WGPULimits limits = WGPU_LIMITS_INIT;
  bool success = wgpuDeviceGetLimits(device, &limits) == WGPUStatus_Success;

  if(success)
  {
    std::cout << "Device limits:" << std::endl;
    std::cout << " - maxTextureDimension1D: " << limits.maxTextureDimension1D << std::endl;
    std::cout << " - maxTextureDimension2D: " << limits.maxTextureDimension2D << std::endl;
    std::cout << " - maxTextureDimension3D: " << limits.maxTextureDimension3D << std::endl;
    std::cout << " - maxTextureArrayLayers: " << limits.maxTextureArrayLayers << std::endl;
    std::cout << " - maxBindGroups: " << limits.maxBindGroups << std::endl;
    std::cout << " - maxBindGroupsPlusVertexBuffers: " << limits.maxBindGroupsPlusVertexBuffers
              << std::endl;
    std::cout << " - maxBindingsPerBindGroup: " << limits.maxBindingsPerBindGroup << std::endl;
    std::cout << " - maxDynamicUniformBuffersPerPipelineLayout: "
              << limits.maxDynamicUniformBuffersPerPipelineLayout << std::endl;
    std::cout << " - maxDynamicStorageBuffersPerPipelineLayout: "
              << limits.maxDynamicStorageBuffersPerPipelineLayout << std::endl;
    std::cout << " - maxSampledTexturesPerShaderStage: " << limits.maxSampledTexturesPerShaderStage
              << std::endl;
    std::cout << " - maxSamplersPerShaderStage: " << limits.maxSamplersPerShaderStage << std::endl;
    std::cout << " - maxStorageBuffersPerShaderStage: " << limits.maxStorageBuffersPerShaderStage
              << std::endl;
    std::cout << " - maxStorageTexturesPerShaderStage: " << limits.maxStorageTexturesPerShaderStage
              << std::endl;
    std::cout << " - maxUniformBuffersPerShaderStage: " << limits.maxUniformBuffersPerShaderStage
              << std::endl;
    std::cout << " - maxUniformBufferBindingSize: " << limits.maxUniformBufferBindingSize
              << std::endl;
    std::cout << " - maxStorageBufferBindingSize: " << limits.maxStorageBufferBindingSize
              << std::endl;
    std::cout << " - minUniformBufferOffsetAlignment: " << limits.minUniformBufferOffsetAlignment
              << std::endl;
    std::cout << " - minStorageBufferOffsetAlignment: " << limits.minStorageBufferOffsetAlignment
              << std::endl;
    std::cout << " - maxVertexBuffers: " << limits.maxVertexBuffers << std::endl;
    std::cout << " - maxBufferSize: " << limits.maxBufferSize << std::endl;
    std::cout << " - maxVertexAttributes: " << limits.maxVertexAttributes << std::endl;
    std::cout << " - maxVertexBufferArrayStride: " << limits.maxVertexBufferArrayStride << std::endl;
    std::cout << " - maxInterStageShaderVariables: " << limits.maxInterStageShaderVariables
              << std::endl;
    std::cout << " - maxColorAttachments: " << limits.maxColorAttachments << std::endl;
    std::cout << " - maxColorAttachmentBytesPerSample: " << limits.maxColorAttachmentBytesPerSample
              << std::endl;
    std::cout << " - maxComputeWorkgroupStorageSize: " << limits.maxComputeWorkgroupStorageSize
              << std::endl;
    std::cout << " - maxComputeInvocationsPerWorkgroup: " << limits.maxComputeInvocationsPerWorkgroup
              << std::endl;
    std::cout << " - maxComputeWorkgroupSizeX: " << limits.maxComputeWorkgroupSizeX << std::endl;
    std::cout << " - maxComputeWorkgroupSizeY: " << limits.maxComputeWorkgroupSizeY << std::endl;
    std::cout << " - maxComputeWorkgroupSizeZ: " << limits.maxComputeWorkgroupSizeZ << std::endl;
    std::cout << " - maxComputeWorkgroupsPerDimension: " << limits.maxComputeWorkgroupsPerDimension
              << std::endl;
    std::cout << " - maxStorageBuffersInVertexStage: " << limits.maxStorageBuffersInVertexStage
              << std::endl;
    std::cout << " - maxStorageTexturesInVertexStage: " << limits.maxStorageTexturesInVertexStage
              << std::endl;
    std::cout << " - maxStorageBuffersInFragmentStage: " << limits.maxStorageBuffersInFragmentStage
              << std::endl;
    std::cout << " - maxStorageTexturesInFragmentStage: " << limits.maxStorageTexturesInFragmentStage
              << std::endl;
  }
}
