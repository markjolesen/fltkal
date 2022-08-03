; image_.asm
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

include image_.inc
include clip_.inc

.model flat

.code

assume ds:_DATA, es:_DATA, ss:_DATA, cs:_TEXT

extrn clip_image:proc

; fill image
;
; inputs:
;   eax image
;   edx color
;
; outputs:
;   none
;
; destroys:
;   none
public image_fill_ 
image_fill_ proc

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es

    mov esi, eax
    mov ecx, edx
    
    mov eax, dword ptr [esi].img_stride
    mov ebx, dword ptr [esi].img_height
    mul ebx
    shr eax, 2
    
    xchg eax, ecx
    
    xor edi, edi
    mov edx, dword ptr [esi].img_selector
    mov es, dx
    assume es:nothing
    
    rep stosd
    
    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret
image_fill_ endp

; fill an area of an image
;
; inputs:
;   eax image
;   edx x
;   ebx y
;   ecx len_x
;   [ebp + 8] len_y
;   [ebp + 12] color
;
; outputs:
;   none
;
; destroys:
;   none
;
public image_fill_area_ 
image_fill_area_ proc

    push ebp
    mov ebp, esp

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax 
    mov eax, edx 
    mov edx, dword ptr [ebp + 8]
    call clip_image
    jc image_fill_area_exit
    
    mov edi, dword ptr [esi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].img_selector
    mov es, ax
    assume es:nothing
    
    mov eax, dword ptr [ebp + 12] ; color
    
image_fill_area_next_line:

    push edi
    push ecx
    rep stosd
    pop ecx
    pop edi
    add edi, dword ptr [esi].img_stride
    dec edx
    jnz image_fill_area_next_line
    
image_fill_area_exit:
 
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

    ret 8
    
image_fill_area_ endp

; draw a pixel
;
; inputs:
;
;   eax image
;   edx x
;   ebx y
;   ecx color
;
; outputs:
;
;   none
;
; detroys:
;
;   none
public image_pixel_put_
image_pixel_put_ proc

    push ebp
    mov ebp, esp
    sub esp, 4
    
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov dword ptr [ebp - 4], ecx
    mov esi, eax 
    mov eax, edx 
    mov ecx, 1
    mov edx, 1
    call clip_image
    jc image_pixel_put_exit

    mov edi, dword ptr [esi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].img_selector
    mov es, ax
    assume es:nothing
    
    mov eax, dword ptr [ebp - 4]
    mov dword ptr es:[edi], eax
    
image_pixel_put_exit:

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
    
image_pixel_put_ endp

; draw a horizontal line
;
; inputs:
;   eax image 
;   edx x
;   ebx y
;   ecx len
;   [ebp+8] color
;
; outputs:
;   none
; 
; destroys:
;   none
;
public image_lineh_
image_lineh_ proc

    push ebp
    mov ebp, esp
    
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax 
    mov eax, edx 
    mov edx, 1
    call clip_image
    jc image_lineh_exit
    
    mov edi, dword ptr [esi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].img_selector
    mov es, ax
    assume es:nothing
    
    mov eax, dword ptr [ebp + 8] ; color
    rep stosd
    
image_lineh_exit:
    
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
    
image_lineh_ endp

; xor a horizontal line
;
; inputs:
;   eax image 
;   edx x
;   ebx y
;   ecx len
;
; outputs:
;   none
; 
; destroys:
;   none
;
public image_lineh_xor_
image_lineh_xor_ proc

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ds
    push es
    
    mov esi, eax 
    mov eax, edx 
    mov edx, 1
    call clip_image
    jc image_lineh_xor_exit
    
    mov edi, dword ptr [esi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].img_selector
    mov esi, edi
    mov es, ax
    assume es:nothing
    mov ds, ax
    assume ds:nothing
    
image_lineh_xor_next:
    
    lodsd 
    xor eax, -1
    stosd
    loop image_lineh_xor_next
    
image_lineh_xor_exit:
    
    pop es
    assume es:_DATA
    pop ds
    assume ds:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    
    ret
    
image_lineh_xor_ endp

