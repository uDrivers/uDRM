#pragma once
#include <udrm/kernel_api.h>

#define VIRTIO_PCI_CAP_COMMON_CFG		 1
#define VIRTIO_PCI_CAP_NOTIFY_CFG		 2
#define VIRTIO_PCI_CAP_ISR_CFG			 3
#define VIRTIO_PCI_CAP_DEVICE_CFG		 4
#define VIRTIO_PCI_CAP_PCI_CFG			 5
#define VIRTIO_PCI_CAP_SHARED_MEMORY_CFG 8
#define VIRTIO_PCI_CAP_VENDOR_CFG		 9

struct virtio_pci_cap
{
	uapi_u8 cap_vndr;
	uapi_u8 cap_next;
	uapi_u8 cap_len;
	uapi_u8 cfg_type;
	uapi_u8 bar;
	uapi_u8 id;
	uapi_u8 padding[2];
	uapi_le32 offset;
	uapi_le32 length;
};

struct virtio_pci_cap64
{
	struct virtio_pci_cap cap;
	uapi_u32 offset_hi;
	uapi_u32 length_hi;
};

struct virtio_pci_common_cfg
{
	uapi_le32 device_feature_select;
	uapi_le32 device_feature;
	uapi_le32 driver_feature_select;
	uapi_le32 driver_feature;
	uapi_le16 config_msix_vector;
	uapi_le16 num_queues;
	uapi_u8 device_status;
	uapi_u8 config_generation;
	uapi_le16 queue_select;
	uapi_le16 queue_size;
	uapi_le16 queue_msix_vector;
	uapi_le16 queue_enable;
	uapi_le16 queue_notify_off;
	uapi_le64 queue_desc;
	uapi_le64 queue_driver;
	uapi_le64 queue_device;
	uapi_le16 queue_notif_config_data;
	uapi_le16 queue_reset;
	uapi_le16 admin_queue_index;
	uapi_le16 admin_queue_num;
};
