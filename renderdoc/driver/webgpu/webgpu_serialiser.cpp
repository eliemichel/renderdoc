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

#include "webgpu_serialiser.h"

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WGPUStringView &el)
{
  const char *str_view = NULL;
  char *owned_str = NULL;

  if(ser.IsWriting() && el.data != NULL)
  {
    if(el.length == WGPU_STRLEN)
    {
      str_view = el.data;
    }
    else
    {
      owned_str = new char[el.length + 1];
      memcpy(owned_str, el.data, el.length);
      owned_str[el.length] = '\0';
      str_view = owned_str;
    }
  }

  SERIALISE_ELEMENT(str_view);

  if(ser.IsReading())
  {
    el.data = str_view;
    el.length = WGPU_STRLEN;
  }

  if(owned_str != NULL)
  {
    delete[] owned_str;
  }
}

INSTANTIATE_SERIALISE_TYPE(WGPUStringView);

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WebGPUInitParams &el)
{
  SERIALISE_MEMBER(Test);
}

INSTANTIATE_SERIALISE_TYPE(WebGPUInitParams);

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WebGPUResourceUsage &el)
{
  SERIALISE_MEMBER(usage);
  SERIALISE_MEMBER(view);
}

INSTANTIATE_SERIALISE_TYPE(WebGPUResourceUsage);

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WebGPUEventInfo &el)
{
  SERIALISE_MEMBER(resourceUsages);
}

INSTANTIATE_SERIALISE_TYPE(WebGPUEventInfo);
