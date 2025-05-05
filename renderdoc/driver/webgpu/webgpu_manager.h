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
#include "official/webgpu.h"

#include "core/resource_manager.h"

#include <map>

class WebGPUResourceManager;

struct WebGPUResource
{
  ResourceId id;

  void AddRef() {}
  void Release() {}
};

struct WebGPUResourceRecord : public ResourceRecord
{
  static WebGPUResource* NullResource;

  rdcstr Label;

  WebGPUResourceRecord(ResourceId id);
};

struct WebGPUInitialContents
{
  template <typename Configuration>
  void Free(ResourceManager<Configuration> *rm)
  {}
};

struct WebGPUResourceManagerConfiguration
{
  typedef WebGPUResource *WrappedResourceType;
  typedef WebGPUResource *RealResourceType;
  typedef WebGPUResourceRecord RecordType;
  typedef WebGPUInitialContents InitialContentData;
};

class WebGPUResourceManager : public ResourceManager<WebGPUResourceManagerConfiguration>
{
public:
  WebGPUResourceManager(CaptureState &state);

#define HANDLE_RESOURCE(ResType)                              \
  void SetResourceHandle(ResourceId id, WGPU##ResType handle) \
  {                                                           \
    SetResourceHandle(id, (void *)handle);                    \
  }                                                           \
  ResourceId GetResourceId(WGPU##ResType handle) { return GetResourceId((void *)handle); } \
  void ReleaseResource(WGPU##ResType handle) { ReleaseResource((void *)handle); }
  FOREACH_WEBGPU_RESOURCE_TYPE(HANDLE_RESOURCE)
#undef HANDLE_RESOURCE

protected: // Implement ResourceManager abstract API
  ResourceId GetID(WrappedResourceType res) override;

  bool ResourceTypeRelease(WrappedResourceType res) override;

  bool Prepare_InitialState(WrappedResourceType res) override;

  uint64_t GetSize_InitialState(ResourceId id, const InitialContentData &initial) override;

  bool Serialise_InitialState(WriteSerialiser &ser, ResourceId id, RecordType *record,
                                      const InitialContentData *initialData) override;
  void Create_InitialState(ResourceId id, WrappedResourceType live, bool hasData) override;
  void Apply_InitialState(WrappedResourceType live, InitialContentData &initial) override;

private:
  // Register a new resource handle and associate it an ID
  void SetResourceHandle(ResourceId id, void *handle);

  // Retrieve the id associated to the handle
  ResourceId GetResourceId(void *handle);

  // Indicate that the handle is no longer used, because the same handle may be
  // reused later to represent a new resource
  void ReleaseResource(void *handle);

private:
  // Map the actual resource handle to RenderDoc's resource ID
  std::map<void *, ResourceId> m_HandleToResourceId;
};
