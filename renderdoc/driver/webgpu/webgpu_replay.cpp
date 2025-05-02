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

#include "webgpu_replay.h"
#include "webgpu_capture.h"
#include "generated/webgpu_serialiser.h"

#include "serialise/rdcfile.h"
#include "serialise/serialiser.h"

#include "official/webgpu.h"

RDResult WebGPU_CreateReplayDevice(RDCFile *rdc, const ReplayOptions &opts, IReplayDriver **driver)
{
  RDCLOG("Creating an WebGPU replay device");
  *driver = new WebGPUDriver();
  return ResultCode::Succeeded;
}

static DriverRegistration WebGPUDriverRegistration(RDCDriver::Custom0, &WebGPU_CreateReplayDevice);

WebGPUDriver::WebGPUDriver()
{
  m_DriverInfo.vendor = GPUVendor::Software;

  // TODO(elie): This is mock data
  m_SDFile = new SDFile();
  m_SDFile->chunks.push_back(new SDChunk(rdcinflexiblestr("wgpuCreateInstance")));
}

WebGPUDriver::~WebGPUDriver()
{
  delete m_SDFile;
  m_SDFile = nullptr;
}

void WebGPUDriver::Shutdown()
{
  delete this;
}

APIProperties WebGPUDriver::GetAPIProperties()
{
  return m_Props;
}

rdcarray<ResourceDescription> WebGPUDriver::GetResources()
{
  return m_Resources;
}

rdcarray<DescriptorStoreDescription> WebGPUDriver::GetDescriptorStores()
{
  return m_DescriptorStores;
}

rdcarray<BufferDescription> WebGPUDriver::GetBuffers()
{
  return m_Buffers;
}

BufferDescription WebGPUDriver::GetBuffer(ResourceId id)
{
  for(const BufferDescription &buf : m_Buffers)
  {
    if(buf.resourceId == id)
      return buf;
  }

  return {};
}

rdcarray<TextureDescription> WebGPUDriver::GetTextures()
{
  return m_Textures;
}

TextureDescription WebGPUDriver::GetTexture(ResourceId id)
{
  for(const TextureDescription &tex : m_Textures)
  {
    if(tex.resourceId == id)
      return tex;
  }

  return {};
}

rdcarray<DebugMessage> WebGPUDriver::GetDebugMessages()
{
  return {};
}

rdcarray<ShaderEntryPoint> WebGPUDriver::GetShaderEntryPoints(ResourceId shader)
{
  return {{"main", ShaderStage::Vertex}};
}

ShaderReflection *WebGPUDriver::GetShader(ResourceId pipeline, ResourceId shader,
                                         ShaderEntryPoint entry)
{
  return NULL;
}

rdcarray<rdcstr> WebGPUDriver::GetDisassemblyTargets(bool withPipeline)
{
  return {"Disassembly"};
}

rdcstr WebGPUDriver::DisassembleShader(ResourceId pipeline, const ShaderReflection *refl,
                                      const rdcstr &target)
{
  return "; No disassembly available due to unrecoverable error analysing capture.";
}

rdcarray<EventUsage> WebGPUDriver::GetUsage(ResourceId id)
{
  return {};
}

void WebGPUDriver::SetPipelineStates(D3D11Pipe::State *d3d11, D3D12Pipe::State *d3d12,
                                    GLPipe::State *gl, VKPipe::State *vk)
{
}

void WebGPUDriver::SavePipelineState(uint32_t eventId)
{
}

rdcarray<Descriptor> WebGPUDriver::GetDescriptors(ResourceId descriptorStore,
                                                 const rdcarray<DescriptorRange> &ranges)
{
  size_t count = 0;
  for(const DescriptorRange &r : ranges)
    count += r.count;
  rdcarray<Descriptor> ret;
  ret.resize(count);
  return ret;
}

rdcarray<SamplerDescriptor> WebGPUDriver::GetSamplerDescriptors(ResourceId descriptorStore,
                                                               const rdcarray<DescriptorRange> &ranges)
{
  size_t count = 0;
  for(const DescriptorRange &r : ranges)
    count += r.count;
  rdcarray<SamplerDescriptor> ret;
  ret.resize(count);
  return ret;
}

