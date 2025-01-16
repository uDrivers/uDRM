#include <udrm/core/plane.h>
#include <udrm/internal/plane.h>
#include <udrm/kernel_api.h>

udrm_plane_handle udrm_plane_new()
{
	return uapi_kernel_calloc(1, sizeof(struct udrm_plane));
}
