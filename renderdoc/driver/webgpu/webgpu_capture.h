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

#include "webgpu_macros.h"

#include "core/core.h"
#include "serialise/serialiser.h"

class WebGPUResourceManager;

/**
 * The capturer runs in the injected process. As soon as it is injected, it
 * starts tracking down resources that we may need to capture
 * (see m_ResourceManager), and when a frame capture ends, it serializes it
 * into an RDC file.
 */
class WebGPUCapturer : public IFrameCapturer
{
public:
  WebGPUCapturer();
  ~WebGPUCapturer();

  // Disable copy
  WebGPUCapturer(WebGPUCapturer &) = delete;
  WebGPUCapturer& operator=(WebGPUCapturer &) = delete;

public:    // IFrameCapturer interface
  RDCDriver GetFrameCaptureDriver() override { return GetDriverType(); }

  void StartFrameCapture(DeviceOwnedWindow devWnd) override;

  bool EndFrameCapture(DeviceOwnedWindow devWnd) override;

  bool DiscardFrameCapture(DeviceOwnedWindow devWnd) override;

public:    // API used by hooks to log events
  void AddChunk(Chunk *chunk);

  // Get a serializer that can be used temporarily to create a chunk
  WriteSerialiser &GetScratchSerialiser() { return m_ScratchSerialiser; }

  WebGPUResourceManager *GetResourceManager() { return m_ResourceManager; }

private:
  static RDCDriver GetDriverType() { return RDCDriver::Custom0; }

  // Common cleanup behavior shared between EndFrameCapture and DiscardFrameCapture
  void CleanupAfterFrameCapture();

private:
  // Tracks down resources
  WebGPUResourceManager *m_ResourceManager;

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

/**
 * Information about any event serialized in a WebGPU capture
 */
struct WebGPUEventInfo
{
  uint32_t Test = 0;
};

enum class WebGPUChunk : uint32_t
{
  Init = (uint32_t)SystemChunk::FirstDriverChunk,

  // For each procedure wgpuFoo, we declare a ProcFoo chunk type
#define DECLARE_PROC_CHUNK(proc) Proc##proc,
  FOREACH_WEBGPU_PROC(DECLARE_PROC_CHUNK)
#undef DECLARE_PROC_CHUNK

  // For each resource type WGPUFoo, we declare a ResFoo chunk type
#define DECLARE_RESOURCE_CHUNK(res) Res##res,
      FOREACH_WEBGPU_RESOURCE_TYPE(DECLARE_RESOURCE_CHUNK)
#undef DECLARE_PROC_CHUNK
};