rdcarray<DescriptorAccess> WebGPUDriver::GetDescriptorAccess(uint32_t eventId)
{
  return {};
}

rdcarray<DescriptorLogicalLocation> WebGPUDriver::GetDescriptorLocations(
    ResourceId descriptorStore, const rdcarray<DescriptorRange> &ranges)
{
  return {};
}

RDResult WebGPUDriver::ReadLogInitialisation(RDCFile *rdc, bool storeStructuredBuffers)
{
  // TODO(elie)
  // ser.ConfigureStructuredExport(&GetChunkName, storeStructuredBuffers, m_TimeBase, m_TimeFrequency);
  // ...
  // (see other implems of ReadLogInitialisation)
  // TODO(elie): use storeStructuredBuffers

  int sectionIdx = rdc->SectionIndex(SectionType::FrameCapture);

  if(sectionIdx < 0)
    RETURN_ERROR_RESULT(ResultCode::FileCorrupted, "File does not contain captured API data");

  uint64_t version = rdc->GetSectionProperties(sectionIdx).version;
  if(version != WebGPUInitParams::CurrentVersion)
  {
    RETURN_ERROR_RESULT(ResultCode::APIIncompatibleVersion,
                        "WebGPU capture is incompatible version %llu, newest supported by this "
                        "build of RenderDoc is %llu",
                        version, WebGPUInitParams::CurrentVersion);
  }

  StreamReader *reader = rdc->ReadSection(sectionIdx);

  ReadSerialiser ser(reader, Ownership::Stream);

  ser.SetVersion(version);

  // TODO(elie): We don't use initParams
  WebGPUInitParams initParams;
  {
    SystemChunk chunk = ser.ReadChunk<SystemChunk>();

    if(chunk != SystemChunk::DriverInit)
    {
      RETURN_ERROR_RESULT(ResultCode::FileCorrupted,
                          "Expected to get a DriverInit chunk, instead got %u", chunk);
    }

    SERIALISE_ELEMENT(initParams);

    ser.EndChunk();
  }

  if(ser.IsErrored())
  {
    return ser.GetError();
  }

  for(;;)
  {
    if(reader->IsErrored() || reader->AtEnd())
      break;

    WebGPUChunk context = ser.ReadChunk<WebGPUChunk>();

    if(reader->IsErrored())
      return RDResult(ResultCode::APIDataCorrupted, ser.GetError().message);

    // TODO(elie): Use 'success'
    bool success = ProcessChunk(ser, context);

    ser.EndChunk();

    if(reader->IsErrored())
      return RDResult(ResultCode::APIDataCorrupted, ser.GetError().message);

    uint64_t offsetEnd = reader->GetOffset();
    RenderDoc::Inst().SetProgress(LoadProgress::FileInitialRead,
                                  float(offsetEnd) / float(reader->GetSize()));

    if((SystemChunk)context == SystemChunk::CaptureScope || reader->IsErrored() || reader->AtEnd())
      break;
  }

  return ResultCode::Succeeded;
}

