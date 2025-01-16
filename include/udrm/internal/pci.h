#pragma once

#include <udrm/kernel_api.h>

uapi_phys_addr udrm_pci_get_bar(uapi_pci_handle device, uapi_u8 idx);
