#pragma once

#include <udrm/kernel_api.h>

UAPI_BEGIN_DECLS

// Extended Display Identification Data
UAPI_PACKED(struct udrm_edid {
	uapi_u8 header[8];	  // 00 FF FF FF FF FF FF 00

	// Vendor & Product Identification
	uapi_u16 mfr_name;
	uapi_u16 product_id;
	uapi_u32 serial_id;
	uapi_u8 model_week;
	uapi_u8 model_year;

	// EDID Structure Version & Revision
	uapi_u8 version;
	uapi_u8 revision;

	// Basic Display Parameters & Features
	uapi_u8 video_input;
	uapi_u8 h_screen_cm;
	uapi_u8 v_screen_cm;
	uapi_u8 gamma;
	uapi_u8 features;

	// Color Characteristics
	uapi_u8 red_green_low;
	uapi_u8 blue_white_low;
	uapi_u8 red_x;
	uapi_u8 red_y;
	uapi_u8 green_x;
	uapi_u8 green_y;
	uapi_u8 blue_x;
	uapi_u8 blue_y;
	uapi_u8 white_x;
	uapi_u8 white_y;

	// Timings
	struct
	{
		uapi_u8 time_1;
		uapi_u8 time_2;
		uapi_u8 time_mfr;
	} established_timings;

	struct
	{
		uapi_u8 h_resoution;	   // (Horizontal addressable pixels ÷ 8) – 31
		uapi_u8 aspect_and_ref;	   // See 3.19
	} standard_timings[8];

	struct
	{
		// Pixel clock frequency divided by 10000.
		// If 0, don't use `data.pixel`.
		uapi_u16 pix_clock;
		union
		{
			struct
			{
				uapi_u8 h_video_low;
				uapi_u8 h_blank_low;
				uapi_u8 h_video_blank_high;
				uapi_u8 v_video_low;
				uapi_u8 v_blank_low;
				uapi_u8 v_video_blank_high;
				uapi_u8 h_sync_offset_low;
				uapi_u8 h_sync_pulse_width_low;
				uapi_u8 v_sync_offset_pulse_width_low;
				uapi_u8 bit_definitons;	   // High order bits for the previous 4 fields
				uapi_u8 h_video_mm_low;
				uapi_u8 v_video_mm_low;
				uapi_u8 hv_video_mm_high;
				uapi_u8 h_border;
				uapi_u8 v_border;
				uapi_u8 misc;
			} pixel;

			struct
			{
				uapi_u8 _reserved1;
				uapi_u8 tag;
				uapi_u8 _reserved2;
				union
				{
					char serial_number[13];
					char alnum_string[13];
				} data;
			} other;
		} data;
	} detailed_timings[4];

	uapi_u8 extension_block_count;
	uapi_u8 checksum;
})
UAPI_EXPECT_SIZEOF(struct udrm_edid, 0x80);

UAPI_END_DECLS
