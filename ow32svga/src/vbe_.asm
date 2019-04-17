; vbe_.asm
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

include regs_.inc
include vbe_.inc

.model flat

.code

assume ds:_DATA, es:_DATA, ss:_DATA, cs:_TEXT

; get VBE controller data
;
; inputs:
;
;   ds = es = ss = _DATA
;   eax 512 byte vbe_info_block address
;
; outputs:
;
;   eax 0 success structure filled in with info
;   eax !0 error
;       -1 function not supported
;       0007h memory control blocks damaged
;       0008h insufficent memory
;       8011h descriptor unavailable 
;       8012h linear memory unavailable
;       8013h physical memory unavailable
;       8014h backing store unavailable
;       8021h invalid value (cx too large)
;
; destroys:
;   eax
public vbe_get_info_block_
vbe_get_info_block_ proc

    push ebp 
    mov ebp, esp 
    sub esp, SIZE regs32
    
    push ebx
    push ecx
    push edx
    push esi
    push edi
   
    mov esi, eax
    
    ; int 31h function 100h Allocate DOS memory block
    ;   bx = number of 16 byte paragraphs desired
    ; returns 
    ;   cf clear
    ;     ax = real mode segment base address of allocated block
    ;     dx = selector for allocated block
    mov ax, 0100h
    mov bx, ((15 + SIZE vbe_info_block) shr 4)
    int 031h
    jc vbe_get_info_block_exit ; DPMI ax=error
    
    ; set regs to zero
    lea  edi, [ebp - SIZE regs32]
    push eax
    push edi
    mov ecx, SIZE regs32
    xor eax, eax
    rep stosb
    pop edi
    pop eax

    ; Function 4f00h - Get VBE Controller Information
    ;
    ; input:
    ;   ax = 4f00h
    ;   es:di= pointer to 512 byte buffer
    ; output: 
    ;   ax return status
    ;     al == 4fh: function supported
    ;     al != 4fh: function not supported
    ;     ah == 00h: function call successful
    ;     ah == 01h: function call failed
    ;     ah == 02h: hardware does not support
    ;     ah == 03h: invalid function call
    mov [dword ptr es:edi].r32_eax, 04f00h
    mov [word ptr es:edi].r32_es, ax
    
    ; int 31h 0300h Simulate real mode interrupt
    ; ax 0300h
    ; bl interrupt number
    ; bh flags (must be zero)
    ; cx number of words to copy from protected mode to real mode stack
    ; es:(e)di selector:offset of real mode register 
    mov eax, 0300h
    mov ebx, 010h
    xor ecx, ecx
    int 031h
    jc vbe_get_info_block_cleanup 
    
    mov eax, [dword ptr es:edi].r32_eax
    cmp  ax, 04fh
    je vbe_get_info_block_copy
    mov eax, -1
    jmp vbe_get_info_block_cleanup
    
vbe_get_info_block_copy:

    ; copy data
    push ds
    mov edi, esi
    mov ds, dx
    assume ds:NOTHING
    xor esi, esi
    mov ecx, SIZE vbe_info_block
    rep movsb
    pop ds
    assume ds:_DATA
    
    xor eax, eax 

vbe_get_info_block_cleanup:

    ; int 31h function 101h Free DOS memory block 
    ;
    ; inputs:
    ;
    ;   ax 0101h
    ;   dx selector of block to be freed
    push eax
    mov eax, 0101h
    int 031h
    pop eax

vbe_get_info_block_exit:    
    
    pop edi
    pop esi
    pop edx
    pop ecx
    pop ebx

    mov esp,ebp 
    pop ebp 
    ret
    
vbe_get_info_block_ endp

; get 256 byte mode info block
;
; inputs:
;
;   ds = es = ss = _DATA
;   eax 256 byte mode info block to fill in
;   edx mode number
;
; outputs:
;
;   eax 0 success structure filled in with info
;   eax !0 error
;       0007h memory control blocks damaged
;       0008h insufficent memory
;       8011h descriptor unavailable 
;
; destroys:
;   eax, edx
public vbe_get_mode_block_
vbe_get_mode_block_ proc

    push ebp 
    mov ebp, esp 
    sub esp, SIZE regs32
    
    push ebx
    push ecx
    push esi
    push edi
   
    mov esi, eax
    mov ecx, edx
    
    ; int 31h function 100h Allocate DOS memory block
    ;   bx = number of 16 byte paragraphs desired
    ; returns 
    ;   cf clear
    ;     ax = real mode segment base address of allocated block
    ;     dx = selector for allocated block
    mov ax, 0100h
    mov bx, ((15 + SIZE vbe_mode_block) shr 4)
    int 031h
    jc vbe_get_mode_block_exit ; DPMI ax=error
    
    ; set regs to zero
    lea  edi, [ebp - SIZE regs32]
    push eax
    push ecx
    push edi
    mov ecx, SIZE regs32
    xor eax, eax
    rep stosb
    pop edi
    pop ecx
    pop eax

    ; Function 4f01h - Get VBE mode information
    ;
    ; input:
    ;   ax = 4f01h
    ;   cx = mode number
    ;   es:di= pointer to 256 byte buffer
    ; output: 
    ;   ax return status
    ;     al == 4fh: function supported
    ;     al != 4fh: function not supported
    ;     ah == 00h: function call successful
    ;     ah == 01h: function call failed
    ;     ah == 02h: hardware does not support
    ;     ah == 03h: invalid function call
    mov [dword ptr es:edi].r32_eax, 04f01h
    mov [dword ptr es:edi].r32_ecx, ecx
    mov [word ptr es:edi].r32_es, ax
    
    ; int 31h 0300h Simulate real mode interrupt
    ; ax 0300h
    ; bl interrupt number
    ; bh flags (must be zero)
    ; cx number of words to copy from protected mode to real mode stack
    ; es:(e)di selector:offset of real mode register 
    mov eax, 0300h
    mov ebx, 010h
    xor ecx, ecx
    int 031h
    jc vbe_get_mode_block_cleanup 
    
    mov eax, [dword ptr es:edi].r32_eax
    cmp  ax, 04fh
    je vbe_get_mode_block_copy
    mov eax, -1
    jmp vbe_get_mode_block_cleanup
    