bool WebGPUDriver::ProcessChunk(ReadSerialiser &ser, WebGPUChunk context)
{
  auto AddMockAction = [this](WebGPUChunk context, rdcstr name) {
    uint32_t actionId =
        m_FrameRecord.actionList.empty() ? 0 : m_FrameRecord.actionList.back().actionId + 1;
    uint32_t firstEventId =
        m_FrameRecord.actionList.empty() ? 0 : m_FrameRecord.actionList.back().eventId + 1;
    ActionDescription action;
    action.customName = name;
    action.actionId = actionId;

    // TODO(elie): Add ActionFlags::Instanced where needed? Or everywhere?
    if(context == WebGPUChunk::ProcCommandEncoderBeginComputePass ||
       context == WebGPUChunk::ProcCommandEncoderBeginRenderPass)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::BeginPass;
    }
    else if(context == WebGPUChunk::ProcCommandEncoderClearBuffer)
    {
      action.flags = ActionFlags::Clear; // TODO(elie): Maybe Clear is only for Color/Depth texture clear?
    }
    else if(context == WebGPUChunk::ProcCommandEncoderCopyBufferToBuffer ||
            context == WebGPUChunk::ProcCommandEncoderCopyBufferToTexture ||
            context == WebGPUChunk::ProcCommandEncoderCopyTextureToBuffer ||
            context == WebGPUChunk::ProcCommandEncoderCopyTextureToTexture ||
            context == WebGPUChunk::ProcCommandEncoderWriteBuffer)
    {
      action.flags = ActionFlags::Copy;
    }
    else if(context == WebGPUChunk::ProcCommandEncoderPushDebugGroup)
    {
      action.flags = ActionFlags::PushMarker;
    }
    else if(context == WebGPUChunk::ProcCommandEncoderPopDebugGroup)
    {
      action.flags = ActionFlags::PopMarker;
    }
    else if(context == WebGPUChunk::ProcCommandEncoderResolveQuerySet)
    {
      action.flags = ActionFlags::Resolve;
    }
    else if(context == WebGPUChunk::ProcComputePassEncoderDispatchWorkgroups)
    {
      action.flags = ActionFlags::Dispatch;
    }
    else if(context == WebGPUChunk::ProcComputePassEncoderDispatchWorkgroupsIndirect)
    {
      action.flags = ActionFlags::Dispatch | ActionFlags::Indirect;
    }
    else if(context == WebGPUChunk::ProcComputePassEncoderEnd)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::EndPass;
    }
    else if(context == WebGPUChunk::ProcComputePassEncoderInsertDebugMarker)
    {
      action.flags = ActionFlags::SetMarker;
    }
    else if(context == WebGPUChunk::ProcComputePassEncoderPushDebugGroup)
    {
      action.flags = ActionFlags::PushMarker;
    }
    else if(context == WebGPUChunk::ProcComputePassEncoderPopDebugGroup)
    {
      action.flags = ActionFlags::PopMarker;
    }
    else if(context == WebGPUChunk::ProcDevicePushErrorScope)
    {
      action.flags = ActionFlags::PushMarker;
    }
    else if(context == WebGPUChunk::ProcDevicePopErrorScope)
    {
      action.flags = ActionFlags::PopMarker;
    }
    else if(context == WebGPUChunk::ProcQueueCopyExternalTextureForBrowser ||
            context == WebGPUChunk::ProcQueueCopyTextureForBrowser ||
            context == WebGPUChunk::ProcQueueWriteBuffer||
            context == WebGPUChunk::ProcQueueWriteTexture)
    {
      action.flags = ActionFlags::Copy;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderDraw ||
            context == WebGPUChunk::ProcRenderBundleEncoderDraw)
    {
      action.flags = ActionFlags::Drawcall;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderDrawIndexed ||
            context == WebGPUChunk::ProcRenderBundleEncoderDrawIndexed)
    {
      action.flags = ActionFlags::Drawcall | ActionFlags::Indexed;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderDrawIndexedIndirect ||
            context == WebGPUChunk::ProcRenderBundleEncoderDrawIndexedIndirect)
    {
      action.flags = ActionFlags::Drawcall | ActionFlags::Indexed | ActionFlags::Indirect;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderDrawIndirect ||
            context == WebGPUChunk::ProcRenderBundleEncoderDrawIndirect)
    {
      action.flags = ActionFlags::Drawcall | ActionFlags::Indirect;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderMultiDrawIndexedIndirect)
    {
      action.flags = ActionFlags::Drawcall | ActionFlags::MultiAction | ActionFlags::Indexed |
                     ActionFlags::Indirect;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderMultiDrawIndirect)
    {
      action.flags = ActionFlags::Drawcall | ActionFlags::MultiAction | ActionFlags::Indirect;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderInsertDebugMarker ||
            context == WebGPUChunk::ProcRenderBundleEncoderInsertDebugMarker)
    {
      action.flags = ActionFlags::SetMarker;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderPushDebugGroup ||
            context == WebGPUChunk::ProcRenderBundleEncoderPushDebugGroup)
    {
      action.flags = ActionFlags::PushMarker;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderPopDebugGroup ||
            context == WebGPUChunk::ProcRenderBundleEncoderPopDebugGroup)
    {
      action.flags = ActionFlags::PopMarker;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderBeginOcclusionQuery)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::BeginPass;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderEndOcclusionQuery)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::EndPass;
    }
    else if(context == WebGPUChunk::ProcRenderPassEncoderEnd ||
            context == WebGPUChunk::ProcRenderBundleEncoderFinish)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::EndPass;
    }
    else if(context == WebGPUChunk::ProcSharedTextureMemoryBeginAccess)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::BeginPass;
    }
    else if(context == WebGPUChunk::ProcSharedTextureMemoryEndAccess)
    {
      action.flags = ActionFlags::PassBoundary | ActionFlags::EndPass;
    }
    
    {
      APIEvent evt;
      evt.eventId = firstEventId + 0;
      evt.chunkIndex = APIEvent::NoChunk;
      action.events.push_back(evt);
    }
    {
      APIEvent evt;
      evt.eventId = firstEventId + 1;
      evt.chunkIndex = APIEvent::NoChunk;
      action.events.push_back(evt);

      action.eventId = action.events.back().eventId;
    }
    m_FrameRecord.actionList.push_back(action);
  };

  switch(context)
  {
    case WebGPUChunk::ProcCreateInstance:
    {
      WGPUInstanceDescriptor descriptor = WGPU_INSTANCE_DESCRIPTOR_INIT;
      WGPUInstanceDescriptor *pDescriptor = &descriptor;
      SERIALISE_ELEMENT_OPT(pDescriptor);

      AddMockAction(context , "wgpuCreateInstance()");
      
      return true;
    }

    case WebGPUChunk::ProcInstanceRelease:
    {
      size_t instanceId;
      SERIALISE_ELEMENT(instanceId);

      AddMockAction(context, StringFormat::Fmt("wgpuInstanceRelease(%#010x)", instanceId));

      return true;
    }

    #define HANDLE_PROC(proc) \
      case WebGPUChunk::Proc##proc: \
      { \
        AddMockAction(context , "wgpu" #proc); \
        return true; \
      }
    FOREACH_WEBGPU_PROC_WITH_DEFAULT_REPLAY_BEHAVIOR(HANDLE_PROC)

    default: return false;
  }
}

