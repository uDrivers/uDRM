#pragma once

#include <udrm/kernel_api.h>

UAPI_BEGIN_DECLS

// This is the entry point of the uDRM library.
// This function must be called before any drivers are initialized.
uapi_status udrm_initialize();

UAPI_END_DECLS
