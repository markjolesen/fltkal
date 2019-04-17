; cursor_.asm
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

include cursor_.inc
include image_.inc

.model flat

.data?

backing_valid dd ?
backing_x dd ?
backing_y dd ?
backing_len_x dd ?
backing_len_y dd ?
backing_data dd (72*72) dup(?)

.data

public __cursor_current

__cursor_current dd 0

.code

assume ds:_DATA, es:_DATA, ss:_DATA, cs:_TEXT

extrn clip_image:proc

; cursor_blt draw a cursor onto an image
;
; inputs:
;   eax image
;   edx dest_x
;   ebx dest_y
;   ecx cursor
;
public cursor_blt_
cursor_blt_ proc

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
    
    mov dword ptr [__cursor_current], ecx
    mov esi, eax
    mov edi, ecx
    
    mov eax, edx
    mov ecx, dword ptr [edi].cur_width
    mov edx, dword ptr [edi].cur_height
    call clip_image
    jc cursor_blt_exit
    
    mov dword ptr [ebp - 4], ecx
    mov dword ptr [ebp - 8], edx
    
    xchg esi, edi
    
    mov edx, dword ptr [edi].img_selector
    mov es, dx
    assume es:nothing
    
    mov edx, dword ptr [edi].img_stride
    mov edi, dword ptr [edi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov eax, dword ptr [esi].cur_width
    mov ecx, dword ptr [ebp - 4]
    sub eax, ecx
    shl eax, 2
    mov dword ptr [ebp - 4], eax
    mov ebx, dword ptr [ebp - 8]
    lea esi, dword ptr [esi].cur_data
    
cursor_blt_next_line:

    push ecx
    push edi
    
cursor_blt_next_pixel:

    lodsd
    or eax, eax
    jz cursor_blt_skip_pixel
    
    mov dword ptr es:[edi], eax
    
cursor_blt_skip_pixel:

    add edi, 4
    loop cursor_blt_next_pixel
    
    add esi, dword ptr [ebp - 4]
    pop edi
    pop ecx
    add edi, edx
    dec ebx
    jnz cursor_blt_next_line

cursor_blt_exit:

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
    
cursor_blt_ endp

; store part of image into cursor backing store
; eax image
; edx x
; ebx y
; ecx len x (maximum value 72; not checked)
; [ebp + 8] len y (maximum value 72; not checked)
;
public cursor_image_to_backing_ 
cursor_image_to_backing_ proc

    push ebp
    mov ebp, esp
    
    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push ds
    
    mov dword ptr [backing_valid], 0
    
    mov esi, eax
    mov eax, edx
    mov edx, dword ptr [ebp + 8] 
    call clip_image
    jc cursor_image_to_backing_exit
    
    mov dword ptr [backing_valid], 1
    mov dword ptr [backing_x], eax
    mov dword ptr [backing_y], ebx
    mov dword ptr [backing_len_x], ecx
    mov dword ptr [backing_len_y], edx
    
    lea edi, backing_data
    
    mov ecx, dword ptr [esi].img_selector
    
    mov edx, dword ptr [esi].img_stride
    mov esi, dword ptr [esi].img_line
    mov esi, dword ptr [esi + ebx * 4]
    shl eax, 2
    add esi, eax
    
    mov ds, cx
    assume ds:nothing
    
    mov ecx, dword ptr es:[backing_len_x]
    mov ebx, dword ptr es:[backing_len_y]
    
cursor_image_to_backing_next_line:

    push ecx
    push esi
    rep movsd
    pop esi
    pop ecx
    add esi, edx
    dec ebx
    jnz cursor_image_to_backing_next_line

cursor_image_to_backing_exit:

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

    ret 4
    
cursor_image_to_backing_ endp

; restore backing store to image
;
; inputs:
;   eax image 
;
; outputs:
;   nothing
;
; destroys:
;   nothing
;
public cursor_backing_to_image_
cursor_backing_to_image_  proc

    push eax
    push ebx
    push ecx
    push edx
    push esi
    push edi
    push es

    mov edi, eax
    mov eax, dword ptr [backing_valid]
    or eax, eax
    jz cursor_backing_to_image_exit
    
    mov eax, dword ptr [backing_x]
    mov ebx, dword ptr [backing_y]
    mov ecx, dword ptr [edi].img_selector
    mov edx, dword ptr [edi].img_stride
    mov edi, dword ptr [edi].img_line
    mov edi, dword ptr [edi + ebx * 4]
    shl eax, 2
    add edi, eax
    
    mov es, cx
    assume es:nothing
    
    lea esi, backing_data
    mov ecx, dword ptr [backing_len_x]
    mov ebx, dword ptr [backing_len_y]
    
cursor_backing_to_image_next_line:

    push ecx
    push edi
    rep movsd
    pop edi
    pop ecx
    add edi, edx
    dec ebx
    jnz cursor_backing_to_image_next_line
    
cursor_backing_to_image_exit:

    pop es
    assume es:_DATA
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax

    ret
    
cursor_backing_to_image_  endp

end
