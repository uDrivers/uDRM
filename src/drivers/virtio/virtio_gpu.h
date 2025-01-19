#pragma once
#include <udrm/kernel_api.h>

#define VIRTIO_GPU_EVENT_DISPLAY (1 << 0)

#define VIRTIO_GPU_F_VIRGL		   (1 << 0)
#define VIRTIO_GPU_F_EDID		   (1 << 1)
#define VIRTIO_GPU_F_RESOURCE_UUID (1 << 2)
#define VIRTIO_GPU_F_RESOURCE_BLOB (1 << 3)
#define VIRTIO_GPU_F_CONTEXT_INIT  (1 << 4)

struct virtio_gpu_config
{
	uapi_le32 events_read;
	uapi_le32 events_clear;
	uapi_le32 num_scanouts;
	uapi_le32 num_capsets;
};

enum virtio_gpu_shm_id
{
	VIRTIO_GPU_SHM_ID_UNDEFINED = 0,
	VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1,
};

enum virtio_gpu_ctrl_type
{
	/* 2d commands */
	VIRTIO_GPU_CMD_GET_DISPLAY_INFO = 0x0100,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_2D,
	VIRTIO_GPU_CMD_RESOURCE_UNREF,
	VIRTIO_GPU_CMD_SET_SCANOUT,
	VIRTIO_GPU_CMD_RESOURCE_FLUSH,
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_2D,
	VIRTIO_GPU_CMD_RESOURCE_ATTACH_BACKING,
	VIRTIO_GPU_CMD_RESOURCE_DETACH_BACKING,
	VIRTIO_GPU_CMD_GET_CAPSET_INFO,
	VIRTIO_GPU_CMD_GET_CAPSET,
	VIRTIO_GPU_CMD_GET_EDID,
	VIRTIO_GPU_CMD_RESOURCE_ASSIGN_UUID,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_BLOB,
	VIRTIO_GPU_CMD_SET_SCANOUT_BLOB,
	/* 3d commands */
	VIRTIO_GPU_CMD_CTX_CREATE = 0x0200,
	VIRTIO_GPU_CMD_CTX_DESTROY,
	VIRTIO_GPU_CMD_CTX_ATTACH_RESOURCE,
	VIRTIO_GPU_CMD_CTX_DETACH_RESOURCE,
	VIRTIO_GPU_CMD_RESOURCE_CREATE_3D,
	VIRTIO_GPU_CMD_TRANSFER_TO_HOST_3D,
	VIRTIO_GPU_CMD_TRANSFER_FROM_HOST_3D,
	VIRTIO_GPU_CMD_SUBMIT_3D,
	VIRTIO_GPU_CMD_RESOURCE_MAP_BLOB,
	VIRTIO_GPU_CMD_RESOURCE_UNMAP_BLOB,
	/* cursor commands */
	VIRTIO_GPU_CMD_UPDATE_CURSOR = 0x0300,
	VIRTIO_GPU_CMD_MOVE_CURSOR,
	/* success responses */
	VIRTIO_GPU_RESP_OK_NODATA = 0x1100,
	VIRTIO_GPU_RESP_OK_DISPLAY_INFO,
	VIRTIO_GPU_RESP_OK_CAPSET_INFO,
	VIRTIO_GPU_RESP_OK_CAPSET,
	VIRTIO_GPU_RESP_OK_EDID,
	VIRTIO_GPU_RESP_OK_RESOURCE_UUID,
	VIRTIO_GPU_RESP_OK_MAP_INFO,
	/* error responses */
	VIRTIO_GPU_RESP_ERR_UNSPEC = 0x1200,
	VIRTIO_GPU_RESP_ERR_OUT_OF_MEMORY,
	VIRTIO_GPU_RESP_ERR_INVALID_SCANOUT_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_RESOURCE_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_CONTEXT_ID,
	VIRTIO_GPU_RESP_ERR_INVALID_PARAMETER,
};

#define VIRTIO_GPU_FLAG_FENCE		  (1 << 0)
#define VIRTIO_GPU_FLAG_INFO_RING_IDX (1 << 1)

struct virtio_gpu_ctrl_hdr
{
	uapi_le32 type;
	uapi_le32 flags;
	uapi_le64 fence_id;
	uapi_le32 ctx_id;
	uapi_u8 ring_idx;
	uapi_u8 padding[3];
};

#define VIRTIO_GPU_MAX_SCANOUTS 16

struct virtio_gpu_rect
{
	uapi_le32 x;
	uapi_le32 y;
	uapi_le32 width;
	uapi_le32 height;
};

struct virtio_gpu_resp_display_info
{
	struct virtio_gpu_ctrl_hdr hdr;
	struct virtio_gpu_display_one
	{
		struct virtio_gpu_rect r;
		uapi_le32 enabled;
		uapi_le32 flags;
	} pmodes[VIRTIO_GPU_MAX_SCANOUTS];
};

struct virtio_gpu_get_edid
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 scanout;
	uapi_le32 padding;
};

struct virtio_gpu_resp_edid
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 size;
	uapi_le32 padding;
	uapi_u8 edid[1024];
};

