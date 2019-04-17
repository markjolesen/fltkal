; bitmap_.asm
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

include image_.inc
include clip_.inc
include bitmap_.inc

.model flat

.code

assume ds:_DATA, es:_DATA, ss:_DATA, cs:_TEXT

extrn clip_image:proc

; copy a 1bpp bitmap into an image
;
; inputs:
;   eax image
;   edx dest x
;   ebx dest y
;   ecx bitmap
;   [ebp + 8] color
;
; outputs:
;   none
;
; destroys:
;   none
public bitmap_1bpp_blt_
bitmap_1bpp_blt_ proc

    push ebp
    mov ebp, esp
    sub esp, 8
    
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax
    mov edi, ecx
    mov eax, edx
    mov ecx, dword ptr [edi].bmp_width
    mov edx, dword ptr [edi].bmp_height
    call clip_image
    jc bitmap_1bpp_blt_exit
    
    mov dword ptr [ebp - 4], ecx
    mov dword ptr [ebp - 8], edx
    
    xchg edi, esi
    
    mov edx, dword ptr [edi].img_selector
    mov es, dx
    assume es:nothing
    
    mov edx, dword ptr [edi].img_stride
    mov edi, dword ptr [edi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].bmp_width
    mov ecx, dword ptr [ebp - 4]
    sub eax, ecx
    mov dword ptr [ebp - 4], eax
    mov ebx, dword ptr [ebp - 8]
    mov esi, dword ptr [esi].bmp_bits
    
bitmap_1bpp_blt_next_line:

    push ecx
    push edi
    
bitmap_1bpp_blt_next_byte:

    lodsb
    or al, al
    jz bitmap_1bpp_blt_skip_byte

    push ebx
    push ecx

    movzx  eax, al
    mov ebx, dword ptr [ebp + 8]
    mov ecx, 8

bitmap_1bpp_blt_next_pixel:

    shr eax, 1
    jnc bitmap_1bpp_blt_skip_pixel

    mov dword ptr es:[edi], ebx

bitmap_1bpp_blt_skip_pixel:

    add edi, 4
    loop bitmap_1bpp_blt_next_pixel
    
    pop ecx
    pop ebx
    jmp bitmap_1bpp_blt_byte_end   

bitmap_1bpp_blt_skip_byte:

    add edi, 32

bitmap_1bpp_blt_byte_end:

    loop bitmap_1bpp_blt_next_byte
    
    add esi, dword ptr [ebp - 4]
    pop edi
    pop ecx
    add edi, edx
    dec ebx
    jnz bitmap_1bpp_blt_next_line
    
bitmap_1bpp_blt_exit:

    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    mov esp, ebp
    pop ebp

    ret 4

bitmap_1bpp_blt_ endp


; copy an 8bpp bitmap into an image
;
; inputs:
;   eax image
;   edx dest x
;   ebx dest y
;   ecx bitmap
;   [ebp + 8] color
;
; outputs:
;   none
;
; destroys:
;   none
public bitmap_8bpp_blt_
bitmap_8bpp_blt_ proc

    push ebp
    mov ebp, esp
    sub esp, 8
    
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax
    mov edi, ecx
    mov eax, edx
    mov ecx, dword ptr [edi].bmp_width
    mov edx, dword ptr [edi].bmp_height
    call clip_image
    jc bitmap_8bpp_blt_exit
    
    mov dword ptr [ebp - 4], ecx
    mov dword ptr [ebp - 8], edx
    
    xchg edi, esi
    
    mov edx, dword ptr [edi].img_selector
    mov es, dx
    assume es:nothing
    
    mov edx, dword ptr [edi].img_stride
    mov edi, dword ptr [edi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].bmp_width
    mov ecx, dword ptr [ebp - 4]
    sub eax, ecx
    mov dword ptr [ebp - 4], eax
    mov ebx, dword ptr [ebp - 8]
    mov esi, dword ptr [esi].bmp_bits
    
bitmap_8bpp_blt_next_line:

    push ecx
    push edi
    
bitmap_8bpp_blt_next_pixel:

    lodsb
    or al, al
    jz bitmap_8bpp_blt_skip_pixel
    
    mov eax, dword ptr [ebp + 8]
    mov dword ptr es:[edi], eax
    
