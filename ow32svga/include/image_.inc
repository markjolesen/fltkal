; image_.inc
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

image struc
    img_stride                  dd ? ; scan line length in bytes
    img_width                   dd ? ; width of image in pixels
    img_height                  dd ? ; height of image in pixels
    img_line                    dd ? ; array of pointers to begining of each line
    img_handle                  dd ? ; memory block handle
    img_selector                dd ? ; selector
    img_clip_x1                 dd ? ; clip x1
    img_clip_y1                 dd ? ; clip y1
    img_clip_x2                 dd ? ; clip x2
    img_clip_y2                 dd ? ; clip y2
image ends
