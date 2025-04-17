#include "serialise/rdcfile.h"

struct DebugTest
{
  DebugTest()
  {
    {
      RDCFile rdc;

      uint64_t machineIdent = 0;
      RDCThumb *thumb = nullptr;
      uint64_t timeBase = 0;
      double timeFreq = 1.0;

      rdc.SetData(RDCDriver::Custom0, "WebGPU", machineIdent, thumb, timeBase, timeFreq);
      rdc.Create("C:/tmp/test_webgpu.rdc");

      {
        SectionProperties sec;
        sec.name = "capture";
        sec.type = SectionType::FrameCapture;
        rdc.WriteSection(sec);
      }
    }

    {
      RDCFile rdc;
      rdc.Open("C:/tmp/test_webgpu.rdc");

      int idx = rdc.SectionIndex(SectionType::FrameCapture);
      RDCLOG("FrameCapture index: ", idx);
    }
  }
};

static DebugTest s_debugTest;
