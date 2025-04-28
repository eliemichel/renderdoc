#pragma once

#include "core/core.h"
#include "serialise/serialiser.h"

class WebGPUCapturer : public IFrameCapturer
{
public:    // IFrameCapturer interface
  RDCDriver GetFrameCaptureDriver() override { return GetDriverType(); }

  void StartFrameCapture(DeviceOwnedWindow devWnd) override;

  bool EndFrameCapture(DeviceOwnedWindow devWnd) override;

  bool DiscardFrameCapture(DeviceOwnedWindow devWnd) override;

public:    // API used by hooks to log events
  void AddChunk(Chunk *chunk);

  WriteSerialiser &GetScratchSerialiser() { return m_ScratchSerialiser; }

private:
  static RDCDriver GetDriverType() { return RDCDriver::Custom0; }

private:
  // We accumulate chunks here each time an API hook is invoked
  rdcarray<Chunk*> m_Chunks;

  // Temporary serialiser used to create the chunks that are added to m_Chunks
  WriteSerialiser m_ScratchSerialiser = {new StreamWriter(1024), Ownership::Stream};
};

// TODO(elie): Make sth useful out of this (used only for testing RDC deserialization for now)
struct WebGPUInitParams
{
  uint32_t Test = 0;

  // check if a frame capture section version is supported
  static const uint64_t CurrentVersion = 0x01;
};

DECLARE_REFLECTION_STRUCT(WebGPUInitParams);

enum class WebGPUChunk : uint32_t
{
  CreateInstance = (uint32_t)SystemChunk::FirstDriverChunk,
  InstanceRelease,
};

