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
    props.version = 0x01;    // TODO(elie): Connect with WebGPUInitParams::CurrentVersion
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
  }

  // TODO(elie): Clear this fake progress
  RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 0.0);
  Sleep(1000);
  RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 0.5);
  Sleep(1000);
  RenderDoc::Inst().SetProgress(CaptureProgress::SerialiseFrameContents, 1.0);

  RenderDoc::Inst().FinishCaptureWriting(rdc, frameNumber);

  return true;
}

bool WebGPUCapturer::DiscardFrameCapture(DeviceOwnedWindow devWnd)
{
  const uint32_t frameNumber = 0;
  RenderDoc::Inst().FinishCaptureWriting(NULL, frameNumber);
  return true;
}

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WebGPUInitParams &el)
{
  SERIALISE_MEMBER(Test);
}

INSTANTIATE_SERIALISE_TYPE(WebGPUInitParams);
