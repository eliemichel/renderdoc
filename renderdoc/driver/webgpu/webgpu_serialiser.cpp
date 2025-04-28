#include "webgpu_serialiser.h"

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WGPUInstanceCapabilities &el)
{
  // SERIALISE_MEMBER(nextInChain); // TODO(elie)
  SERIALISE_MEMBER(timedWaitAnyEnable);
  SERIALISE_MEMBER(timedWaitAnyMaxCount);
}

INSTANTIATE_SERIALISE_TYPE(WGPUInstanceCapabilities);

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WGPUInstanceDescriptor &el)
{
  //SERIALISE_MEMBER(nextInChain); // TODO(elie)
  SERIALISE_MEMBER(capabilities);
}

INSTANTIATE_SERIALISE_TYPE(WGPUInstanceDescriptor);

template <typename SerialiserType>
void DoSerialise(SerialiserType &ser, WGPUInstance &el)
{
  SERIALISE_ELEMENT(el);
}

INSTANTIATE_SERIALISE_TYPE(WGPUInstance);
