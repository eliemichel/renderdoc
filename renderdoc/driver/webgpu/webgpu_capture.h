#pragma once

#include "core/core.h"

class WebGPUCapturer : public IFrameCapturer
{
public:
  RDCDriver GetFrameCaptureDriver() override { return GetDriverType(); }

  void StartFrameCapture(DeviceOwnedWindow devWnd) override;

  bool EndFrameCapture(DeviceOwnedWindow devWnd) override;

  bool DiscardFrameCapture(DeviceOwnedWindow devWnd) override;

private:
  static RDCDriver GetDriverType() { return RDCDriver::Custom0; }
};

// TODO(elie): Make sth useful out of this (used only for testing RDC deserialization for now)
struct WebGPUInitParams
{
  uint32_t Test = 0;

  // check if a frame capture section version is supported
  static const uint64_t CurrentVersion = 0x01;
};

DECLARE_REFLECTION_STRUCT(WebGPUInitParams);
