#include "webgpu_hooks.h"
#include "webgpu_capture.h"

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

    hooks.CreateInstance.Register("webgpu_dawn.dll", "wgpuCreateInstance", wgpuCreateInstance_hook);
    hooks.InstanceRelease.Register("webgpu_dawn.dll", "wgpuInstanceRelease", wgpuInstanceRelease_hook);

    RenderDoc::Inst().AddDeviceFrameCapturer(&webgpuHooks, &webgpuHooks.capturer);
    MessageBeep(MB_OK);
  }

private:
  static WebGPUHook webgpuHooks;

  WebGPUCapturer capturer;

  struct HookedFunctions
  {
    HookedFunction<WGPUProcCreateInstance> CreateInstance;
    HookedFunction<WGPUProcInstanceRelease> InstanceRelease;
  };
  HookedFunctions hooks;

  // Original WebGPU proc pointers
  struct Procs
  {
    WGPUProcCreateInstance wgpuCreateInstance;
    WGPUProcInstanceRelease wgpuInstanceRelease;
  };
  Procs procs;

  void LoadProcs() {
    HMODULE hModule = GetModuleHandleA("webgpu_dawn.dll");
    procs.wgpuCreateInstance = (WGPUProcCreateInstance)GetProcAddress(hModule, "wgpuCreateInstance");
    procs.wgpuInstanceRelease =
        (WGPUProcInstanceRelease)GetProcAddress(hModule, "wgpuInstanceRelease");
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
      SCOPED_SERIALISE_CHUNK(WebGPUChunk::Foo, sizeof(WebGPUInitParams));
      WebGPUInitParams initParams;
      SERIALISE_ELEMENT(initParams);
      // TODO(elie): Add actual info about the call
      webgpuHooks.capturer.AddChunk(scope.Get());
    }

    return webgpuHooks.procs.wgpuCreateInstance(descriptor);
  }

  static void wgpuInstanceRelease_hook(WGPUInstance instance)
  {
    RDCDEBUG("Intercepted 'wgpuReleaseInstance'!");

    // End the capture
    RenderDoc::Inst().EndFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));

    webgpuHooks.procs.wgpuInstanceRelease(instance);
  }
};

WebGPUHook WebGPUHook::webgpuHooks;
