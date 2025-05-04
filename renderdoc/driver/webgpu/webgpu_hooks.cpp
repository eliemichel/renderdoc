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

#include "webgpu_hooks.h"
#include "webgpu_utils.h"
#include "webgpu_capture.h"
#include "webgpu_manager.h"
#include "webgpu_serialiser.h"
#include "generated/webgpu_macros.h"

#include "hooks/hooks.h"
#include "common/common.h"
#include "core/core.h"

#include "official/webgpu.h"

// TODO(elie): remove that, it's only for debug Bell and Sleep
#include <windows.h>

/**
 * This class is used when injecting into an application to replace the
 * original WebGPU calls with calls to hooks that wrap the original call
 * so that we can log detailed information.
 * 
 * Some specific hooks are manually written, and the remaining ones are
 * automatically generated from WebGPU spec.
 * 
 * This is a singleton which gets automatically registered (as per
 * LibraryHook parent behavior) upon which RegisterHooks() is called.
 * NB: This is called in the injected application's process.
 */
class WebGPUHook : LibraryHook
{
public:
  void RegisterHooks()
  {
    RDCLOG("Registering WebGPU hooks");

    // TODO(elie): Add cases for other OSes and backends
    LibraryHooks::RegisterLibraryHook("webgpu_dawn.dll", NULL);

    procs.LoadProcs();
    SetupHooks();

    // Register the frame capturer
    RenderDoc::Inst().AddDeviceFrameCapturer(&webgpuHooks, &webgpuHooks.capturer);
  }

private:
  // The singleton instance of this class
  static WebGPUHook webgpuHooks;

  // The capturer to log information to when there is an ongoing capture.
  WebGPUCapturer capturer;

  // The index of the current frame, which we need to determine whether the
  // user asked to capture it.
  uint32_t currentFrameNumber = 0;

  // Original WebGPU proc pointers, which we call to issue the original call
  // from within the hooks.
  WebGPUProcs procs;

  // HookedFunction are RenderDoc's abstraction to help injecting our hooks in
  // lieu of the original WebGPU procs.
  struct HookedFunctions
  {
#define DECLARE_HOOK(proc) HookedFunction<WGPUProc##proc> proc;
    FOREACH_WEBGPU_PROC(DECLARE_HOOK)
  };
  HookedFunctions hooks;

  // Replace raw WebGPU procs by our hooks in the injected application
  void SetupHooks()
  {
#define REGISTER_HOOK(proc) \
    hooks.CreateInstance.Register("webgpu_dawn.dll", "wgpu" #proc, wgpu##proc##_hook);

    FOREACH_WEBGPU_PROC(REGISTER_HOOK)
  }

  private:
  // Hook destinations
  static WGPUInstance wgpuCreateInstance_hook(WGPUInstanceDescriptor const *descriptor) {
    RenderDoc::Inst().AddActiveDriver(webgpuHooks.capturer.GetFrameCaptureDriver(), false);

    // Start the capture
    if(RenderDoc::Inst().ShouldTriggerCapture(0) || true) // TODO(elie): remove that debug true and fix the queue capture issue
    {
      MessageBeep(MB_OK);
      RenderDoc::Inst().StartFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));
    }

    // Regular hook behavior
    if(RenderDoc::Inst().IsFrameCapturing())
    {
      WriteSerialiser &ser = webgpuHooks.capturer.GetScratchSerialiser();
      ser.SetActionChunk(); // elie: is this useful?
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::ProcCreateInstance);
      // TODO(elie): move into Serialize_CreateInstance
      SERIALISE_ELEMENT_OPT(descriptor);
      webgpuHooks.capturer.AddChunk(scope.Get());
    }

    return webgpuHooks.procs.wgpuCreateInstance(descriptor);
  }

  static void wgpuInstanceRelease_hook(WGPUInstance instance)
  {
    // Regular hook behavior
    if(RenderDoc::Inst().IsFrameCapturing())
    {
      WriteSerialiser &ser = webgpuHooks.capturer.GetScratchSerialiser();
      ser.SetActionChunk();
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::ProcInstanceRelease);
      size_t instanceId = (size_t)instance;
      SERIALISE_ELEMENT(instanceId);
      webgpuHooks.capturer.AddChunk(scope.Get());
    }

    // End the capture if it was still running
    if(RenderDoc::Inst().IsFrameCapturing())
    {
      RenderDoc::Inst().EndFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));
    }

    webgpuHooks.procs.wgpuInstanceRelease(instance);
  }

  static void wgpuSurfacePresent_hook(WGPUSurface surface)
  {
    // Regular hook behavior
    if(RenderDoc::Inst().IsFrameCapturing())
    {
      WriteSerialiser &ser = webgpuHooks.capturer.GetScratchSerialiser();
      ser.SetActionChunk();
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::ProcSurfacePresent);
      webgpuHooks.capturer.AddChunk(scope.Get());
    }

    RenderDoc::Inst().Tick();
    RenderDoc::Inst().AddActiveDriver(webgpuHooks.capturer.GetFrameCaptureDriver(), true);

    // Stop ongoing capture if there was one
    if(RenderDoc::Inst().IsFrameCapturing())
    {
      RenderDoc::Inst().EndFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));
    }

    // Increment frame number and check whether this new frame must be captured
    ++webgpuHooks.currentFrameNumber;
    if(RenderDoc::Inst().ShouldTriggerCapture(webgpuHooks.currentFrameNumber))
    {
      RenderDoc::Inst().StartFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));
    }

    webgpuHooks.procs.wgpuSurfacePresent(surface);
  }

  static WGPUTexture wgpuDeviceCreateTexture_hook(WGPUDevice device,
                                                  WGPUTextureDescriptor const *descriptor)
  {
    // Regular hook behavior
    if(RenderDoc::Inst().IsFrameCapturing())
    {
      WriteSerialiser &ser = webgpuHooks.capturer.GetScratchSerialiser();
      ser.SetActionChunk();
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::ProcDeviceCreateTexture);
      SERIALISE_ELEMENT(*descriptor);
      webgpuHooks.capturer.AddChunk(scope.Get());
    }

    WGPUTexture texture = webgpuHooks.procs.wgpuDeviceCreateTexture(device, descriptor);

    // Register resource
    ResourceId resourceId = ResourceIDGen::GetNewUniqueID();
    auto* res = webgpuHooks.capturer.GetResourceManager();
    auto* record = res->AddResourceRecord(resourceId);
    {
      WriteSerialiser &ser = webgpuHooks.capturer.GetScratchSerialiser();
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::ResTexture);
      SERIALISE_ELEMENT(resourceId);
      SERIALISE_ELEMENT(*descriptor);
      record->AddChunk(scope.Get());
    }

    if (RenderDoc::Inst().IsFrameCapturing())
    {
      res->MarkResourceFrameReferenced(resourceId, eFrameRef_CompleteWrite);
    }

    return texture;
  }

  // Auto-generated hooks
  #include "generated/webgpu_hooks.inc.cpp"
};

WebGPUHook WebGPUHook::webgpuHooks;