void WebGPUDriver::ReplayLog(uint32_t endEventID, ReplayLogType replayType)
{
}

SDFile *WebGPUDriver::GetStructuredFile()
{
  return m_SDFile;
}

rdcarray<uint32_t> WebGPUDriver::GetPassEvents(uint32_t eventId)
{
  return {eventId};
}

void WebGPUDriver::InitPostVSBuffers(uint32_t eventId)
{
}

void WebGPUDriver::InitPostVSBuffers(const rdcarray<uint32_t> &passEvents)
{
}

ResourceId WebGPUDriver::GetLiveID(ResourceId id)
{
  return id;
}

MeshFormat WebGPUDriver::GetPostVSBuffers(uint32_t eventId, uint32_t instID, uint32_t viewID,
                                         MeshDataStage stage)
{
  return {};
}

void WebGPUDriver::GetBufferData(ResourceId buff, uint64_t offset, uint64_t len, bytebuf &retData)
{
  retData.clear();
}

void WebGPUDriver::GetTextureData(ResourceId tex, const Subresource &sub,
                                 const GetTextureDataParams &params, bytebuf &data)
{
  data.clear();
}

void WebGPUDriver::BuildTargetShader(ShaderEncoding sourceEncoding, const bytebuf &source,
                                    const rdcstr &entry, const ShaderCompileFlags &compileFlags,
                                    ShaderStage type, ResourceId &id, rdcstr &errors)
{
  id = ResourceId();
  errors = "Unrecoverable error encountered while analysing capture";
}

rdcarray<ShaderEncoding> WebGPUDriver::GetTargetShaderEncodings()
{
  return {ShaderEncoding::HLSL, ShaderEncoding::GLSL};
}

void WebGPUDriver::ReplaceResource(ResourceId from, ResourceId to)
{
}

void WebGPUDriver::RemoveReplacement(ResourceId id)
{
}

