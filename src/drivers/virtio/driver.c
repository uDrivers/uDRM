#include <udrm/core/device.h>
#include <udrm/internal/pci.h>
#include <udrm/kernel_api.h>
#include <udrm/uapi/utilities/pci.h>

#include "virtio_gpu.h"
#include "virtio_pci.h"
#include "virtio_queue.h"

struct udrm_virtio_device
{
	udrm_device_handle dev;
	uapi_handle primary_plane;
	uapi_handle crtc;
	uapi_handle encoder;
	uapi_handle connector;

	struct virtq command_queue;
	struct virtq cursor_queue;
};

uapi_status udrm_virtio_probe(uapi_pci_handle pci_device)
{
	if (pci_device == NULL)
		return UAPI_STATUS_INVALID_ARGUMENT;

	struct udrm_virtio_device* virtio = uapi_kernel_calloc(1, sizeof(struct udrm_virtio_device));
	uapi_status status;

	status = uapi_kernel_pci_set_ctx(pci_device, virtio);
	if (status != UAPI_STATUS_OK)
		return status;

	// Find PCI CAPs.
	volatile struct virtio_pci_common_cfg* common_cfg = NULL;
	uapi_u64 cap_ptr, cap_id;
	uapi_kernel_pci_cfg_read(pci_device, UAPI_PCI_CFG_CAPABILITIES, sizeof(uapi_u8), &cap_ptr);
	do
	{
		uapi_kernel_pci_cfg_read(pci_device, cap_ptr + 0, sizeof(uapi_u8), &cap_id);
		uapi_kernel_pci_cfg_read(pci_device, cap_ptr + 1, sizeof(uapi_u8), &cap_ptr);
		cap_ptr &= 0xFC;

		if (cap_id != 0x09)
			continue;

#define VIRTIO_READ_PCI_CAP_FIELD(target, field) \
	uapi_kernel_pci_cfg_read(pci_device, cap_ptr + offsetof(struct virtio_pci_cap, field), sizeof(target.field), \
							 (uapi_u64*)&target.field)

		struct virtio_pci_cap pci_cap;
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, cap_vndr);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, cap_next);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, cap_len);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, cfg_type);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, bar);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, id);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, offset);
		VIRTIO_READ_PCI_CAP_FIELD(pci_cap, length);

		uapi_phys_addr bar = udrm_pci_get_bar(pci_device, pci_cap.bar);

		void* addr = uapi_kernel_map(bar + pci_cap.offset, pci_cap.length, UAPI_CACHING_MMIO,
									 UAPI_ACCESS_TYPE_READ | UAPI_ACCESS_TYPE_WRITE);

		if (pci_cap.cfg_type == VIRTIO_PCI_CAP_COMMON_CFG)
			common_cfg = addr;
	} while (cap_ptr != 0);

	// Setup virtqueues.
	common_cfg->queue_select = 0;
	common_cfg->queue_desc = udrm_virtq_create(&virtio->command_queue, common_cfg->queue_size);

	// Init successful, register with DRM.
	status = udrm_dev_register(virtio->dev);
	if (status != UAPI_STATUS_OK)
		return status;

	return UAPI_STATUS_OK;
}

static uapi_status udrm_virtio_fini(struct udrm_virtio_device* virtio)
{
	return UAPI_STATUS_OK;
}

uapi_status udrm_virtio_remove(uapi_pci_handle pci_device)
{
	return udrm_virtio_fini(uapi_kernel_pci_get_ctx(pci_device));
}
