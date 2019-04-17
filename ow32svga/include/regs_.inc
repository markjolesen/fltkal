; regs_.inc
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

regs32 struc
    r32_edi   dd ?
    r32_esi   dd ? 
    r32_ebp   dd ? 
    r32_resv  dd ?
    r32_ebx   dd ?
    r32_edx   dd ?
    r32_ecx   dd ?
    r32_eax   dd ?
    r32_cpu   dw ?
    r32_es    dw ?
    r32_ds    dw ?
    r32_fs    dw ?
    r32_gs    dw ?
    r32_ip    dw ?
    r32_cs    dw ?
    r32_sp    dw ?
    r32_ss    dw ?
regs32 ends

