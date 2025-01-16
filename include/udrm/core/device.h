#pragma once

#include <udrm/kernel_api.h>

UAPI_BEGIN_DECLS

typedef void* udrm_device_handle;

// Allocates a new device.
udrm_device_handle udrm_dev_new();

// Destroys a device.
uapi_status udrm_dev_delete(udrm_device_handle dev);

// Registers a device.
uapi_status udrm_dev_register(udrm_device_handle dev);

// Unregisters a device.
uapi_status udrm_dev_unregister(udrm_device_handle dev);

// References a device.
uapi_status udrm_dev_ref(udrm_device_handle dev);

// Unreferences a device.
uapi_status udrm_dev_unref(udrm_device_handle dev);

UAPI_END_DECLS
