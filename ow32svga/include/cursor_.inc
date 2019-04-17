; cursor_.inc
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

cursor struc
    cur_width                   dd ?
    cur_height                  dd ?
    cur_hot_x                   dd ? 
    cur_hot_y                   dd ? 
    cur_data                    dd ?
cursor ends
