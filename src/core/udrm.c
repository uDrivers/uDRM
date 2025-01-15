#include <udrm/core/udrm.h>
#include <udrm/kernel_api.h>

#include "device.c"
#include "plane.c"

uapi_status udrm_initialize()
{
	uapi_kernel_log(UAPI_LOG_INFO, "Initialized uDRM.\n");
	return UAPI_STATUS_OK;
}
