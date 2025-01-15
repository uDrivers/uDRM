#include <udrm/core/plane.h>
#include <udrm/kernel_api.h>

uapi_handle udrm_plane_new()
{
	return uapi_kernel_calloc(1, sizeof(struct udrm_plane));
}
