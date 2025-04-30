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
#include "webgpu_capture.h"
#include "generated/webgpu_serialiser.h"
#include "generated/webgpu_macros.h"

#include "hooks/hooks.h"
#include "common/common.h"
#include "core/core.h"

#include "official/webgpu.h"

// TODO(elie): remove that, it's only for debug Bell and Sleep
#include <windows.h>

class WebGPUHook : LibraryHook
{
public:
  void RegisterHooks()
  {
    RDCLOG("Registering WebGPU hooks");

    // TODO(elie): Add cases for other OSes and backends
    LibraryHooks::RegisterLibraryHook("webgpu_dawn.dll", NULL);

    LoadProcs();
    SetupHooks();

    RenderDoc::Inst().AddDeviceFrameCapturer(&webgpuHooks, &webgpuHooks.capturer);
    MessageBeep(MB_OK);
  }

private:
  static WebGPUHook webgpuHooks;

  WebGPUCapturer capturer;

  struct HookedFunctions
  {
#define DECLARE_HOOK(proc) HookedFunction<WGPUProc##proc> proc;
    FOREACH_WEBGPU_PROC(DECLARE_HOOK)
  };
  HookedFunctions hooks;

  // Original WebGPU proc pointers
  struct Procs
  {
#define DECLARE_PROC(proc) WGPUProc##proc wgpu##proc;
    FOREACH_WEBGPU_PROC(DECLARE_PROC)
  };
  Procs procs;

  void SetupHooks()
  {
#define REGISTER_HOOK(proc) \
    hooks.CreateInstance.Register("webgpu_dawn.dll", "wgpu" #proc, wgpu##proc##_hook);

    FOREACH_WEBGPU_PROC(REGISTER_HOOK)
  }

  void LoadProcs() {
    HMODULE hModule = GetModuleHandleA("webgpu_dawn.dll");
#define GET_PROC(proc) \
    procs.wgpu##proc = (WGPUProc##proc)GetProcAddress(hModule, "wgpu" #proc);

    FOREACH_WEBGPU_PROC(GET_PROC)
  }

  private:
  // Hook destinations
  static WGPUInstance wgpuCreateInstance_hook(WGPUInstanceDescriptor const *descriptor) {
    RDCDEBUG("Intercepted 'wgpuCreateInstance'!");
    MessageBeep(MB_OK);

    // Start the capture
    RenderDoc::Inst().StartFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));

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
    RDCDEBUG("Intercepted 'wgpuReleaseInstance'!");

    {
      WriteSerialiser &ser = webgpuHooks.capturer.GetScratchSerialiser();
      ser.SetActionChunk();
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::ProcInstanceRelease);
      size_t instanceId = (size_t)instance;
      SERIALISE_ELEMENT(instanceId);
      webgpuHooks.capturer.AddChunk(scope.Get());
    }

    // End the capture
    RenderDoc::Inst().EndFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));

    webgpuHooks.procs.wgpuInstanceRelease(instance);
  }

  // Auto-generated hooks
  #include "generated/webgpu_hooks.inc.cpp"
};

WebGPUHook WebGPUHook::webgpuHooks;
