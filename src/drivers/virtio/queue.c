#include <udrm/drivers/virtio.h>

#include "virtio_queue.h"

uapi_phys_addr udrm_virtq_create(struct virtq* queue, uapi_size queue_size)
{
	queue->num = queue_size;

	// Calculate offsets
	const uapi_phys_addr avail_offset = (queue_size * sizeof(struct virtq_desc));
	const uapi_phys_addr used_offset = avail_offset + sizeof(struct virtq_avail) + (queue_size * sizeof(uapi_u16));
	const uapi_phys_addr end_offset =
		used_offset + sizeof(struct virtq_used) + (queue_size * sizeof(struct virtq_used_elem));

	// TODO: Don't assume 0x1000 page size. Needs better API.
	uapi_phys_addr pages = uapi_kernel_allocate_pages(end_offset / 0x1000, 0, ~0ULL);
	uapi_u8* virt_pages =
		uapi_kernel_map(pages, end_offset, UAPI_CACHING_MMIO, UAPI_ACCESS_TYPE_READ | UAPI_ACCESS_TYPE_WRITE);

	queue->desc = (struct virtq_desc*)virt_pages;
	queue->avail = (struct virtq_avail*)(virt_pages + avail_offset);
	queue->used = (struct virtq_used*)(virt_pages + used_offset);

	return pages;
}

void udrm_virtq_submit(struct virtq* queue, void* cmd, uapi_size cmd_size)
{
	// TODO
}
