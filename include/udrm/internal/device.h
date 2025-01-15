#pragma once
#include <udrm/kernel_api.h>

struct udrm_device
{
	void* private;			// Driver-specific data.
	uapi_size ref_count;	// Amount of active references to this device.
};
