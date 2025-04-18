#include "webgpu_hooks.h"

#include "hooks/hooks.h"
#include "common/common.h"

#include "official/webgpu.h"

// TODO(elie): remove that, it's only for debug Bell
#include <windows.h>

class WebGPUHook : LibraryHook
{
public:
  void RegisterHooks()
  {
    RDCLOG("Registering WebGPU hooks");

    // TODO(elie): Add cases for other OSes and backends
    LibraryHooks::RegisterLibraryHook("webgpu_dawn.dll", NULL);

    hooks.CreateInstance.Register("webgpu_dawn.dll", "wgpuCreateInstance", wgpuCreateInstance_hook);
    hooks.InstanceRelease.Register("webgpu_dawn.dll", "wgpuInstanceRelease", wgpuInstanceRelease_hook);

    LoadProcs();
  }

private:
  static WebGPUHook webgpuHooks;

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
    return webgpuHooks.procs.wgpuCreateInstance(descriptor);
  }

  static void wgpuInstanceRelease_hook(WGPUInstance instance)
  {
    RDCDEBUG("Intercepted 'wgpuReleaseInstance'!");
    MessageBeep(MB_OK);
    webgpuHooks.procs.wgpuInstanceRelease(instance);
  }
};

WebGPUHook WebGPUHook::webgpuHooks;
