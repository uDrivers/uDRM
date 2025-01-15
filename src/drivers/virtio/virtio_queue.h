#pragma once
#include <udrm/kernel_api.h>

#define VIRTQ_DESC_F_NEXT		   1
#define VIRTQ_DESC_F_WRITE		   2
#define VIRTQ_DESC_F_INDIRECT	   4
#define VIRTQ_USED_F_NO_NOTIFY	   1
#define VIRTQ_AVAIL_F_NO_INTERRUPT 1
#define VIRTIO_F_ANY_LAYOUT		   27
#define VIRTIO_F_INDIRECT_DESC	   28
#define VIRTIO_F_EVENT_IDX		   29

struct virtq_desc
{
	uapi_le64 addr;
	uapi_le32 len;
	uapi_le16 flags;
	uapi_le16 next;
};

struct virtq_avail
{
	uapi_le16 flags;
	uapi_le16 idx;
	uapi_le16 ring[];
};

struct virtq_used_elem
{
	uapi_le32 id;
	uapi_le32 len;
};

struct virtq_used
{
	uapi_le16 flags;
	uapi_le16 idx;
	struct virtq_used_elem ring[];
};

struct virtq
{
	unsigned int num;

	struct virtq_desc* desc;
	struct virtq_avail* avail;
	struct virtq_used* used;
};

static inline int virtq_need_event(uint16_t event_idx, uint16_t new_idx, uint16_t old_idx)
{
	return (uint16_t)(new_idx - event_idx - 1) < (uint16_t)(new_idx - old_idx);
}

static inline uapi_le16* virtq_used_event(struct virtq* vq)
{
	return &vq->avail->ring[vq->num];
}

static inline uapi_le16* virtq_avail_event(struct virtq* vq)
{
	return (uapi_le16*)&vq->used->ring[vq->num];
}
