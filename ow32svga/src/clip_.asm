; clip_.asm
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

include clip_.inc
include image_.inc

.model flat

.code

assume ds:_DATA, es:_DATA, ss:_DATA, cs:_TEXT

; clip to boundries
;
; inputs:
;   eax x
;   ebx y
;   ecx len_x
;   edx len_y
;   esi clip
;
; ouputs:
;   cf(0) success
;       eax clipped x
;       ebx clipped y
;       ecx clipped len_x
;       edx clipped len_y
;   cf(1) out of boundries
; 
; destroys:
;   none
;
public clip_rect
clip_rect proc

    push edi

    or ecx, ecx
    jz clip_rect_exit_carry
    
    or edx, edx 
    jz clip_rect_exit_carry
    
    cmp eax, dword ptr [esi].clip_x2
    jg clip_rect_exit_carry
    
    cmp ebx, dword ptr [esi].clip_y2
    jg clip_rect_exit_carry
    
    mov edi, dword ptr [esi].clip_x1
    cmp eax, edi
    jge clip_rect_x2
    
    sub edi, eax
    sub ecx, edi
    jle clip_rect_exit_carry
    
    mov eax, dword ptr [esi].clip_x1
    
clip_rect_x2:

    mov edi, eax
    add edi, ecx
    cmp edi, dword ptr [esi].clip_x2
    jle clip_rect_y1
    
    mov ecx, dword ptr [esi].clip_x2
    sub ecx, eax
    jle clip_rect_exit_carry
    
clip_rect_y1:

    mov edi, dword ptr [esi].clip_y1
    cmp ebx, edi
    jge clip_rect_y2
    
    sub edi, ebx
    sub edx, edi
    jle clip_rect_exit_carry
    
    mov ebx, dword ptr [esi].clip_y1
    
clip_rect_y2:

    mov edi, ebx
    add edi, edx
    cmp edi, dword ptr [esi].clip_y2
    jle clip_rect_exit_nocarry
    
    mov edx, dword ptr [esi].clip_y2
    sub edx, ebx
    jle clip_rect_exit_carry
    
clip_rect_exit_nocarry:

    clc
    jmp clip_rect_exit

clip_rect_exit_carry:

    stc
    
clip_rect_exit:

    pop edi

    ret
clip_rect endp

; clip to image boundries
;
; inputs:
;   eax x
;   ebx y
;   ecx len_x
;   edx len_y
;   esi image
;
; ouputs:
;   cf(0) success
;       eax clipped x
;       ebx clipped y
;       ecx clipped len_x
;       edx clipped len_y
;   cf(1) out of boundries
; 
; destroys:
;   none
;
public clip_image
clip_image proc

    push esi
    
    lea esi, [esi].img_clip_x1
    call clip_rect
    
    pop esi
    
    ret
    
clip_image endp

end
