#include <udrm/core/connector.h>
#include <udrm/core/crtc.h>
#include <udrm/core/device.h>
#include <udrm/core/driver.h>
#include <udrm/core/encoder.h>
#include <udrm/core/mode.h>
#include <udrm/core/plane.h>
#include <udrm/drivers/bochs.h>
#include <udrm/kernel_api.h>
#include <udrm/uapi/utilities/pci.h>

#define VBE_DISPI_BANK_ADDRESS		   0xA0000
#define VBE_DISPI_BANK_SIZE_KB		   64
#define VBE_DISPI_MAX_XRES			   1024
#define VBE_DISPI_MAX_YRES			   768
#define VBE_DISPI_IOPORT_INDEX		   0x01CE
#define VBE_DISPI_IOPORT_DATA		   0x01CF
#define VBE_DISPI_INDEX_ID			   0x0
#define VBE_DISPI_INDEX_XRES		   0x1
#define VBE_DISPI_INDEX_YRES		   0x2
#define VBE_DISPI_INDEX_BPP			   0x3
#define VBE_DISPI_INDEX_ENABLE		   0x4
#define VBE_DISPI_INDEX_BANK		   0x5
#define VBE_DISPI_INDEX_VIRT_WIDTH	   0x6
#define VBE_DISPI_INDEX_VIRT_HEIGHT	   0x7
#define VBE_DISPI_INDEX_X_OFFSET	   0x8
#define VBE_DISPI_INDEX_Y_OFFSET	   0x9
#define VBE_DISPI_ID0				   0xB0C0
#define VBE_DISPI_ID1				   0xB0C1
#define VBE_DISPI_ID2				   0xB0C2
#define VBE_DISPI_ID3				   0xB0C3
#define VBE_DISPI_ID4				   0xB0C4
#define VBE_DISPI_DISABLED			   0x00
#define VBE_DISPI_ENABLED			   0x01
#define VBE_DISPI_VBE_ENABLED		   0x40
#define VBE_DISPI_NOCLEARMEM		   0x80
#define VBE_DISPI_LFB_PHYSICAL_ADDRESS 0xE0000000

struct udrm_bochs_device
{
	udrm_device_handle dev;
	uapi_handle primary_plane;
	uapi_handle crtc;
	uapi_handle encoder;
	uapi_handle connector;

	volatile void* mmio;

	uapi_u16 xres, yres, yres_virtual;
	uapi_u32 stride;
	uapi_u32 bpp;
};

// TODO: Use uAPI functions once they're done.
static void outw(uapi_u16 value, uapi_u16 port)
{
	asm volatile("outw %w0, %w1" : : "a"(value), "Nd"(port));
}

static void bochs_write(struct udrm_bochs_device* bochs, uapi_u16 port, uapi_u16 value)
{
	outw(port, VBE_DISPI_IOPORT_INDEX);
	outw(value, VBE_DISPI_IOPORT_DATA);
}

static uapi_status udrm_bochs_init(struct udrm_bochs_device* bochs)
{
	bochs->dev = udrm_dev_new();
	bochs->primary_plane = udrm_plane_new();

	// TODO
	// bochs->crtc = udrm_crtc_new();
	// bochs->encoder = udrm_encoder_new();
	// bochs->connector = udrm_connector_new();

	// Disable display.
	bochs_write(bochs, VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);

	// Re-enable display.
	bochs_write(bochs, VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED);

	return UAPI_STATUS_OK;
}

uapi_status udrm_bochs_probe(uapi_pci_handle pci_device)
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

static uapi_status udrm_bochs_fini(struct udrm_bochs_device* bochs)
{
	return UAPI_STATUS_OK;
}

uapi_status udrm_bochs_remove(uapi_pci_handle pci_device)
{
	return udrm_bochs_fini(uapi_kernel_pci_get_ctx(pci_device));
}
