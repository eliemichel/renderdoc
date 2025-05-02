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

#include "webgpu_capture.h"

#include "serialise/serialiser.h"
#include "serialise/rdcfile.h"
#include "serialise/streamio.h"

void WebGPUCapturer::StartFrameCapture(DeviceOwnedWindow devWnd)
{
  RDCLOG("Starting WebGPU capture");
  m_Chunks.clear();
}

bool WebGPUCapturer::EndFrameCapture(DeviceOwnedWindow devWnd)
{
  RDCLOG("Ending WebGPU capture");
  MessageBeep(MB_OK);
  const uint32_t frameNumber = 0;    // TODO(elie)
  RenderDoc::FramePixels pixels;     // TODO(elie)
  RDCFile *rdc = RenderDoc::Inst().CreateRDC(GetDriverType(), frameNumber, pixels);

  RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 0.0);

  StreamWriter *captureWriter = NULL;

  if(rdc)
  {
    SectionProperties props;

    // Compress with LZ4 so that it's fast
    props.name = "WebGPU Capture";
    props.flags = SectionFlags::LZ4Compressed;
    props.version = WebGPUInitParams::CurrentVersion;
    props.type = SectionType::FrameCapture;

    captureWriter = rdc->WriteSection(props);
  }
  else
  {
    captureWriter = new StreamWriter(StreamWriter::InvalidStream);
  }

  {
    WriteSerialiser ser(captureWriter, Ownership::Stream);

    {
      SCOPED_SERIALISE_CHUNK(SystemChunk::DriverInit, sizeof(WebGPUInitParams));

      WebGPUInitParams initParams;
      SERIALISE_ELEMENT(initParams);
    }

    size_t tot = m_Chunks.size();
    size_t done = 0;

    for(Chunk *chunk : m_Chunks)
    {
      chunk->Write(ser);

      ++done;
      RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents,
                                    (float)done / (float)tot);
    }
  }

  RenderDoc::Inst().FinishCaptureWriting(rdc, frameNumber);

  m_Chunks.clear();

  return true;
}

bool WebGPUCapturer::DiscardFrameCapture(DeviceOwnedWindow devWnd)
{
  const uint32_t frameNumber = 0;
  RenderDoc::Inst().FinishCaptureWriting(NULL, frameNumber);

  m_Chunks.clear();

  return true;
}

void WebGPUCapturer::AddChunk(Chunk *chunk)
{
  m_Chunks.push_back(chunk);
}

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WebGPUInitParams &el)
{
  SERIALISE_MEMBER(Test);
}

INSTANTIATE_SERIALISE_TYPE(WebGPUInitParams);
