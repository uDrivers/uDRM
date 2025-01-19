#include <udrm/internal/pci.h>
#include <udrm/kernel_api.h>
#include <udrm/uapi/utilities/pci.h>

uapi_phys_addr udrm_pci_get_bar(uapi_pci_handle device, uapi_u8 idx)
{
	uapi_phys_addr bar;
	uapi_kernel_pci_cfg_read(device, UAPI_PCI_CFG_BAR(idx), sizeof(uapi_u32), &bar);

	// Memory Space BAR
	if ((bar & 1) == 0)
	{
		const uapi_u8 type = (bar & 0b110) >> 1;
		// If a 64-bit BAR, add the upper bits to the address.
		if (type == 0x2)
		{
			uapi_phys_addr bar1;
			uapi_kernel_pci_cfg_read(device, UAPI_PCI_CFG_BAR(idx + 1), sizeof(uapi_u32), &bar1);
			bar |= (bar1 << 32);
		}
		bar &= ~(uapi_phys_addr)0xF;
	}
	// IO Space BAR
	else
	{
		bar &= 0xFFFFFFFC;
	}

	return bar;
}
