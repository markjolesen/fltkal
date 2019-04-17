/*
 vbe.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright 
 and related or neighboring rights to ow32svga Library. This work is published 
 from: United States.
*/
#if !defined(__VBE_H__)

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 0)
struct vbe_info_block 
{
    uint8_t  vbe_signature[4];
    uint16_t vbe_version;
    uint32_t vbe_oem_string_ptr;
    uint8_t  vbe_capabilities[4];
    uint32_t vbe_video_mode_ptr;
    uint16_t vbe_total_memory;
    uint16_t vbe_oem_software_rev;
    uint32_t vbe_oem_vendor_name_ptr;
    uint32_t vbe_oem_product_name_ptr;
    uint32_t vbe_oem_product_rev_ptr;
    uint8_t  vbe_reserved[222];
    uint8_t  vbe_oem_data[256];
};
#pragma pack(pop)

#pragma pack(push, 0)
struct vbe_mode_block
{
    uint16_t mod_attr;
    uint8_t  mod_wina_attr;
    uint8_t  mod_winb_attr;
    uint16_t mod_win_granularity;
    uint16_t mod_win_size;
    uint16_t mod_wina_seg;
    uint16_t mod_winb_seg;
    uint32_t mod_win_func_ptr;
    uint16_t mod_bytes_per_scan_line;
    uint16_t mod_x_resolution;
    uint16_t mod_y_resolution;
    uint8_t  mod_x_char_size;
    uint8_t  mod_y_char_size;
    uint8_t  mod_number_of_planes;
    uint8_t  mod_bits_per_pixel;
    uint8_t  mod_number_of_banks;
    uint8_t  mod_memory_model;
    uint8_t  mod_bank_size;
    uint8_t  mod_number_of_image_pages;
    uint8_t  mod_reserved1;
    uint8_t  mod_red_mask_size;
    uint8_t  mod_red_field_position;
    uint8_t  mod_green_mask_size;
    uint8_t  mod_green_field_position;
    uint8_t  mod_blue_mask_size;
    uint8_t  mod_blue_field_position;
    uint8_t  mod_rsvd_mask_size;
    uint8_t  mod_rsvd_field_position;
    uint8_t  mod_direct_color_mode_info;
    uint32_t mod_phys_base_ptr;
    uint32_t mod_off_screen_mem_offset;
    uint16_t mod_off_screen_mem_size;
    uint8_t  mod_reserved2[206];
};
#pragma pack(pop)


extern struct vbe_info_block _vbe_info;

extern int
vbe_get_info_block(
    struct vbe_info_block* info);

extern int
vbe_cleanup();

extern int
vbe_get_mode_block(
    struct vbe_mode_block* info,
    int16_t const mode);

extern int
vbe_query_installed();

extern int
vbe_query_mode(
    size_t const width,
    size_t const height,
    size_t const depth);

extern int16_t
vbe_get_mode();

extern int
vbe_set_mode(
    int16_t const mode);

#ifdef __cplusplus
}
#endif

#define __VBE_H__
#endif
