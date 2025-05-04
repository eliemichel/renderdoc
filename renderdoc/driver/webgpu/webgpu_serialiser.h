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

#include "generated/webgpu_serialiser_gen.h"

#include "webgpu_capture.h"

#include "core/core.h"

// In this file, we find the serialisation procedure that are manually written
// (as opposed to "generated/webgpu_serialiser.h")

DECLARE_REFLECTION_STRUCT(WGPUStringView);

DECLARE_REFLECTION_STRUCT(WebGPUInitParams);
DECLARE_REFLECTION_STRUCT(WebGPUResourceUsage);
DECLARE_REFLECTION_STRUCT(WebGPUEventInfo);

template <typename SerialiserType, typename DescriptorType>
void Serialize_WebGPUResource(SerialiserType &ser, const char* resourceTypeName, ResourceDescription& rdDesc, DescriptorType &wgpuDesc)
{
  ResourceId resourceId;
  SERIALISE_ELEMENT(resourceId);
  SERIALISE_ELEMENT(wgpuDesc);

  rdDesc.resourceId = resourceId;
  rdDesc.type = ResourceType::Unknown;
  std::string label = toStdStringView(wgpuDesc.label);
  if(wgpuDesc.label.data != NULL)
  {
    rdDesc.SetCustomName(StringFormat::Fmt("%s '%s'", resourceTypeName, label));
  }
  else
  {
    rdDesc.SetCustomName(StringFormat::Fmt("%s (Unlabeled)", resourceTypeName));
  }
}