enum virtio_gpu_formats
{
	VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM = 1,
	VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM = 2,
	VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM = 3,
	VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM = 4,
	VIRTIO_GPU_FORMAT_R8G8B8A8_UNORM = 67,
	VIRTIO_GPU_FORMAT_X8B8G8R8_UNORM = 68,
	VIRTIO_GPU_FORMAT_A8B8G8R8_UNORM = 121,
	VIRTIO_GPU_FORMAT_R8G8B8X8_UNORM = 134,
};

struct virtio_gpu_resource_create_2d
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 format;
	uapi_le32 width;
	uapi_le32 height;
};

struct virtio_gpu_resource_unref
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 padding;
};

struct virtio_gpu_set_scanout
{
	struct virtio_gpu_ctrl_hdr hdr;
	struct virtio_gpu_rect r;
	uapi_le32 scanout_id;
	uapi_le32 resource_id;
};

struct virtio_gpu_resource_flush
{
	struct virtio_gpu_ctrl_hdr hdr;
	struct virtio_gpu_rect r;
	uapi_le32 resource_id;
	uapi_le32 padding;
};

struct virtio_gpu_transfer_to_host_2d
{
	struct virtio_gpu_ctrl_hdr hdr;
	struct virtio_gpu_rect r;
	uapi_le64 offset;
	uapi_le32 resource_id;
	uapi_le32 padding;
};

struct virtio_gpu_resource_attach_backing
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 nr_entries;
};

struct virtio_gpu_mem_entry
{
	uapi_le64 addr;
	uapi_le32 length;
	uapi_le32 padding;
};

struct virtio_gpu_resource_detach_backing
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 padding;
};

struct virtio_gpu_get_capset_info
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 capset_index;
	uapi_le32 padding;
};

#define VIRTIO_GPU_CAPSET_VIRGL		   1
#define VIRTIO_GPU_CAPSET_VIRGL2	   2
#define VIRTIO_GPU_CAPSET_GFXSTREAM	   3
#define VIRTIO_GPU_CAPSET_VENUS		   4
#define VIRTIO_GPU_CAPSET_CROSS_DOMAIN 5

struct virtio_gpu_resp_capset_info
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 capset_id;
	uapi_le32 capset_max_version;
	uapi_le32 capset_max_size;
	uapi_le32 padding;
};

struct virtio_gpu_get_capset
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 capset_id;
	uapi_le32 capset_version;
};

struct virtio_gpu_resp_capset
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_u8 capset_data[];
};

struct virtio_gpu_resource_assign_uuid
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 padding;
};

struct virtio_gpu_resp_resource_uuid
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_u8 uuid[16];
};

#define VIRTIO_GPU_BLOB_MEM_GUEST			  0x0001
#define VIRTIO_GPU_BLOB_MEM_HOST3D			  0x0002
#define VIRTIO_GPU_BLOB_MEM_HOST3D_GUEST	  0x0003
#define VIRTIO_GPU_BLOB_FLAG_USE_MAPPABLE	  0x0001
#define VIRTIO_GPU_BLOB_FLAG_USE_SHAREABLE	  0x0002
#define VIRTIO_GPU_BLOB_FLAG_USE_CROSS_DEVICE 0x0004

struct virtio_gpu_resource_create_blob
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 blob_mem;
	uapi_le32 blob_flags;
	uapi_le32 nr_entries;
	uapi_le64 blob_id;
	uapi_le64 size;
};

struct virtio_gpu_set_scanout_blob
{
	struct virtio_gpu_ctrl_hdr hdr;
	struct virtio_gpu_rect r;
	uapi_le32 scanout_id;
	uapi_le32 resource_id;
	uapi_le32 width;
	uapi_le32 height;
	uapi_le32 format;
	uapi_le32 padding;
	uapi_le32 strides[4];
	uapi_le32 offsets[4];
};

#define VIRTIO_GPU_CONTEXT_INIT_CAPSET_ID_MASK 0x000000ff;

struct virtio_gpu_ctx_create
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 nlen;
	uapi_le32 context_init;
	char debug_name[64];
};

struct virtio_gpu_resource_map_blob
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 padding;
	uapi_le64 offset;
};

#define VIRTIO_GPU_MAP_CACHE_MASK	  0x0f
#define VIRTIO_GPU_MAP_CACHE_NONE	  0x00
#define VIRTIO_GPU_MAP_CACHE_CACHED	  0x01
#define VIRTIO_GPU_MAP_CACHE_UNCACHED 0x02
#define VIRTIO_GPU_MAP_CACHE_WC		  0x03

struct virtio_gpu_resp_map_info
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_u32 map_info;
	uapi_u32 padding;
};

struct virtio_gpu_resource_unmap_blob
{
	struct virtio_gpu_ctrl_hdr hdr;
	uapi_le32 resource_id;
	uapi_le32 padding;
};

struct virtio_gpu_cursor_pos
{
	uapi_le32 scanout_id;
	uapi_le32 x;
	uapi_le32 y;
	uapi_le32 padding;
};

struct virtio_gpu_update_cursor
{
	struct virtio_gpu_ctrl_hdr hdr;
	struct virtio_gpu_cursor_pos pos;
	uapi_le32 resource_id;
	uapi_le32 hot_x;
	uapi_le32 hot_y;
	uapi_le32 padding;
};