; draw a vertical line
;
; inputs:
;   eax image 
;   edx x
;   ebx y
;   ecx len
;   [ebp+8] color
;
; outputs:
;   none
; 
; destroys:
;   none
;
public image_linev_
image_linev_ proc

    push ebp
    mov ebp, esp
    
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax 
    mov eax, edx 
    mov edx, ecx
    mov ecx, 1
    call clip_image
    jc image_linev_exit
    
    
    mov edi, dword ptr [esi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov ecx, edx 
    mov eax, dword ptr [esi].img_selector
    mov es, ax
    assume es:nothing
    
    mov eax, dword ptr [ebp + 8]
    mov edx, dword ptr [esi].img_stride
    
image_linev_next_line:

    mov dword ptr es:[edi], eax
    add edi, edx
    loop image_linev_next_line 
    
image_linev_exit:
    
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
    
image_linev_ endp

; xor a vertical line
;
; inputs:
;   eax image 
;   edx x
;   ebx y
;   ecx len
;
; outputs:
;   none
; 
; destroys:
;   none
;
public image_linev_xor_
image_linev_xor_ proc

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es
    
    mov esi, eax 
    mov eax, edx 
    mov edx, ecx
    mov ecx, 1
    call clip_image
    jc image_linev_xor_exit
    
    mov edi, dword ptr [esi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov ecx, edx 
    mov eax, dword ptr [esi].img_selector
    mov es, ax
    assume es:nothing
    
    mov edx, dword ptr [esi].img_stride
    
image_linev_xor_next_line:

    mov eax, dword ptr es:[edi]
    xor eax, -1
    mov dword ptr es:[edi], eax
    add edi, edx
    loop image_linev_xor_next_line 
    
image_linev_xor_exit:
    
    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    
    ret
    
image_linev_xor_ endp

; copy bits from one image into another (with exact dimensions)
;
; inputs:
;
;   eax destination image
;   edx source image
;
; outputs:
;   none
;
; destroys:
;   none
;
public image_blt_exact_
image_blt_exact_ proc

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ds
    push es
    
    mov edi, eax
    mov esi, edx

    mov eax, dword ptr [esi].img_stride
    mov ebx, dword ptr [esi].img_height
    mul ebx
    shr eax, 2
    
    mov ecx, eax
    
    mov eax, dword ptr [edi].img_selector
    mov es, ax
    assume es:nothing
    mov eax, dword ptr [esi].img_selector
    mov ds, ax
    assume ds:nothing
    xor esi, esi
    xor edi, edi
    rep movsd
    
    pop es
    assume es:_DATA
    pop ds
    assume ds:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret
    
image_blt_exact_ endp

; copy bits from one image into another (no clipping/checking)
;
; inputs:
;
;   eax destination image
;   edx destination x
;   ebx destination y
;   ecx source image
;
; outputs:
;   none
;
; destroys:
;   none
;
public image_noclip_blt_
image_noclip_blt_ proc

    push ebp
    mov ebp, esp
    sub esp, 12

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ds
    push es
    
    mov edi, dword ptr [eax].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl edx, 2
    add edi, edx
    mov edx, dword ptr [eax].img_stride
    mov dword ptr [ebp - 4], edx
    mov ebx, dword ptr [eax].img_selector
    mov es, bx
    assume es:nothing
    
    mov eax, dword ptr [ecx].img_stride
    mov dword ptr [ebp - 8], eax
    mov eax, dword ptr [ecx].img_width
    mov dword ptr [ebp - 12], eax
    mov edx, dword ptr [ecx].img_height
    
    mov esi, dword ptr [ecx].img_line
    mov esi, dword ptr [esi] 
    mov eax, dword ptr [ecx].img_selector
    mov ds, ax
    assume ds:nothing
    
image_noclip_blt_next_line:

    push esi
    push edi
    mov ecx, dword ptr [ebp - 12]
    rep movsd
    pop edi
    pop esi
    add edi, dword ptr [ebp - 4]
    add esi, dword ptr [ebp - 8]
    dec edx
    jnz image_noclip_blt_next_line

    pop es
    assume es:_DATA
    pop ds
    assume ds:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    
    mov esp, ebp
    pop ebp
    ret
    
    ret
image_noclip_blt_ endp

end