vbe_get_mode_block_copy:

    ; copy data
    push ds
    mov edi, esi
    mov ds, dx
    assume ds:NOTHING
    xor esi, esi
    mov ecx, SIZE vbe_mode_block
    rep movsb
    pop ds
    assume ds:_DATA
    
    xor eax, eax 

vbe_get_mode_block_cleanup:

    ; int 31h function 101h Free DOS memory block 
    ;
    ; inputs:
    ;
    ;   ax 0101h
    ;   dx selector of block to be freed
    push eax
    mov eax, 0101h
    int 031h
    pop eax

vbe_get_mode_block_exit:    
    
    pop edi
    pop esi
    pop ecx
    pop ebx

    mov esp,ebp 
    pop ebp 
    ret
    
vbe_get_mode_block_ endp

public vbe_get_mode_
vbe_get_mode_ proc

    push ebp 
    mov ebp, esp 
    sub esp, SIZE regs32
    
    push ebx
    push ecx
    push esi
    push edi
    
    ; set regs to zero
    lea  edi, [ebp - SIZE regs32]
    push eax
    push edi
    mov ecx, SIZE regs32
    xor eax, eax
    rep stosb
    pop edi
    pop eax
    
    ; Function 4f03 - Get SuperVGA video mode
    ;
    ; input:
    ;
    ;   ax = 4f03h
    ;
    ; output: 
    ;
    ;   ah return status
    ;     ah == 0h: successful
    ;     ah == 1h: failed
    ;     bx video mode
    mov [dword ptr es:edi].r32_eax, 04f03h
    
    ; int 31h 0300h Simulate real mode interrupt
    ; ax 0300h
    ; bl interrupt number
    ; bh flags (must be zero)
    ; cx number of words to copy from protected mode to real mode stack
    ; es:(e)di selector:offset of real mode register 
    mov eax, 0300h
    mov ebx, 010h
    xor ecx, ecx
    int 031h
    jc vbe_get_mode_error_exit 
    
    mov eax, [dword ptr es:edi].r32_eax
    cmp  ax, 04fh
    jne vbe_get_mode_error_exit
    mov eax, [dword ptr es:edi].r32_ebx
    and eax, 0xffff
    jmp vbe_get_mode_exit
    
vbe_get_mode_error_exit:    
    mov eax, -1
    
vbe_get_mode_exit:    
    
    pop edi
    pop esi
    pop ecx
    pop ebx

    mov esp,ebp 
    pop ebp 
    ret
vbe_get_mode_ endp

; set video mode
;
; inputs:
;   eax video mode
;
; outputs:
;   eax 0 success
;      !0 failure
;
; destroys:
;   eax
public vbe_set_mode_
vbe_set_mode_ proc

    push ebp 
    mov ebp, esp 
    sub esp, SIZE regs32
    
    push ebx
    push ecx
    push esi
    push edi
    
    ; set regs to zero
    lea  edi, [ebp - SIZE regs32]
    push eax
    push edi
    mov ecx, SIZE regs32
    xor eax, eax
    rep stosb
    pop edi
    pop eax
    
    ; Function 4f02 - Set SuperVGA video mode
    ;
    ; input:
    ;   ax = 4f02h
    ;   bx = mode number
    ;   es:di CRTC information block 
    ; output: 
    ;   ax return status
    ;     al == 4fh: function supported
    ;     al != 4fh: function not supported
    ;     ah == 00h: function call successful
    ;     ah == 01h: function call failed
    mov [dword ptr es:edi].r32_eax, 04f02h
    and eax, not (1 shl 11) ; turn off CRTC refresh rate values
    mov [dword ptr es:edi].r32_ebx, eax
    
    ; int 31h 0300h Simulate real mode interrupt
    ; ax 0300h
    ; bl interrupt number
    ; bh flags (must be zero)
    ; cx number of words to copy from protected mode to real mode stack
    ; es:(e)di selector:offset of real mode register 
    mov eax, 0300h
    mov ebx, 010h
    xor ecx, ecx
    int 031h
    jc vbe_set_mode_error_exit 
    
    mov eax, [dword ptr es:edi].r32_eax
    cmp  ax, 04fh
    jne vbe_set_mode_error_exit
    
    xor eax, eax
    jmp vbe_set_mode_exit
    
vbe_set_mode_error_exit:    
    mov eax, -1
    
vbe_set_mode_exit:    
    
    pop edi
    pop esi
    pop ecx
    pop ebx

    mov esp,ebp 
    pop ebp 
    ret
    
vbe_set_mode_ endp

end