void WebGPUDriver::FreeTargetResource(ResourceId id)
{
}

void WebGPUDriver::ClearReplayCache()
{
}

rdcarray<GPUCounter> WebGPUDriver::EnumerateCounters()
{
  return {};
}

CounterDescription WebGPUDriver::DescribeCounter(GPUCounter counterID)
{
  return {};
}

rdcarray<CounterResult> WebGPUDriver::FetchCounters(const rdcarray<GPUCounter> &counterID)
{
  return {};
}

void WebGPUDriver::FillCBufferVariables(ResourceId pipeline, ResourceId shader, ShaderStage stage,
                                       rdcstr entryPoint, uint32_t cbufSlot,
                                       rdcarray<ShaderVariable> &outvars, const bytebuf &data)
{
  outvars.clear();
}

rdcarray<PixelModification> WebGPUDriver::PixelHistory(rdcarray<EventUsage> events,
                                                      ResourceId target, uint32_t x, uint32_t y,
                                                      const Subresource &sub, CompType typeCast)
{
  return {};
}

ShaderDebugTrace *WebGPUDriver::DebugVertex(uint32_t eventId, uint32_t vertid, uint32_t instid,
                                           uint32_t idx, uint32_t view)
{
  return new ShaderDebugTrace;
}

ShaderDebugTrace *WebGPUDriver::DebugMeshThread(uint32_t eventId,
                                               const rdcfixedarray<uint32_t, 3> &groupid,
                                               const rdcfixedarray<uint32_t, 3> &threadid)
{
  return new ShaderDebugTrace;
}

ShaderDebugTrace *WebGPUDriver::DebugPixel(uint32_t eventId, uint32_t x, uint32_t y,
                                          const DebugPixelInputs &inputs)
{
  return new ShaderDebugTrace;
}

ShaderDebugTrace *WebGPUDriver::DebugThread(uint32_t eventId,
                                           const rdcfixedarray<uint32_t, 3> &groupid,
                                           const rdcfixedarray<uint32_t, 3> &threadid)
{
  return new ShaderDebugTrace;
}

rdcarray<ShaderDebugState> WebGPUDriver::ContinueDebug(ShaderDebugger *debugger)
{
  return {};
}

void WebGPUDriver::FreeDebugger(ShaderDebugger *debugger)
{
}

ResourceId WebGPUDriver::RenderOverlay(ResourceId texid, FloatVector clearCol, DebugOverlay overlay,
                                      uint32_t eventId, const rdcarray<uint32_t> &passEvents)
{
  return ResourceId();
}

bool WebGPUDriver::IsRenderOutput(ResourceId id)
{
  return false;
}

void WebGPUDriver::FileChanged()
{
}

bool WebGPUDriver::NeedRemapForFetch(const ResourceFormat &format)
{
  return false;
}

DriverInformation WebGPUDriver::GetDriverInfo()
{
  return m_DriverInfo;
}

rdcarray<GPUDevice> WebGPUDriver::GetAvailableGPUs()
{
  return m_GPUs;
}

bool WebGPUDriver::IsRemoteProxy()
{
  return m_Proxy;
}

RDResult WebGPUDriver::FatalErrorCheck()
{
  return ResultCode::Succeeded;
}

IReplayDriver *WebGPUDriver::MakeDummyDriver()
{
  return NULL;
}

rdcarray<WindowingSystem> WebGPUDriver::GetSupportedWindowSystems()
{
  rdcarray<WindowingSystem> ret;
#if ENABLED(RDOC_LINUX)

#if ENABLED(RDOC_XLIB)
  ret.push_back(WindowingSystem::Xlib);
#endif

#if ENABLED(RDOC_XCB)
  ret.push_back(WindowingSystem::XCB);
#endif

#if ENABLED(RDOC_WAYLAND)
  ret.push_back(WindowingSystem::Wayland);
#endif

#elif ENABLED(RDOC_WIN32)

  ret.push_back(WindowingSystem::Win32);

#elif ENABLED(RDOC_ANDROID)

  ret.push_back(WindowingSystem::Android);

#elif ENABLED(RDOC_APPLE)

  ret.push_back(WindowingSystem::MacOS);

#endif

  return ret;
}

