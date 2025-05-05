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

#include "webgpu_manager.h"

#include <stdexcept>

WebGPUResource* WebGPUResourceRecord::NullResource = NULL;

WebGPUResourceRecord::WebGPUResourceRecord(ResourceId id)
    : ResourceRecord(id, true)
{
}
/*
void WebGPUResourceRecord::Insert(const std::map<int64_t, Chunk *> &sortedChunks)
{
    // TODO(elie)
}

void WebGPUResourceRecord::MarkDataUnwritten()
{
  // TODO(elie)
}
*/
WebGPUResourceManager::WebGPUResourceManager(CaptureState &state)
    : ResourceManager(state)
{
}

ResourceId WebGPUResourceManager::GetID(WrappedResourceType res)
{
  return res->id;
}

bool WebGPUResourceManager::ResourceTypeRelease(WrappedResourceType res)
{
  return true;    // TODO(elie)
}

bool WebGPUResourceManager::Prepare_InitialState(WrappedResourceType res)
{
  return true;    // TODO(elie)
}

uint64_t WebGPUResourceManager::GetSize_InitialState(ResourceId id, const InitialContentData &initial)
{
  return 0;    // TODO(elie)
}

bool WebGPUResourceManager::Serialise_InitialState(WriteSerialiser &ser, ResourceId id,
                                                   RecordType *record,
                                                   const InitialContentData *initialData)
{
  return true;    // TODO(elie) Called from ApplyInitialContentsNonChunks
}

void WebGPUResourceManager::Create_InitialState(ResourceId id, WrappedResourceType live, bool hasData)
{
  // TODO(elie)
}

void WebGPUResourceManager::Apply_InitialState(WrappedResourceType live, InitialContentData &initial)
{
  // TODO(elie)
}

void WebGPUResourceManager::SetResourceHandle(ResourceId id, void *handle)
{
  if(m_HandleToResourceId.find(handle) != m_HandleToResourceId.end())
  {
    throw std::runtime_error(
        StringFormat::Fmt("Handle '%#010x' already has an associated resource ID!", handle).c_str());
  }
  m_HandleToResourceId.insert({handle, id});
}

ResourceId WebGPUResourceManager::GetResourceId(void *handle)
{
  auto it = m_HandleToResourceId.find(handle);
  if(it == m_HandleToResourceId.end())
  {
    return ResourceId::Null();
  }
  else
  {
    return it->second;
  }
}

void WebGPUResourceManager::ReleaseResource(void *handle)
{
  m_HandleToResourceId.erase(handle);
}
