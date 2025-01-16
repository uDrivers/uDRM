#pragma once

#include <udrm/kernel_api.h>

UAPI_BEGIN_DECLS

typedef void* udrm_plane_handle;

// Creates a new plane.
udrm_plane_handle udrm_plane_new();

UAPI_END_DECLS