bitmap_8bpp_blt_skip_pixel:

    add edi, 4
    loop bitmap_8bpp_blt_next_pixel
    
    add esi, dword ptr [ebp - 4]
    pop edi
    pop ecx
    add edi, edx
    dec ebx
    jnz bitmap_8bpp_blt_next_line
    
bitmap_8bpp_blt_exit:

    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    mov esp, ebp
    pop ebp

    ret 4

bitmap_8bpp_blt_ endp

; copy a 24bpp bitmap into an image
;
; inputs:
;   eax image
;   edx dest x
;   ebx dest y
;   ecx bitmap
;
; outputs:
;   none
;
; destroys:
;   none
public bitmap_24bpp_blt_
bitmap_24bpp_blt_ proc

    push ebp
    mov ebp, esp
    sub esp, 8

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax
    mov edi, ecx
    mov eax, edx
    mov ecx, dword ptr [edi].bmp_width
    mov edx, dword ptr [edi].bmp_height
    call clip_image
    jc bitmap_24bpp_blt_exit
    
    mov dword ptr [ebp - 4], ecx
    mov dword ptr [ebp - 8], edx
    
    xchg edi, esi
    
    mov edx, dword ptr [edi].img_selector
    mov es, dx
    assume es:nothing
    
    mov edx, dword ptr [edi].img_stride
    mov edi, dword ptr [edi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].bmp_width
    mov ecx, dword ptr [ebp - 4]
    sub eax, ecx
    mov dword ptr [ebp - 4], eax
    mov ebx, dword ptr [ebp - 8]
    mov esi, dword ptr [esi].bmp_bits
    
bitmap_24bpp_blt_next_line:

    push ecx
    push edi
    
bitmap_24bpp_blt_next_pixel:

    push ebx
    xor ebx, ebx

    lodsb
    movzx eax, al
    shl eax, 16
    or ebx, eax

    lodsb
    movzx eax, al
    shl eax, 8
    or ebx, eax

    lodsb
    movzx eax, al
    or ebx, eax

    mov dword ptr es:[edi], ebx
    
    pop ebx
    add edi, 4
    loop bitmap_24bpp_blt_next_pixel
    
    add esi, dword ptr [ebp - 4]
    pop edi
    pop ecx
    add edi, edx
    dec ebx
    jnz bitmap_24bpp_blt_next_line
    
bitmap_24bpp_blt_exit:

    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    mov esp, ebp
    pop ebp

    ret

bitmap_24bpp_blt_ endp

; copy a 32bpp bitmap into an image
;
; inputs:
;   eax image
;   edx dest x
;   ebx dest y
;   ecx bitmap
;
; outputs:
;   none
;
; destroys:
;   none
public bitmap_32bpp_blt_
bitmap_32bpp_blt_ proc

    push ebp
    mov ebp, esp
    sub esp, 8

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax
    mov edi, ecx
    mov eax, edx
    mov ecx, dword ptr [edi].bmp_width
    mov edx, dword ptr [edi].bmp_height
    call clip_image
    jc bitmap_32bpp_blt_exit
    
    mov dword ptr [ebp - 4], ecx
    mov dword ptr [ebp - 8], edx
    
    xchg edi, esi
    
    mov edx, dword ptr [edi].img_selector
    mov es, dx
    assume es:nothing
    
    mov edx, dword ptr [edi].img_stride
    mov edi, dword ptr [edi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].bmp_width
    mov ecx, dword ptr [ebp - 4]
    sub eax, ecx
    mov dword ptr [ebp - 4], eax
    mov ebx, dword ptr [ebp - 8]
    mov esi, dword ptr [esi].bmp_bits
    
bitmap_32bpp_blt_next_line:

    push ecx
    push edi
    
    rep movsd

    add esi, dword ptr [ebp - 4]
    pop edi
    pop ecx
    add edi, edx
    dec ebx
    jnz bitmap_32bpp_blt_next_line
    
bitmap_32bpp_blt_exit:

    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    mov esp, ebp
    pop ebp

    ret

bitmap_32bpp_blt_ endp

end
