#include "webgpu_hooks.h"

#include "hooks/hooks.h"
#include "common/common.h"
#include "core/core.h"

#include "serialise/rdcfile.h"
#include "serialise/streamio.h"

#include "official/webgpu.h"

// TODO(elie): remove that, it's only for debug Bell and Sleep
#include <windows.h>

class WebGPUCapturer : public IFrameCapturer
{
public:
  RDCDriver GetFrameCaptureDriver() override { return GetDriverType(); }

  void StartFrameCapture(DeviceOwnedWindow devWnd) override {
    RDCLOG("Starting WebGPU capture");
    MessageBeep(MB_OK);
  }

  bool EndFrameCapture(DeviceOwnedWindow devWnd) override
  {
    RDCLOG("Ending WebGPU capture");
    const uint32_t frameNumber = 0;
    RenderDoc::FramePixels pixels;
    RDCFile *rdc = RenderDoc::Inst().CreateRDC(GetDriverType(), frameNumber, pixels);

    StreamWriter *captureWriter = NULL;

    if(rdc)
    {
      SectionProperties props;

      // Compress with LZ4 so that it's fast
      props.name = "WebGPU Capture";
      props.flags = SectionFlags::LZ4Compressed;
      props.version = 0;
      props.type = SectionType::FrameCapture;

      captureWriter = rdc->WriteSection(props);
    }
    else
    {
      captureWriter = new StreamWriter(StreamWriter::InvalidStream);
    }

    RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 0.0);
    Sleep(1000);
    RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 0.5);
    Sleep(1000);
    RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 1.0);

    RenderDoc::Inst().FinishCaptureWriting(rdc, frameNumber);

    return true;
  }

  bool DiscardFrameCapture(DeviceOwnedWindow devWnd) override {
    const uint32_t frameNumber = 0;
    RenderDoc::Inst().FinishCaptureWriting(NULL, frameNumber);
    return true;
  }

private:
  static RDCDriver GetDriverType() { return RDCDriver::Custom0; }
};

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

    // Start the capture
    RenderDoc::Inst().StartFrameCapture(DeviceOwnedWindow(&webgpuHooks, NULL));

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