AMDRGPControl *WebGPUDriver::GetRGPControl()
{
  return NULL;
}

uint64_t WebGPUDriver::MakeOutputWindow(WindowingData window, bool depth)
{
  return 1;
}

void WebGPUDriver::DestroyOutputWindow(uint64_t id)
{
}

bool WebGPUDriver::CheckResizeOutputWindow(uint64_t id)
{
  return false;
}

void WebGPUDriver::GetOutputWindowDimensions(uint64_t id, int32_t &w, int32_t &h)
{
}

void WebGPUDriver::GetOutputWindowData(uint64_t id, bytebuf &retData)
{
}

void WebGPUDriver::ClearOutputWindowColor(uint64_t id, FloatVector col)
{
}

void WebGPUDriver::ClearOutputWindowDepth(uint64_t id, float depth, uint8_t stencil)
{
}

void WebGPUDriver::BindOutputWindow(uint64_t id, bool depth)
{
}

bool WebGPUDriver::IsOutputWindowVisible(uint64_t id)
{
  return true;
}

void WebGPUDriver::FlipOutputWindow(uint64_t id)
{
}

bool WebGPUDriver::GetMinMax(ResourceId texid, const Subresource &sub, CompType typeCast,
                            float *minval, float *maxval)
{
  *minval = 0.0f;
  *maxval = 1.0f;
  return false;
}

bool WebGPUDriver::GetHistogram(ResourceId texid, const Subresource &sub, CompType typeCast,
                               float minval, float maxval, const rdcfixedarray<bool, 4> &channels,
                               rdcarray<uint32_t> &histogram)
{
  histogram.fill(256, 0);
  return false;
}

void WebGPUDriver::PickPixel(ResourceId texture, uint32_t x, uint32_t y, const Subresource &sub,
                            CompType typeCast, float pixel[4])
{
}

ResourceId WebGPUDriver::CreateProxyTexture(const TextureDescription &templateTex)
{
  return ResourceId();
}

void WebGPUDriver::SetProxyTextureData(ResourceId texid, const Subresource &sub, byte *data,
                                      size_t dataSize)
{
}

bool WebGPUDriver::IsTextureSupported(const TextureDescription &tex)
{
  return true;
}

ResourceId WebGPUDriver::CreateProxyBuffer(const BufferDescription &templateBuf)
{
  return ResourceId();
}

void WebGPUDriver::SetProxyBufferData(ResourceId bufid, byte *data, size_t dataSize)
{
}

void WebGPUDriver::RenderMesh(uint32_t eventId, const rdcarray<MeshFormat> &secondaryDraws,
                             const MeshDisplay &cfg)
{
}

bool WebGPUDriver::RenderTexture(TextureDisplay cfg)
{
  return false;
}

void WebGPUDriver::SetCustomShaderIncludes(const rdcarray<rdcstr> &directories)
{
}

void WebGPUDriver::BuildCustomShader(ShaderEncoding sourceEncoding, const bytebuf &source,
                                    const rdcstr &entry, const ShaderCompileFlags &compileFlags,
                                    ShaderStage type, ResourceId &id, rdcstr &errors)
{
  id = ResourceId();
  errors = "Unrecoverable error encountered while analysing capture";
}

rdcarray<ShaderEncoding> WebGPUDriver::GetCustomShaderEncodings()
{
  return m_CustomEncodings;
}

rdcarray<ShaderSourcePrefix> WebGPUDriver::GetCustomShaderSourcePrefixes()
{
  return m_CustomPrefixes;
}

ResourceId WebGPUDriver::ApplyCustomShader(TextureDisplay &display)
{
  return ResourceId();
}

void WebGPUDriver::FreeCustomShader(ResourceId id)
{
}

void WebGPUDriver::RenderCheckerboard(FloatVector dark, FloatVector light)
{
}

void WebGPUDriver::RenderHighlightBox(float w, float h, float scale)
{
}

uint32_t WebGPUDriver::PickVertex(uint32_t eventId, int32_t width, int32_t height,
                                 const MeshDisplay &cfg, uint32_t x, uint32_t y)
{
  return ~0U;
}
