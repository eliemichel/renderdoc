#include "webgpu_capture.h"

#include "serialise/serialiser.h"
#include "serialise/rdcfile.h"
#include "serialise/streamio.h"

void WebGPUCapturer::StartFrameCapture(DeviceOwnedWindow devWnd)
{
  RDCLOG("Starting WebGPU capture");
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

  return true;
}

bool WebGPUCapturer::DiscardFrameCapture(DeviceOwnedWindow devWnd)
{
  const uint32_t frameNumber = 0;
  RenderDoc::Inst().FinishCaptureWriting(NULL, frameNumber);
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
