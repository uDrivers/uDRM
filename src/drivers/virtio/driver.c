#include <udrm/core/device.h>
#include <udrm/kernel_api.h>

#include "virtio_gpu.h"
#include "virtio_queue.h"

uapi_status udrm_virtio_probe(uapi_pci_handle pci_device)
{
	if (pci_device == NULL)
		return UAPI_STATUS_INVALID_ARGUMENT;

	struct udrm_bochs_device* bochs = uapi_kernel_calloc(1, sizeof(struct udrm_bochs_device));
	uapi_status status;

	status = uapi_kernel_pci_set_ctx(pci_device, bochs);
	if (status != UAPI_STATUS_OK)
		return status;

	// Initialize the Bochs hardware.
	status = udrm_bochs_init(bochs);
	if (status != UAPI_STATUS_OK)
		return status;

	// Init successful, register with DRM.
	status = udrm_dev_register(bochs->dev);
	if (status != UAPI_STATUS_OK)
		return status;

	return UAPI_STATUS_OK;
}

static uapi_status udrm_virtio_fini(struct udrm_virtio_device* bochs)
{
	return UAPI_STATUS_OK;
}

uapi_status udrm_virtio_remove(uapi_pci_handle pci_device)
{
	return udrm_virtio_fini(uapi_kernel_pci_get_ctx(pci_device));
}
