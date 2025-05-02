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

#pragma once

#include "generated/webgpu_macros.h"

#include "official/webgpu.h"

#include <string>

/**
 * Convert a WebGPU string view into a C++ std::string_view.
 */
std::string toStdStringView(WGPUStringView wgpuStringView);

/**
 * Convert a C++ std::string_view into a WebGPU string view.
 */
WGPUStringView toWgpuStringView(std::string stdStringView);

/**
 * Convert a C string into a WebGPU string view
 */
WGPUStringView toWgpuStringView(const char* cString);

/**
 * Sleep for a given number of milliseconds.
 * This works with both native builds and emscripten, provided that -sASYNCIFY
 * compile option is provided when building with emscripten.
 */
void sleepForMilliseconds(unsigned int milliseconds);

/**
 * Original WebGPU proc pointers, which we call to issue the original call
 * from within the hooks.
 */
struct WebGPUProcs
{
public:
#define DECLARE_PROC(proc) WGPUProc##proc wgpu##proc;
  FOREACH_WEBGPU_PROC(DECLARE_PROC)

public:
  /**
   * Load the procedures from the dll, this must be called before anything else.
   */
  void LoadProcs();

public: // Utility functions that use WebGPU procedures
  /**
   * Utility function to get a WebGPU adapter, so that
   *     WGPUAdapter adapter = requestAdapter(options);
   * is roughly equivalent to
   *     const adapter = await navigator.gpu.requestAdapter(options);
   */
  WGPUAdapter requestAdapterSync(WGPUInstance instance, WGPURequestAdapterOptions const *options);

  /**
   * Utility function to get a WebGPU device, so that
   *     WGPUAdapter device = requestDevice(adapter, options);
   * is roughly equivalent to
   *     const device = await adapter.requestDevice(descriptor);
   * It is very similar to requestAdapter
   */
  WGPUDevice requestDeviceSync(WGPUInstance instance, WGPUAdapter adapter,
                               WGPUDeviceDescriptor const *descriptor);

  /**
   * An example of how we can inspect the capabilities of the hardware through
   * the adapter object.
   */
  void inspectAdapter(WGPUAdapter adapter);
  /**
   * Display information about a device
   */
  void inspectDevice(WGPUDevice device);
};
