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
#include "webgpu_utils.h"
#include "webgpu_manager.h"
#include "webgpu_serialiser.h"

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

  CaptureState state = CaptureState::LoadingReplaying;
  m_ResourceManager = new WebGPUResourceManager(state);


  // TODO(elie): Serialize in capture init info
  m_Props.pipelineType = GraphicsAPI::Vulkan;
  m_Props.localRenderer = GraphicsAPI::Vulkan;
  m_Props.vendor = GPUVendor::Unknown;

  // TODO(elie): This is mock data
  m_SDFile = new SDFile();

  // TODO(elie): This is mock data
  ResourceDescription mockResource;
  mockResource.resourceId = ResourceIDGen::GetNewUniqueID();
  mockResource.type = ResourceType::Device;
  mockResource.SetCustomName("Mock Device");
  m_Resources.push_back(mockResource);
}

WebGPUDriver::~WebGPUDriver()
{
  m_ResourceManager->Shutdown();
  SAFE_DELETE(m_ResourceManager);

  SAFE_DELETE(m_SDFile);
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
  rdcarray<DebugMessage> returnedMessages;
  std::swap(m_PendingDebugMessages, returnedMessages);
  return returnedMessages;
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
  return "; Shader disassembly is not available in the WebGPU driver.";
}

rdcarray<EventUsage> WebGPUDriver::GetUsage(ResourceId id)
{
  return m_ResourceUses[id];
}

void WebGPUDriver::SetPipelineStates(D3D11Pipe::State *d3d11, D3D12Pipe::State *d3d12,
                                    GLPipe::State *gl, VKPipe::State *vk)
{
  RDCDEBUG("[WebGPU driver] SetPipelineStates");
}

