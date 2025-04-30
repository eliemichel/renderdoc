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

/**
 * IMPORTANT: This file is AUTO-GENERATED, do not directly modify it.
 * See 'generate_renderdoc.py' in the 'renderdoc' branch of https://github.com/eliemichel/WebGPU-Cpp
 */

/**
 * NB: This is meant to be included in the definition of WebGPUHook in the
 * manually written webgpu_hooks.cpp
 */

static void wgpuAdapterInfoFreeMembers_hook(WGPUAdapterInfo value) {
    webgpuHooks.procs.wgpuAdapterInfoFreeMembers(value);
}
static void wgpuAdapterPropertiesMemoryHeapsFreeMembers_hook(WGPUAdapterPropertiesMemoryHeaps value) {
    webgpuHooks.procs.wgpuAdapterPropertiesMemoryHeapsFreeMembers(value);
}
static void wgpuAdapterPropertiesSubgroupMatrixConfigsFreeMembers_hook(WGPUAdapterPropertiesSubgroupMatrixConfigs value) {
    webgpuHooks.procs.wgpuAdapterPropertiesSubgroupMatrixConfigsFreeMembers(value);
}
static void wgpuDawnDrmFormatCapabilitiesFreeMembers_hook(WGPUDawnDrmFormatCapabilities value) {
    webgpuHooks.procs.wgpuDawnDrmFormatCapabilitiesFreeMembers(value);
}
static WGPUStatus wgpuGetInstanceCapabilities_hook(WGPUInstanceCapabilities * capabilities) {
    return webgpuHooks.procs.wgpuGetInstanceCapabilities(capabilities);
}
static WGPUProc wgpuGetProcAddress_hook(WGPUStringView procName) {
    return webgpuHooks.procs.wgpuGetProcAddress(procName);
}
static void wgpuSharedBufferMemoryEndAccessStateFreeMembers_hook(WGPUSharedBufferMemoryEndAccessState value) {
    webgpuHooks.procs.wgpuSharedBufferMemoryEndAccessStateFreeMembers(value);
}
static void wgpuSharedTextureMemoryEndAccessStateFreeMembers_hook(WGPUSharedTextureMemoryEndAccessState value) {
    webgpuHooks.procs.wgpuSharedTextureMemoryEndAccessStateFreeMembers(value);
}
static void wgpuSupportedWGSLLanguageFeaturesFreeMembers_hook(WGPUSupportedWGSLLanguageFeatures value) {
    webgpuHooks.procs.wgpuSupportedWGSLLanguageFeaturesFreeMembers(value);
}
static void wgpuSupportedFeaturesFreeMembers_hook(WGPUSupportedFeatures value) {
    webgpuHooks.procs.wgpuSupportedFeaturesFreeMembers(value);
}
static void wgpuSurfaceCapabilitiesFreeMembers_hook(WGPUSurfaceCapabilities value) {
    webgpuHooks.procs.wgpuSurfaceCapabilitiesFreeMembers(value);
}
static WGPUDevice wgpuAdapterCreateDevice_hook(WGPUAdapter adapter, WGPUDeviceDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuAdapterCreateDevice(adapter, descriptor);
}
static void wgpuAdapterGetFeatures_hook(WGPUAdapter adapter, WGPUSupportedFeatures * features) {
    webgpuHooks.procs.wgpuAdapterGetFeatures(adapter, features);
}
static WGPUStatus wgpuAdapterGetFormatCapabilities_hook(WGPUAdapter adapter, WGPUTextureFormat format, WGPUDawnFormatCapabilities * capabilities) {
    return webgpuHooks.procs.wgpuAdapterGetFormatCapabilities(adapter, format, capabilities);
}
static WGPUStatus wgpuAdapterGetInfo_hook(WGPUAdapter adapter, WGPUAdapterInfo * info) {
    return webgpuHooks.procs.wgpuAdapterGetInfo(adapter, info);
}
static WGPUInstance wgpuAdapterGetInstance_hook(WGPUAdapter adapter) {
    return webgpuHooks.procs.wgpuAdapterGetInstance(adapter);
}
static WGPUStatus wgpuAdapterGetLimits_hook(WGPUAdapter adapter, WGPULimits * limits) {
    return webgpuHooks.procs.wgpuAdapterGetLimits(adapter, limits);
}
static WGPUBool wgpuAdapterHasFeature_hook(WGPUAdapter adapter, WGPUFeatureName feature) {
    return webgpuHooks.procs.wgpuAdapterHasFeature(adapter, feature);
}
static WGPUFuture wgpuAdapterRequestDevice_hook(WGPUAdapter adapter, WGPUDeviceDescriptor const * options, WGPURequestDeviceCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuAdapterRequestDevice(adapter, options, callbackInfo);
}
static void wgpuAdapterAddRef_hook(WGPUAdapter adapter) {
    webgpuHooks.procs.wgpuAdapterAddRef(adapter);
}
static void wgpuAdapterRelease_hook(WGPUAdapter adapter) {
    webgpuHooks.procs.wgpuAdapterRelease(adapter);
}
static void wgpuBindGroupSetLabel_hook(WGPUBindGroup bindGroup, WGPUStringView label) {
    webgpuHooks.procs.wgpuBindGroupSetLabel(bindGroup, label);
}
static void wgpuBindGroupAddRef_hook(WGPUBindGroup bindGroup) {
    webgpuHooks.procs.wgpuBindGroupAddRef(bindGroup);
}
static void wgpuBindGroupRelease_hook(WGPUBindGroup bindGroup) {
    webgpuHooks.procs.wgpuBindGroupRelease(bindGroup);
}
static void wgpuBindGroupLayoutSetLabel_hook(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label) {
    webgpuHooks.procs.wgpuBindGroupLayoutSetLabel(bindGroupLayout, label);
}
static void wgpuBindGroupLayoutAddRef_hook(WGPUBindGroupLayout bindGroupLayout) {
    webgpuHooks.procs.wgpuBindGroupLayoutAddRef(bindGroupLayout);
}
static void wgpuBindGroupLayoutRelease_hook(WGPUBindGroupLayout bindGroupLayout) {
    webgpuHooks.procs.wgpuBindGroupLayoutRelease(bindGroupLayout);
}
static void wgpuBufferDestroy_hook(WGPUBuffer buffer) {
    webgpuHooks.procs.wgpuBufferDestroy(buffer);
}
static void const * wgpuBufferGetConstMappedRange_hook(WGPUBuffer buffer, size_t offset, size_t size) {
    return webgpuHooks.procs.wgpuBufferGetConstMappedRange(buffer, offset, size);
}
static WGPUBufferMapState wgpuBufferGetMapState_hook(WGPUBuffer buffer) {
    return webgpuHooks.procs.wgpuBufferGetMapState(buffer);
}
static void * wgpuBufferGetMappedRange_hook(WGPUBuffer buffer, size_t offset, size_t size) {
    return webgpuHooks.procs.wgpuBufferGetMappedRange(buffer, offset, size);
}
static uint64_t wgpuBufferGetSize_hook(WGPUBuffer buffer) {
    return webgpuHooks.procs.wgpuBufferGetSize(buffer);
}
static WGPUBufferUsage wgpuBufferGetUsage_hook(WGPUBuffer buffer) {
    return webgpuHooks.procs.wgpuBufferGetUsage(buffer);
}
static WGPUFuture wgpuBufferMapAsync_hook(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuBufferMapAsync(buffer, mode, offset, size, callbackInfo);
}
static WGPUStatus wgpuBufferReadMappedRange_hook(WGPUBuffer buffer, size_t offset, void * data, size_t size) {
    return webgpuHooks.procs.wgpuBufferReadMappedRange(buffer, offset, data, size);
}
static void wgpuBufferSetLabel_hook(WGPUBuffer buffer, WGPUStringView label) {
    webgpuHooks.procs.wgpuBufferSetLabel(buffer, label);
}
static void wgpuBufferUnmap_hook(WGPUBuffer buffer) {
    webgpuHooks.procs.wgpuBufferUnmap(buffer);
}
static WGPUStatus wgpuBufferWriteMappedRange_hook(WGPUBuffer buffer, size_t offset, void const * data, size_t size) {
    return webgpuHooks.procs.wgpuBufferWriteMappedRange(buffer, offset, data, size);
}
static void wgpuBufferAddRef_hook(WGPUBuffer buffer) {
    webgpuHooks.procs.wgpuBufferAddRef(buffer);
}
static void wgpuBufferRelease_hook(WGPUBuffer buffer) {
    webgpuHooks.procs.wgpuBufferRelease(buffer);
}
static void wgpuCommandBufferSetLabel_hook(WGPUCommandBuffer commandBuffer, WGPUStringView label) {
    webgpuHooks.procs.wgpuCommandBufferSetLabel(commandBuffer, label);
}
static void wgpuCommandBufferAddRef_hook(WGPUCommandBuffer commandBuffer) {
    webgpuHooks.procs.wgpuCommandBufferAddRef(commandBuffer);
}
static void wgpuCommandBufferRelease_hook(WGPUCommandBuffer commandBuffer) {
    webgpuHooks.procs.wgpuCommandBufferRelease(commandBuffer);
}
static WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass_hook(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuCommandEncoderBeginComputePass(commandEncoder, descriptor);
}
static WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass_hook(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuCommandEncoderBeginRenderPass(commandEncoder, descriptor);
}
static void wgpuCommandEncoderClearBuffer_hook(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    webgpuHooks.procs.wgpuCommandEncoderClearBuffer(commandEncoder, buffer, offset, size);
}
static void wgpuCommandEncoderCopyBufferToBuffer_hook(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) {
    webgpuHooks.procs.wgpuCommandEncoderCopyBufferToBuffer(commandEncoder, source, sourceOffset, destination, destinationOffset, size);
}
static void wgpuCommandEncoderCopyBufferToTexture_hook(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) {
    webgpuHooks.procs.wgpuCommandEncoderCopyBufferToTexture(commandEncoder, source, destination, copySize);
}
static void wgpuCommandEncoderCopyTextureToBuffer_hook(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) {
    webgpuHooks.procs.wgpuCommandEncoderCopyTextureToBuffer(commandEncoder, source, destination, copySize);
}
static void wgpuCommandEncoderCopyTextureToTexture_hook(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) {
    webgpuHooks.procs.wgpuCommandEncoderCopyTextureToTexture(commandEncoder, source, destination, copySize);
}
static WGPUCommandBuffer wgpuCommandEncoderFinish_hook(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuCommandEncoderFinish(commandEncoder, descriptor);
}
static void wgpuCommandEncoderInjectValidationError_hook(WGPUCommandEncoder commandEncoder, WGPUStringView message) {
    webgpuHooks.procs.wgpuCommandEncoderInjectValidationError(commandEncoder, message);
}
static void wgpuCommandEncoderInsertDebugMarker_hook(WGPUCommandEncoder commandEncoder, WGPUStringView markerLabel) {
    webgpuHooks.procs.wgpuCommandEncoderInsertDebugMarker(commandEncoder, markerLabel);
}
static void wgpuCommandEncoderPopDebugGroup_hook(WGPUCommandEncoder commandEncoder) {
    webgpuHooks.procs.wgpuCommandEncoderPopDebugGroup(commandEncoder);
}
static void wgpuCommandEncoderPushDebugGroup_hook(WGPUCommandEncoder commandEncoder, WGPUStringView groupLabel) {
    webgpuHooks.procs.wgpuCommandEncoderPushDebugGroup(commandEncoder, groupLabel);
}
static void wgpuCommandEncoderResolveQuerySet_hook(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) {
    webgpuHooks.procs.wgpuCommandEncoderResolveQuerySet(commandEncoder, querySet, firstQuery, queryCount, destination, destinationOffset);
}
static void wgpuCommandEncoderSetLabel_hook(WGPUCommandEncoder commandEncoder, WGPUStringView label) {
    webgpuHooks.procs.wgpuCommandEncoderSetLabel(commandEncoder, label);
}
static void wgpuCommandEncoderWriteBuffer_hook(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const * data, uint64_t size) {
    webgpuHooks.procs.wgpuCommandEncoderWriteBuffer(commandEncoder, buffer, bufferOffset, data, size);
}
static void wgpuCommandEncoderWriteTimestamp_hook(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    webgpuHooks.procs.wgpuCommandEncoderWriteTimestamp(commandEncoder, querySet, queryIndex);
}
static void wgpuCommandEncoderAddRef_hook(WGPUCommandEncoder commandEncoder) {
    webgpuHooks.procs.wgpuCommandEncoderAddRef(commandEncoder);
}
static void wgpuCommandEncoderRelease_hook(WGPUCommandEncoder commandEncoder) {
    webgpuHooks.procs.wgpuCommandEncoderRelease(commandEncoder);
}
static void wgpuComputePassEncoderDispatchWorkgroups_hook(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) {
    webgpuHooks.procs.wgpuComputePassEncoderDispatchWorkgroups(computePassEncoder, workgroupCountX, workgroupCountY, workgroupCountZ);
}
static void wgpuComputePassEncoderDispatchWorkgroupsIndirect_hook(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    webgpuHooks.procs.wgpuComputePassEncoderDispatchWorkgroupsIndirect(computePassEncoder, indirectBuffer, indirectOffset);
}
static void wgpuComputePassEncoderEnd_hook(WGPUComputePassEncoder computePassEncoder) {
    webgpuHooks.procs.wgpuComputePassEncoderEnd(computePassEncoder);
}
static void wgpuComputePassEncoderInsertDebugMarker_hook(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel) {
    webgpuHooks.procs.wgpuComputePassEncoderInsertDebugMarker(computePassEncoder, markerLabel);
}
static void wgpuComputePassEncoderPopDebugGroup_hook(WGPUComputePassEncoder computePassEncoder) {
    webgpuHooks.procs.wgpuComputePassEncoderPopDebugGroup(computePassEncoder);
}
static void wgpuComputePassEncoderPushDebugGroup_hook(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel) {
    webgpuHooks.procs.wgpuComputePassEncoderPushDebugGroup(computePassEncoder, groupLabel);
}
static void wgpuComputePassEncoderSetBindGroup_hook(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    webgpuHooks.procs.wgpuComputePassEncoderSetBindGroup(computePassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void wgpuComputePassEncoderSetImmediateData_hook(WGPUComputePassEncoder computePassEncoder, uint32_t offset, void const * data, size_t size) {
    webgpuHooks.procs.wgpuComputePassEncoderSetImmediateData(computePassEncoder, offset, data, size);
}
static void wgpuComputePassEncoderSetLabel_hook(WGPUComputePassEncoder computePassEncoder, WGPUStringView label) {
    webgpuHooks.procs.wgpuComputePassEncoderSetLabel(computePassEncoder, label);
}
static void wgpuComputePassEncoderSetPipeline_hook(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) {
    webgpuHooks.procs.wgpuComputePassEncoderSetPipeline(computePassEncoder, pipeline);
}
static void wgpuComputePassEncoderWriteTimestamp_hook(WGPUComputePassEncoder computePassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    webgpuHooks.procs.wgpuComputePassEncoderWriteTimestamp(computePassEncoder, querySet, queryIndex);
}
static void wgpuComputePassEncoderAddRef_hook(WGPUComputePassEncoder computePassEncoder) {
    webgpuHooks.procs.wgpuComputePassEncoderAddRef(computePassEncoder);
}
static void wgpuComputePassEncoderRelease_hook(WGPUComputePassEncoder computePassEncoder) {
    webgpuHooks.procs.wgpuComputePassEncoderRelease(computePassEncoder);
}
static WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout_hook(WGPUComputePipeline computePipeline, uint32_t groupIndex) {
    return webgpuHooks.procs.wgpuComputePipelineGetBindGroupLayout(computePipeline, groupIndex);
}
static void wgpuComputePipelineSetLabel_hook(WGPUComputePipeline computePipeline, WGPUStringView label) {
    webgpuHooks.procs.wgpuComputePipelineSetLabel(computePipeline, label);
}
static void wgpuComputePipelineAddRef_hook(WGPUComputePipeline computePipeline) {
    webgpuHooks.procs.wgpuComputePipelineAddRef(computePipeline);
}
static void wgpuComputePipelineRelease_hook(WGPUComputePipeline computePipeline) {
    webgpuHooks.procs.wgpuComputePipelineRelease(computePipeline);
}
static WGPUBindGroup wgpuDeviceCreateBindGroup_hook(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateBindGroup(device, descriptor);
}
static WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout_hook(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateBindGroupLayout(device, descriptor);
}
static WGPUBuffer wgpuDeviceCreateBuffer_hook(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateBuffer(device, descriptor);
}
static WGPUCommandEncoder wgpuDeviceCreateCommandEncoder_hook(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateCommandEncoder(device, descriptor);
}
static WGPUComputePipeline wgpuDeviceCreateComputePipeline_hook(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateComputePipeline(device, descriptor);
}
static WGPUFuture wgpuDeviceCreateComputePipelineAsync_hook(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuDeviceCreateComputePipelineAsync(device, descriptor, callbackInfo);
}
static WGPUBuffer wgpuDeviceCreateErrorBuffer_hook(WGPUDevice device, WGPUBufferDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateErrorBuffer(device, descriptor);
}
static WGPUExternalTexture wgpuDeviceCreateErrorExternalTexture_hook(WGPUDevice device) {
    return webgpuHooks.procs.wgpuDeviceCreateErrorExternalTexture(device);
}
static WGPUShaderModule wgpuDeviceCreateErrorShaderModule_hook(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor, WGPUStringView errorMessage) {
    return webgpuHooks.procs.wgpuDeviceCreateErrorShaderModule(device, descriptor, errorMessage);
}
static WGPUTexture wgpuDeviceCreateErrorTexture_hook(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateErrorTexture(device, descriptor);
}
static WGPUExternalTexture wgpuDeviceCreateExternalTexture_hook(WGPUDevice device, WGPUExternalTextureDescriptor const * externalTextureDescriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateExternalTexture(device, externalTextureDescriptor);
}
static WGPUPipelineLayout wgpuDeviceCreatePipelineLayout_hook(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreatePipelineLayout(device, descriptor);
}
static WGPUQuerySet wgpuDeviceCreateQuerySet_hook(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateQuerySet(device, descriptor);
}
static WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder_hook(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateRenderBundleEncoder(device, descriptor);
}
static WGPURenderPipeline wgpuDeviceCreateRenderPipeline_hook(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateRenderPipeline(device, descriptor);
}
static WGPUFuture wgpuDeviceCreateRenderPipelineAsync_hook(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuDeviceCreateRenderPipelineAsync(device, descriptor, callbackInfo);
}
static WGPUSampler wgpuDeviceCreateSampler_hook(WGPUDevice device, WGPUSamplerDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateSampler(device, descriptor);
}
static WGPUShaderModule wgpuDeviceCreateShaderModule_hook(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateShaderModule(device, descriptor);
}
static WGPUTexture wgpuDeviceCreateTexture_hook(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceCreateTexture(device, descriptor);
}
static void wgpuDeviceDestroy_hook(WGPUDevice device) {
    webgpuHooks.procs.wgpuDeviceDestroy(device);
}
static void wgpuDeviceForceLoss_hook(WGPUDevice device, WGPUDeviceLostReason type, WGPUStringView message) {
    webgpuHooks.procs.wgpuDeviceForceLoss(device, type, message);
}
static WGPUStatus wgpuDeviceGetAHardwareBufferProperties_hook(WGPUDevice device, void * handle, WGPUAHardwareBufferProperties * properties) {
    return webgpuHooks.procs.wgpuDeviceGetAHardwareBufferProperties(device, handle, properties);
}
static WGPUAdapter wgpuDeviceGetAdapter_hook(WGPUDevice device) {
    return webgpuHooks.procs.wgpuDeviceGetAdapter(device);
}
static WGPUStatus wgpuDeviceGetAdapterInfo_hook(WGPUDevice device, WGPUAdapterInfo * adapterInfo) {
    return webgpuHooks.procs.wgpuDeviceGetAdapterInfo(device, adapterInfo);
}
static void wgpuDeviceGetFeatures_hook(WGPUDevice device, WGPUSupportedFeatures * features) {
    webgpuHooks.procs.wgpuDeviceGetFeatures(device, features);
}
static WGPUStatus wgpuDeviceGetLimits_hook(WGPUDevice device, WGPULimits * limits) {
    return webgpuHooks.procs.wgpuDeviceGetLimits(device, limits);
}
static WGPUFuture wgpuDeviceGetLostFuture_hook(WGPUDevice device) {
    return webgpuHooks.procs.wgpuDeviceGetLostFuture(device);
}
static WGPUQueue wgpuDeviceGetQueue_hook(WGPUDevice device) {
    return webgpuHooks.procs.wgpuDeviceGetQueue(device);
}
static WGPUBool wgpuDeviceHasFeature_hook(WGPUDevice device, WGPUFeatureName feature) {
    return webgpuHooks.procs.wgpuDeviceHasFeature(device, feature);
}
static WGPUSharedBufferMemory wgpuDeviceImportSharedBufferMemory_hook(WGPUDevice device, WGPUSharedBufferMemoryDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceImportSharedBufferMemory(device, descriptor);
}
static WGPUSharedFence wgpuDeviceImportSharedFence_hook(WGPUDevice device, WGPUSharedFenceDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceImportSharedFence(device, descriptor);
}
static WGPUSharedTextureMemory wgpuDeviceImportSharedTextureMemory_hook(WGPUDevice device, WGPUSharedTextureMemoryDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuDeviceImportSharedTextureMemory(device, descriptor);
}
static void wgpuDeviceInjectError_hook(WGPUDevice device, WGPUErrorType type, WGPUStringView message) {
    webgpuHooks.procs.wgpuDeviceInjectError(device, type, message);
}
static WGPUFuture wgpuDevicePopErrorScope_hook(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuDevicePopErrorScope(device, callbackInfo);
}
static void wgpuDevicePushErrorScope_hook(WGPUDevice device, WGPUErrorFilter filter) {
    webgpuHooks.procs.wgpuDevicePushErrorScope(device, filter);
}
static void wgpuDeviceSetLabel_hook(WGPUDevice device, WGPUStringView label) {
    webgpuHooks.procs.wgpuDeviceSetLabel(device, label);
}
static void wgpuDeviceSetLoggingCallback_hook(WGPUDevice device, WGPULoggingCallbackInfo callbackInfo) {
    webgpuHooks.procs.wgpuDeviceSetLoggingCallback(device, callbackInfo);
}
static void wgpuDeviceTick_hook(WGPUDevice device) {
    webgpuHooks.procs.wgpuDeviceTick(device);
}
static void wgpuDeviceValidateTextureDescriptor_hook(WGPUDevice device, WGPUTextureDescriptor const * descriptor) {
    webgpuHooks.procs.wgpuDeviceValidateTextureDescriptor(device, descriptor);
}
static void wgpuDeviceAddRef_hook(WGPUDevice device) {
    webgpuHooks.procs.wgpuDeviceAddRef(device);
}
static void wgpuDeviceRelease_hook(WGPUDevice device) {
    webgpuHooks.procs.wgpuDeviceRelease(device);
}
static void wgpuExternalTextureDestroy_hook(WGPUExternalTexture externalTexture) {
    webgpuHooks.procs.wgpuExternalTextureDestroy(externalTexture);
}
static void wgpuExternalTextureExpire_hook(WGPUExternalTexture externalTexture) {
    webgpuHooks.procs.wgpuExternalTextureExpire(externalTexture);
}
static void wgpuExternalTextureRefresh_hook(WGPUExternalTexture externalTexture) {
    webgpuHooks.procs.wgpuExternalTextureRefresh(externalTexture);
}
static void wgpuExternalTextureSetLabel_hook(WGPUExternalTexture externalTexture, WGPUStringView label) {
    webgpuHooks.procs.wgpuExternalTextureSetLabel(externalTexture, label);
}
static void wgpuExternalTextureAddRef_hook(WGPUExternalTexture externalTexture) {
    webgpuHooks.procs.wgpuExternalTextureAddRef(externalTexture);
}
static void wgpuExternalTextureRelease_hook(WGPUExternalTexture externalTexture) {
    webgpuHooks.procs.wgpuExternalTextureRelease(externalTexture);
}
static WGPUSurface wgpuInstanceCreateSurface_hook(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuInstanceCreateSurface(instance, descriptor);
}
static WGPUStatus wgpuInstanceGetWGSLLanguageFeatures_hook(WGPUInstance instance, WGPUSupportedWGSLLanguageFeatures * features) {
    return webgpuHooks.procs.wgpuInstanceGetWGSLLanguageFeatures(instance, features);
}
static WGPUBool wgpuInstanceHasWGSLLanguageFeature_hook(WGPUInstance instance, WGPUWGSLLanguageFeatureName feature) {
    return webgpuHooks.procs.wgpuInstanceHasWGSLLanguageFeature(instance, feature);
}
static void wgpuInstanceProcessEvents_hook(WGPUInstance instance) {
    webgpuHooks.procs.wgpuInstanceProcessEvents(instance);
}
static WGPUFuture wgpuInstanceRequestAdapter_hook(WGPUInstance instance, WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuInstanceRequestAdapter(instance, options, callbackInfo);
}
static WGPUWaitStatus wgpuInstanceWaitAny_hook(WGPUInstance instance, size_t futureCount, WGPUFutureWaitInfo * futures, uint64_t timeoutNS) {
    return webgpuHooks.procs.wgpuInstanceWaitAny(instance, futureCount, futures, timeoutNS);
}
static void wgpuInstanceAddRef_hook(WGPUInstance instance) {
    webgpuHooks.procs.wgpuInstanceAddRef(instance);
}
static void wgpuPipelineLayoutSetLabel_hook(WGPUPipelineLayout pipelineLayout, WGPUStringView label) {
    webgpuHooks.procs.wgpuPipelineLayoutSetLabel(pipelineLayout, label);
}
static void wgpuPipelineLayoutAddRef_hook(WGPUPipelineLayout pipelineLayout) {
    webgpuHooks.procs.wgpuPipelineLayoutAddRef(pipelineLayout);
}
static void wgpuPipelineLayoutRelease_hook(WGPUPipelineLayout pipelineLayout) {
    webgpuHooks.procs.wgpuPipelineLayoutRelease(pipelineLayout);
}
static void wgpuQuerySetDestroy_hook(WGPUQuerySet querySet) {
    webgpuHooks.procs.wgpuQuerySetDestroy(querySet);
}
static uint32_t wgpuQuerySetGetCount_hook(WGPUQuerySet querySet) {
    return webgpuHooks.procs.wgpuQuerySetGetCount(querySet);
}
static WGPUQueryType wgpuQuerySetGetType_hook(WGPUQuerySet querySet) {
    return webgpuHooks.procs.wgpuQuerySetGetType(querySet);
}
static void wgpuQuerySetSetLabel_hook(WGPUQuerySet querySet, WGPUStringView label) {
    webgpuHooks.procs.wgpuQuerySetSetLabel(querySet, label);
}
static void wgpuQuerySetAddRef_hook(WGPUQuerySet querySet) {
    webgpuHooks.procs.wgpuQuerySetAddRef(querySet);
}
static void wgpuQuerySetRelease_hook(WGPUQuerySet querySet) {
    webgpuHooks.procs.wgpuQuerySetRelease(querySet);
}
static void wgpuQueueCopyExternalTextureForBrowser_hook(WGPUQueue queue, WGPUImageCopyExternalTexture const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    webgpuHooks.procs.wgpuQueueCopyExternalTextureForBrowser(queue, source, destination, copySize, options);
}
static void wgpuQueueCopyTextureForBrowser_hook(WGPUQueue queue, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize, WGPUCopyTextureForBrowserOptions const * options) {
    webgpuHooks.procs.wgpuQueueCopyTextureForBrowser(queue, source, destination, copySize, options);
}
static WGPUFuture wgpuQueueOnSubmittedWorkDone_hook(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuQueueOnSubmittedWorkDone(queue, callbackInfo);
}
static void wgpuQueueSetLabel_hook(WGPUQueue queue, WGPUStringView label) {
    webgpuHooks.procs.wgpuQueueSetLabel(queue, label);
}
static void wgpuQueueSubmit_hook(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) {
    webgpuHooks.procs.wgpuQueueSubmit(queue, commandCount, commands);
}
static void wgpuQueueWriteBuffer_hook(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) {
    webgpuHooks.procs.wgpuQueueWriteBuffer(queue, buffer, bufferOffset, data, size);
}
static void wgpuQueueWriteTexture_hook(WGPUQueue queue, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) {
    webgpuHooks.procs.wgpuQueueWriteTexture(queue, destination, data, dataSize, dataLayout, writeSize);
}
static void wgpuQueueAddRef_hook(WGPUQueue queue) {
    webgpuHooks.procs.wgpuQueueAddRef(queue);
}
static void wgpuQueueRelease_hook(WGPUQueue queue) {
    webgpuHooks.procs.wgpuQueueRelease(queue);
}
static void wgpuRenderBundleSetLabel_hook(WGPURenderBundle renderBundle, WGPUStringView label) {
    webgpuHooks.procs.wgpuRenderBundleSetLabel(renderBundle, label);
}
static void wgpuRenderBundleAddRef_hook(WGPURenderBundle renderBundle) {
    webgpuHooks.procs.wgpuRenderBundleAddRef(renderBundle);
}
static void wgpuRenderBundleRelease_hook(WGPURenderBundle renderBundle) {
    webgpuHooks.procs.wgpuRenderBundleRelease(renderBundle);
}
static void wgpuRenderBundleEncoderDraw_hook(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    webgpuHooks.procs.wgpuRenderBundleEncoderDraw(renderBundleEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void wgpuRenderBundleEncoderDrawIndexed_hook(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    webgpuHooks.procs.wgpuRenderBundleEncoderDrawIndexed(renderBundleEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void wgpuRenderBundleEncoderDrawIndexedIndirect_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    webgpuHooks.procs.wgpuRenderBundleEncoderDrawIndexedIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static void wgpuRenderBundleEncoderDrawIndirect_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    webgpuHooks.procs.wgpuRenderBundleEncoderDrawIndirect(renderBundleEncoder, indirectBuffer, indirectOffset);
}
static WGPURenderBundle wgpuRenderBundleEncoderFinish_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderBundleDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuRenderBundleEncoderFinish(renderBundleEncoder, descriptor);
}
static void wgpuRenderBundleEncoderInsertDebugMarker_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView markerLabel) {
    webgpuHooks.procs.wgpuRenderBundleEncoderInsertDebugMarker(renderBundleEncoder, markerLabel);
}
static void wgpuRenderBundleEncoderPopDebugGroup_hook(WGPURenderBundleEncoder renderBundleEncoder) {
    webgpuHooks.procs.wgpuRenderBundleEncoderPopDebugGroup(renderBundleEncoder);
}
static void wgpuRenderBundleEncoderPushDebugGroup_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView groupLabel) {
    webgpuHooks.procs.wgpuRenderBundleEncoderPushDebugGroup(renderBundleEncoder, groupLabel);
}
static void wgpuRenderBundleEncoderSetBindGroup_hook(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    webgpuHooks.procs.wgpuRenderBundleEncoderSetBindGroup(renderBundleEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void wgpuRenderBundleEncoderSetImmediateData_hook(WGPURenderBundleEncoder renderBundleEncoder, uint32_t offset, void const * data, size_t size) {
    webgpuHooks.procs.wgpuRenderBundleEncoderSetImmediateData(renderBundleEncoder, offset, data, size);
}
static void wgpuRenderBundleEncoderSetIndexBuffer_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    webgpuHooks.procs.wgpuRenderBundleEncoderSetIndexBuffer(renderBundleEncoder, buffer, format, offset, size);
}
static void wgpuRenderBundleEncoderSetLabel_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView label) {
    webgpuHooks.procs.wgpuRenderBundleEncoderSetLabel(renderBundleEncoder, label);
}
static void wgpuRenderBundleEncoderSetPipeline_hook(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) {
    webgpuHooks.procs.wgpuRenderBundleEncoderSetPipeline(renderBundleEncoder, pipeline);
}
static void wgpuRenderBundleEncoderSetVertexBuffer_hook(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    webgpuHooks.procs.wgpuRenderBundleEncoderSetVertexBuffer(renderBundleEncoder, slot, buffer, offset, size);
}
static void wgpuRenderBundleEncoderAddRef_hook(WGPURenderBundleEncoder renderBundleEncoder) {
    webgpuHooks.procs.wgpuRenderBundleEncoderAddRef(renderBundleEncoder);
}
static void wgpuRenderBundleEncoderRelease_hook(WGPURenderBundleEncoder renderBundleEncoder) {
    webgpuHooks.procs.wgpuRenderBundleEncoderRelease(renderBundleEncoder);
}
static void wgpuRenderPassEncoderBeginOcclusionQuery_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) {
    webgpuHooks.procs.wgpuRenderPassEncoderBeginOcclusionQuery(renderPassEncoder, queryIndex);
}
static void wgpuRenderPassEncoderDraw_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
    webgpuHooks.procs.wgpuRenderPassEncoderDraw(renderPassEncoder, vertexCount, instanceCount, firstVertex, firstInstance);
}
static void wgpuRenderPassEncoderDrawIndexed_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) {
    webgpuHooks.procs.wgpuRenderPassEncoderDrawIndexed(renderPassEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}
static void wgpuRenderPassEncoderDrawIndexedIndirect_hook(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    webgpuHooks.procs.wgpuRenderPassEncoderDrawIndexedIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void wgpuRenderPassEncoderDrawIndirect_hook(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) {
    webgpuHooks.procs.wgpuRenderPassEncoderDrawIndirect(renderPassEncoder, indirectBuffer, indirectOffset);
}
static void wgpuRenderPassEncoderEnd_hook(WGPURenderPassEncoder renderPassEncoder) {
    webgpuHooks.procs.wgpuRenderPassEncoderEnd(renderPassEncoder);
}
static void wgpuRenderPassEncoderEndOcclusionQuery_hook(WGPURenderPassEncoder renderPassEncoder) {
    webgpuHooks.procs.wgpuRenderPassEncoderEndOcclusionQuery(renderPassEncoder);
}
static void wgpuRenderPassEncoderExecuteBundles_hook(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) {
    webgpuHooks.procs.wgpuRenderPassEncoderExecuteBundles(renderPassEncoder, bundleCount, bundles);
}
static void wgpuRenderPassEncoderInsertDebugMarker_hook(WGPURenderPassEncoder renderPassEncoder, WGPUStringView markerLabel) {
    webgpuHooks.procs.wgpuRenderPassEncoderInsertDebugMarker(renderPassEncoder, markerLabel);
}
static void wgpuRenderPassEncoderMultiDrawIndexedIndirect_hook(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) {
    webgpuHooks.procs.wgpuRenderPassEncoderMultiDrawIndexedIndirect(renderPassEncoder, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset);
}
static void wgpuRenderPassEncoderMultiDrawIndirect_hook(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) {
    webgpuHooks.procs.wgpuRenderPassEncoderMultiDrawIndirect(renderPassEncoder, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset);
}
static void wgpuRenderPassEncoderPixelLocalStorageBarrier_hook(WGPURenderPassEncoder renderPassEncoder) {
    webgpuHooks.procs.wgpuRenderPassEncoderPixelLocalStorageBarrier(renderPassEncoder);
}
static void wgpuRenderPassEncoderPopDebugGroup_hook(WGPURenderPassEncoder renderPassEncoder) {
    webgpuHooks.procs.wgpuRenderPassEncoderPopDebugGroup(renderPassEncoder);
}
static void wgpuRenderPassEncoderPushDebugGroup_hook(WGPURenderPassEncoder renderPassEncoder, WGPUStringView groupLabel) {
    webgpuHooks.procs.wgpuRenderPassEncoderPushDebugGroup(renderPassEncoder, groupLabel);
}
static void wgpuRenderPassEncoderSetBindGroup_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetBindGroup(renderPassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}
static void wgpuRenderPassEncoderSetBlendConstant_hook(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetBlendConstant(renderPassEncoder, color);
}
static void wgpuRenderPassEncoderSetImmediateData_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t offset, void const * data, size_t size) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetImmediateData(renderPassEncoder, offset, data, size);
}
static void wgpuRenderPassEncoderSetIndexBuffer_hook(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetIndexBuffer(renderPassEncoder, buffer, format, offset, size);
}
static void wgpuRenderPassEncoderSetLabel_hook(WGPURenderPassEncoder renderPassEncoder, WGPUStringView label) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetLabel(renderPassEncoder, label);
}
static void wgpuRenderPassEncoderSetPipeline_hook(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetPipeline(renderPassEncoder, pipeline);
}
static void wgpuRenderPassEncoderSetScissorRect_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetScissorRect(renderPassEncoder, x, y, width, height);
}
static void wgpuRenderPassEncoderSetStencilReference_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetStencilReference(renderPassEncoder, reference);
}
static void wgpuRenderPassEncoderSetVertexBuffer_hook(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetVertexBuffer(renderPassEncoder, slot, buffer, offset, size);
}
static void wgpuRenderPassEncoderSetViewport_hook(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) {
    webgpuHooks.procs.wgpuRenderPassEncoderSetViewport(renderPassEncoder, x, y, width, height, minDepth, maxDepth);
}
static void wgpuRenderPassEncoderWriteTimestamp_hook(WGPURenderPassEncoder renderPassEncoder, WGPUQuerySet querySet, uint32_t queryIndex) {
    webgpuHooks.procs.wgpuRenderPassEncoderWriteTimestamp(renderPassEncoder, querySet, queryIndex);
}
static void wgpuRenderPassEncoderAddRef_hook(WGPURenderPassEncoder renderPassEncoder) {
    webgpuHooks.procs.wgpuRenderPassEncoderAddRef(renderPassEncoder);
}
static void wgpuRenderPassEncoderRelease_hook(WGPURenderPassEncoder renderPassEncoder) {
    webgpuHooks.procs.wgpuRenderPassEncoderRelease(renderPassEncoder);
}
static WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout_hook(WGPURenderPipeline renderPipeline, uint32_t groupIndex) {
    return webgpuHooks.procs.wgpuRenderPipelineGetBindGroupLayout(renderPipeline, groupIndex);
}
static void wgpuRenderPipelineSetLabel_hook(WGPURenderPipeline renderPipeline, WGPUStringView label) {
    webgpuHooks.procs.wgpuRenderPipelineSetLabel(renderPipeline, label);
}
static void wgpuRenderPipelineAddRef_hook(WGPURenderPipeline renderPipeline) {
    webgpuHooks.procs.wgpuRenderPipelineAddRef(renderPipeline);
}
static void wgpuRenderPipelineRelease_hook(WGPURenderPipeline renderPipeline) {
    webgpuHooks.procs.wgpuRenderPipelineRelease(renderPipeline);
}
static void wgpuSamplerSetLabel_hook(WGPUSampler sampler, WGPUStringView label) {
    webgpuHooks.procs.wgpuSamplerSetLabel(sampler, label);
}
static void wgpuSamplerAddRef_hook(WGPUSampler sampler) {
    webgpuHooks.procs.wgpuSamplerAddRef(sampler);
}
static void wgpuSamplerRelease_hook(WGPUSampler sampler) {
    webgpuHooks.procs.wgpuSamplerRelease(sampler);
}
static WGPUFuture wgpuShaderModuleGetCompilationInfo_hook(WGPUShaderModule shaderModule, WGPUCompilationInfoCallbackInfo callbackInfo) {
    return webgpuHooks.procs.wgpuShaderModuleGetCompilationInfo(shaderModule, callbackInfo);
}
static void wgpuShaderModuleSetLabel_hook(WGPUShaderModule shaderModule, WGPUStringView label) {
    webgpuHooks.procs.wgpuShaderModuleSetLabel(shaderModule, label);
}
static void wgpuShaderModuleAddRef_hook(WGPUShaderModule shaderModule) {
    webgpuHooks.procs.wgpuShaderModuleAddRef(shaderModule);
}
static void wgpuShaderModuleRelease_hook(WGPUShaderModule shaderModule) {
    webgpuHooks.procs.wgpuShaderModuleRelease(shaderModule);
}
static WGPUStatus wgpuSharedBufferMemoryBeginAccess_hook(WGPUSharedBufferMemory sharedBufferMemory, WGPUBuffer buffer, WGPUSharedBufferMemoryBeginAccessDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuSharedBufferMemoryBeginAccess(sharedBufferMemory, buffer, descriptor);
}
static WGPUBuffer wgpuSharedBufferMemoryCreateBuffer_hook(WGPUSharedBufferMemory sharedBufferMemory, WGPUBufferDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuSharedBufferMemoryCreateBuffer(sharedBufferMemory, descriptor);
}
static WGPUStatus wgpuSharedBufferMemoryEndAccess_hook(WGPUSharedBufferMemory sharedBufferMemory, WGPUBuffer buffer, WGPUSharedBufferMemoryEndAccessState * descriptor) {
    return webgpuHooks.procs.wgpuSharedBufferMemoryEndAccess(sharedBufferMemory, buffer, descriptor);
}
static WGPUStatus wgpuSharedBufferMemoryGetProperties_hook(WGPUSharedBufferMemory sharedBufferMemory, WGPUSharedBufferMemoryProperties * properties) {
    return webgpuHooks.procs.wgpuSharedBufferMemoryGetProperties(sharedBufferMemory, properties);
}
static WGPUBool wgpuSharedBufferMemoryIsDeviceLost_hook(WGPUSharedBufferMemory sharedBufferMemory) {
    return webgpuHooks.procs.wgpuSharedBufferMemoryIsDeviceLost(sharedBufferMemory);
}
static void wgpuSharedBufferMemorySetLabel_hook(WGPUSharedBufferMemory sharedBufferMemory, WGPUStringView label) {
    webgpuHooks.procs.wgpuSharedBufferMemorySetLabel(sharedBufferMemory, label);
}
static void wgpuSharedBufferMemoryAddRef_hook(WGPUSharedBufferMemory sharedBufferMemory) {
    webgpuHooks.procs.wgpuSharedBufferMemoryAddRef(sharedBufferMemory);
}
static void wgpuSharedBufferMemoryRelease_hook(WGPUSharedBufferMemory sharedBufferMemory) {
    webgpuHooks.procs.wgpuSharedBufferMemoryRelease(sharedBufferMemory);
}
static void wgpuSharedFenceExportInfo_hook(WGPUSharedFence sharedFence, WGPUSharedFenceExportInfo * info) {
    webgpuHooks.procs.wgpuSharedFenceExportInfo(sharedFence, info);
}
static void wgpuSharedFenceAddRef_hook(WGPUSharedFence sharedFence) {
    webgpuHooks.procs.wgpuSharedFenceAddRef(sharedFence);
}
static void wgpuSharedFenceRelease_hook(WGPUSharedFence sharedFence) {
    webgpuHooks.procs.wgpuSharedFenceRelease(sharedFence);
}
static WGPUStatus wgpuSharedTextureMemoryBeginAccess_hook(WGPUSharedTextureMemory sharedTextureMemory, WGPUTexture texture, WGPUSharedTextureMemoryBeginAccessDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuSharedTextureMemoryBeginAccess(sharedTextureMemory, texture, descriptor);
}
static WGPUTexture wgpuSharedTextureMemoryCreateTexture_hook(WGPUSharedTextureMemory sharedTextureMemory, WGPUTextureDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuSharedTextureMemoryCreateTexture(sharedTextureMemory, descriptor);
}
static WGPUStatus wgpuSharedTextureMemoryEndAccess_hook(WGPUSharedTextureMemory sharedTextureMemory, WGPUTexture texture, WGPUSharedTextureMemoryEndAccessState * descriptor) {
    return webgpuHooks.procs.wgpuSharedTextureMemoryEndAccess(sharedTextureMemory, texture, descriptor);
}
static WGPUStatus wgpuSharedTextureMemoryGetProperties_hook(WGPUSharedTextureMemory sharedTextureMemory, WGPUSharedTextureMemoryProperties * properties) {
    return webgpuHooks.procs.wgpuSharedTextureMemoryGetProperties(sharedTextureMemory, properties);
}
static WGPUBool wgpuSharedTextureMemoryIsDeviceLost_hook(WGPUSharedTextureMemory sharedTextureMemory) {
    return webgpuHooks.procs.wgpuSharedTextureMemoryIsDeviceLost(sharedTextureMemory);
}
static void wgpuSharedTextureMemorySetLabel_hook(WGPUSharedTextureMemory sharedTextureMemory, WGPUStringView label) {
    webgpuHooks.procs.wgpuSharedTextureMemorySetLabel(sharedTextureMemory, label);
}
static void wgpuSharedTextureMemoryAddRef_hook(WGPUSharedTextureMemory sharedTextureMemory) {
    webgpuHooks.procs.wgpuSharedTextureMemoryAddRef(sharedTextureMemory);
}
static void wgpuSharedTextureMemoryRelease_hook(WGPUSharedTextureMemory sharedTextureMemory) {
    webgpuHooks.procs.wgpuSharedTextureMemoryRelease(sharedTextureMemory);
}
static void wgpuSurfaceConfigure_hook(WGPUSurface surface, WGPUSurfaceConfiguration const * config) {
    webgpuHooks.procs.wgpuSurfaceConfigure(surface, config);
}
static WGPUStatus wgpuSurfaceGetCapabilities_hook(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) {
    return webgpuHooks.procs.wgpuSurfaceGetCapabilities(surface, adapter, capabilities);
}
static void wgpuSurfaceGetCurrentTexture_hook(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) {
    webgpuHooks.procs.wgpuSurfaceGetCurrentTexture(surface, surfaceTexture);
}
static void wgpuSurfacePresent_hook(WGPUSurface surface) {
    webgpuHooks.procs.wgpuSurfacePresent(surface);
}
static void wgpuSurfaceSetLabel_hook(WGPUSurface surface, WGPUStringView label) {
    webgpuHooks.procs.wgpuSurfaceSetLabel(surface, label);
}
static void wgpuSurfaceUnconfigure_hook(WGPUSurface surface) {
    webgpuHooks.procs.wgpuSurfaceUnconfigure(surface);
}
static void wgpuSurfaceAddRef_hook(WGPUSurface surface) {
    webgpuHooks.procs.wgpuSurfaceAddRef(surface);
}
static void wgpuSurfaceRelease_hook(WGPUSurface surface) {
    webgpuHooks.procs.wgpuSurfaceRelease(surface);
}
static WGPUTextureView wgpuTextureCreateErrorView_hook(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuTextureCreateErrorView(texture, descriptor);
}
static WGPUTextureView wgpuTextureCreateView_hook(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor) {
    return webgpuHooks.procs.wgpuTextureCreateView(texture, descriptor);
}
static void wgpuTextureDestroy_hook(WGPUTexture texture) {
    webgpuHooks.procs.wgpuTextureDestroy(texture);
}
static uint32_t wgpuTextureGetDepthOrArrayLayers_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetDepthOrArrayLayers(texture);
}
static WGPUTextureDimension wgpuTextureGetDimension_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetDimension(texture);
}
static WGPUTextureFormat wgpuTextureGetFormat_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetFormat(texture);
}
static uint32_t wgpuTextureGetHeight_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetHeight(texture);
}
static uint32_t wgpuTextureGetMipLevelCount_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetMipLevelCount(texture);
}
static uint32_t wgpuTextureGetSampleCount_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetSampleCount(texture);
}
static WGPUTextureUsage wgpuTextureGetUsage_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetUsage(texture);
}
static uint32_t wgpuTextureGetWidth_hook(WGPUTexture texture) {
    return webgpuHooks.procs.wgpuTextureGetWidth(texture);
}
static void wgpuTextureSetLabel_hook(WGPUTexture texture, WGPUStringView label) {
    webgpuHooks.procs.wgpuTextureSetLabel(texture, label);
}
static void wgpuTextureAddRef_hook(WGPUTexture texture) {
    webgpuHooks.procs.wgpuTextureAddRef(texture);
}
static void wgpuTextureRelease_hook(WGPUTexture texture) {
    webgpuHooks.procs.wgpuTextureRelease(texture);
}
static void wgpuTextureViewSetLabel_hook(WGPUTextureView textureView, WGPUStringView label) {
    webgpuHooks.procs.wgpuTextureViewSetLabel(textureView, label);
}
static void wgpuTextureViewAddRef_hook(WGPUTextureView textureView) {
    webgpuHooks.procs.wgpuTextureViewAddRef(textureView);
}
static void wgpuTextureViewRelease_hook(WGPUTextureView textureView) {
    webgpuHooks.procs.wgpuTextureViewRelease(textureView);
}
