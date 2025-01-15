#pragma once

#include <udrm/kernel_api.h>

UAPI_BEGIN_DECLS

uapi_status udrm_bochs_probe(uapi_pci_handle pci_device);
uapi_status udrm_bochs_remove(uapi_pci_handle pci_device);

UAPI_END_DECLS