void WebGPUDriver::SavePipelineState(uint32_t eventId)
{
  RDCDEBUG("[WebGPU driver] SavePipelineState");
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

  // We use the same chunks to build structured data and to replay
  // TODO(elie): Should we change that?
  StreamReader *sourceReader = rdc->ReadSection(sectionIdx);
  uint64_t frameDataSize = sourceReader->GetSize() - sourceReader->GetOffset();
  m_FrameReader = new StreamReader(sourceReader, frameDataSize);
  SAFE_DELETE(sourceReader);
  
  StreamReader *reader = m_FrameReader;
  reader->SetOffset(0);

  ReadSerialiser ser(reader, Ownership::Nothing);

  ser.SetUserData(GetResourceManager());
  ser.SetStringDatabase(&m_Strings);

  ser.SetVersion(version);

  {
    SystemChunk chunk = ser.ReadChunk<SystemChunk>();

    if(chunk != SystemChunk::DriverInit)
    {
      RETURN_ERROR_RESULT(ResultCode::FileCorrupted,
                          "Expected to get a DriverInit chunk, instead got %u", chunk);
    }

    ProcessChunk(ser, (WebGPUChunk)chunk);

    ser.EndChunk();
  }

  if(ser.IsErrored())
  {
    return ser.GetError();
  }

  // Reset reading state before starting to process chunks
  // TODO(elie): If we create a class dedicated to Action tree building, move that to its constructor
  m_ActionStack.clear();
  m_PendingEvents.clear();
  m_NextActionId = 0;
  m_NextEventId = 0;
  m_SDFile->chunks.clear();
  AddWipWarningMessage();

  for(;;)
  {
    if(reader->IsErrored() || reader->AtEnd())
      break;

    WebGPUChunk context = ser.ReadChunk<WebGPUChunk>();

    if(reader->IsErrored())
      return RDResult(ResultCode::APIDataCorrupted, ser.GetError().message);

    bool success = ProcessChunk(ser, context);

    if(reader->IsErrored())
      return RDResult(
          ResultCode::APIDataCorrupted,
                      StringFormat::Fmt("Failed to process chunk with type %#010x", context));

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
  switch((SystemChunk)context)
  {
    case SystemChunk::DriverInit:
    {    // TODO(elie): We don't use initParams
      WebGPUInitParams initParams;
      SERIALISE_ELEMENT(initParams);
      return true;
    }

    case SystemChunk::InitialContentsList:
    {
      GetResourceManager()->CreateInitialContents(ser);
      return true;
    }

    default: break;
  }

  switch(context)
  {
    case WebGPUChunk::ProcCreateInstance:
    {
      // TODO(elie): There is no reason for ProcCreateInstance and ProcInstanceRelease to be special cases for now
      WGPUInstanceDescriptor descriptor = WGPU_INSTANCE_DESCRIPTOR_INIT;
      WGPUInstanceDescriptor *pDescriptor = &descriptor;
      SERIALISE_ELEMENT_OPT(pDescriptor);

      WebGPUEventInfo eventInfo;
      AddEvent(context, eventInfo, "wgpuCreateInstance()");
      
      return true;
    }

    case WebGPUChunk::ProcInstanceRelease:
    {
      size_t instanceId;
      SERIALISE_ELEMENT(instanceId);

      WebGPUEventInfo eventInfo;
      AddEvent(context, eventInfo, StringFormat::Fmt("wgpuInstanceRelease(%#010x)", instanceId));

      return true;
    }

    // Default proc handler
#define HANDLE_PROC(proc)                       \
  case WebGPUChunk::Proc##proc:                 \
  {                                             \
    WebGPUEventInfo eventInfo;                  \
    SERIALISE_ELEMENT(eventInfo);               \
    AddEvent(context, eventInfo, "wgpu" #proc); \
    return true;                                \
  }
    FOREACH_WEBGPU_PROC_WITH_DEFAULT_REPLAY_BEHAVIOR(HANDLE_PROC)

    // Resource handlers
    case WebGPUChunk::ResTexture:
    {
      ResourceDescription res;
      WGPUTextureDescriptor wgpuDesc;
      Serialize_WebGPUResource(ser, "Texture", res, wgpuDesc);
      res.type = ResourceType::Texture;
      m_Resources.push_back(res);
      m_ResourceUses.insert({res.resourceId, {}});

      TextureDescription desc = toRdTextureDescription(wgpuDesc);
      desc.resourceId = res.resourceId;
      m_Textures.push_back(desc);
      return true;
    }

    // Default resource handler
#define HANDLE_RESOURCE_TYPE(resType)                          \
  case WebGPUChunk::Res##resType:                              \
  {                                                            \
    ResourceDescription rdDesc;                                \
    WGPU##resType##Descriptor wgpuDesc;                            \
    Serialize_WebGPUResource(ser, #resType, rdDesc, wgpuDesc); \
    rdDesc.type = ResourceType::Unknown; /* TODO(elie) */      \
    m_Resources.push_back(rdDesc);                             \
    m_ResourceUses.insert({rdDesc.resourceId, {}});            \
    /* TODO(elie): Add to resource-specific descriptors */     \
    return true;                                               \
  }
    FOREACH_WEBGPU_RESOURCE_TYPE_WITH_DEFAULT_REPLAY_BEHAVIOR(HANDLE_RESOURCE_TYPE)

    default: return false;
  }
}

void WebGPUDriver::AddEvent(WebGPUChunk context, const WebGPUEventInfo& eventInfo, rdcstr name)
{
  ActionDescription action;
  action.customName = name;
  action.flags = toRdActionFlags(context);

  bool pushActionOnStack = (action.flags & ActionFlags::BeginPass) != ActionFlags::NoFlags;
  bool popActionFromStack = (action.flags & ActionFlags::EndPass) != ActionFlags::NoFlags;
  bool isActionEvent = action.flags != ActionFlags::NoFlags;

  SDChunk *chunk = new SDChunk(rdcinflexiblestr(name));
  
  APIEvent evt;
  evt.eventId = m_NextEventId++;
  evt.chunkIndex = static_cast<uint32_t>(m_SDFile->chunks.size());
  m_SDFile->chunks.push_back(chunk);

  // TODO(elie): read eventInfo
  //m_ResourceUses

  m_PendingEvents.push_back(evt);

  if(isActionEvent)
  {
    action.actionId = m_NextActionId++;
    std::swap(action.events, m_PendingEvents);
    action.eventId = action.events.back().eventId;

    if(pushActionOnStack)
    {
      // Instead of directly logging this action, we put it on hold in the stack
      // so that next actions are added as children.
      m_ActionStack.push_back(action);
    }
    else
    {
      AddAction(action);
    }

    if(popActionFromStack)
    {
      if(m_ActionStack.empty())
      {
        // TODO(elie): Log error about mismatch of begin/end sections
      }
      else
      {
        auto parent = m_ActionStack.back();
        m_ActionStack.pop_back();

        AddAction(parent);
      }
    }
  }
}

void WebGPUDriver::AddAction(const ActionDescription &action)
{
  if(m_ActionStack.empty())
  {
    m_FrameRecord.actionList.push_back(action);
  }
  else
  {
    m_ActionStack.back().children.push_back(action);
  }
}

void WebGPUDriver::AddWipWarningMessage()
{
  DebugMessage WipWarningMsg;
  WipWarningMsg.eventId = 0;
  WipWarningMsg.category = MessageCategory::Miscellaneous;
  WipWarningMsg.severity = MessageSeverity::Info;
  WipWarningMsg.source = MessageSource::RuntimeWarning;
  WipWarningMsg.messageID = 0;
  WipWarningMsg.description = "The WebGPU driver for RenderDoc is EXPERIMENTAL! Use with caution.";
  m_PendingDebugMessages.push_back(WipWarningMsg);
}

void WebGPUDriver::ReplayLog(uint32_t endEventID, ReplayLogType replayType)
{
  RDCDEBUG("[WebGPU driver] ReplayLog, endEventID = ", endEventID, ", replayType = ", replayType);

  StreamReader *reader = m_FrameReader;
  reader->SetOffset(0);

  ReadSerialiser ser(reader, Ownership::Nothing);

  ser.SetVersion(WebGPUInitParams::CurrentVersion);

  /* SystemChunk chunk = */ser.ReadChunk<SystemChunk>();
  // TODO(elie): Use init info to init replay context
  ser.EndChunk();

  EnsureReplayContext();

  for(;;)
  {
    if(reader->IsErrored() || reader->AtEnd())
      break;

    WebGPUChunk context = ser.ReadChunk<WebGPUChunk>();

    // TODO(elie)
    //ReplayChunk(ser, context, replayType);

    ser.EndChunk();

    // TODO(elie): Break when reaching endEventID

    if((SystemChunk)context == SystemChunk::CaptureScope || reader->IsErrored() || reader->AtEnd())
      break;
  }
}

void WebGPUDriver::EnsureReplayContext()
{
  if(!m_ReplayContext.ready)
  {
    m_ReplayContext.Init();
  }
}

void WebGPUDriver::ReplayContext::Init()
{
  // TODO(elie): Check for loading errors
  LoadProcs();

  instance = wgpuCreateInstance(NULL);

  WGPURequestAdapterOptions opts = WGPU_REQUEST_ADAPTER_OPTIONS_INIT; 
  WGPUAdapter adapter = requestAdapterSync(instance, &opts);

  WGPUDeviceDescriptor desc = WGPU_DEVICE_DESCRIPTOR_INIT;
  device = requestDeviceSync(instance, adapter, &desc);

  ready = true;
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
