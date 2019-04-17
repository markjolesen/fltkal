; vbe_.inc
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

vbe_info_block struc
    vbe_signature               db 4 dup(?)     ; signature 'VESA'
    vbe_version                 dw ?            ; version
    vbe_oem_string_ptr          dd ?            ; OEM string pointer
    vbe_capabilities            db 4 dup(?)     ; graphic capabilities
    vbe_video_mode_ptr          dd ?            ; video mode list pointer
    vbe_total_memory            dw ?            ; number of 64kb memory blocks
    vbe_oem_software_rev        dw ?            ; VBE software revision
    vbe_oem_vendor_name_ptr     dd ?            ; vendor name string pointer
    vbe_oem_product_name_ptr    dd ?            ; product name string pointer
    vbe_oem_product_rev_ptr     dd ?            ; product revision string pointer
    vbe_reserved                db 222 dup(?)   ; reserved
    vbe_oem_data                db 256 dup(?)   ; OEM strings
vbe_info_block ends

vbe_mode_block struc
    mod_attr                    dw ?            ; mode attributes
    mod_wina_attr               db ?            ; window A attributes
    mod_winb_attr               db ?            ; window B attributes
    mod_win_granularity         dw ?            ; window granularity
    mod_win_size                dw ?            ; window size
    mod_wina_seg                dw ?            ; window A start segment
    mod_winb_seg                dw ?            ; window B start segment
    mod_win_func_ptr            dd ?            ; window function pointer
    mod_bytes_per_scan_line     dw ?            ; bytes per scan line
    mod_x_resolution            dw ?            ; horizontal resolution in pixels or chars
    mod_y_resolution            dw ?            ; vertical resolution in pixels or chars
    mod_x_char_size             db ?            ; character cell width in pixels
    mod_y_char_size             db ?            ; character cell height in pixels
    mod_number_of_planes        db ?            ; number of memory planes
    mod_bits_per_pixel          db ?            ; bits per pixel
    mod_number_of_banks         db ?            ; number of banks
    mod_memory_model            db ?            ; memory model type
    mod_bank_size               db ?            ; bank size in KB
    mod_number_of_image_pages   db ?            ; number of image pages
    mod_reserved1               db ?            ; reserved for page function
    mod_red_mask_size           db ?            ; size of direct color red mask in bits
    mod_red_field_position      db ?            ; bit position of lsb of red mask
    mod_green_mask_size         db ?            ; size of direct color green mask in bits
    mod_green_field_position    db ?            ; bit position of lsb of green mask
    mod_blue_mask_size          db ?            ; size of direct color blue mask in bits
    mod_blue_field_position     db ?            ; bit position of lsb of blue mask
    mod_rsvd_mask_size          db ?            ; size of direct color reserved mask in bits
    mod_rsvd_field_position     db ?            ; bit position of lsb of reserved mask
    mod_direct_color_mode_info  db ?            ; direct color mode attributes
    mod_phys_base_ptr           dd ?            ; physical address for flat frame buffer
    mod_off_screen_mem_offset   dd ?            ; start of off screen memory
    mod_off_screen_mem_size     dw ?            ; amount of off screen memoery in 1k units
    mod_reserved2               db 206 dup(?)   ; reserved
vbe_mode_block ends
