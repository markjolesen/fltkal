; dpmi_.asm
;
; License CC0 PUBLIC DOMAIN
;
; To the extent possible under law, Mark J. Olesen has waived all copyright 
; and related or neighboring rights to ow32svga Library. This work is published 
; from: United States.

.model flat

.code

; Allocate LDT descriptor
;
; inputs:
;   none
;
; ouputs:
;   ax selector
;
; destroys:
;   eax
public dpmi_selector_alloc_ 
dpmi_selector_alloc_ proc

    push ebx
    push ecx

    ; int 31 function 0x00 - Allocate LDT descriptor
    ;
    ; inputs:
    ;   ax 00h
    ;   cx number of descriptors to allocate
    ;
    ; returns
    ;   cf clear success
    ;       ax selector
    ;   cf set failure
    ;       ax error code
    xor eax, eax
    mov ecx, 1
    int 31h
    jc dpmi_selector_alloc_error
    
    ; INT 31h 09h - Set descriptor access rights
    ;   ax 09h
    ;   bx selector
    ;   cl access rights
    ;   ch 80386 extended rights
    ;
    ; returns
    ;   cf clear success
    ;       eax selector
    ;   cf set failure
    ;       eax error code
    mov ebx, eax
    mov eax, 09h
    mov ecx, 08092h ; 32 bit page granular
    int 31h
    mov eax, ebx
    jnc dpmi_selector_alloc_exit
    
    ; INT 31 01h Free LDT descriptor
    mov eax, 01h
    int 31h

dpmi_selector_alloc_error:

    mov eax, -1

dpmi_selector_alloc_exit:

    pop ecx
    pop ebx
    
    ret
    
dpmi_selector_alloc_ endp

; Free LDT Descriptor
;
; inputs:
;   ax descriptor
;
; outputs:
;   none
;
; destroys:
;   none
public dpmi_selector_free_
dpmi_selector_free_ proc

    push eax
    push ebx
    
    ; INT 31 01h Free LDT descriptor
    mov ebx, eax
    mov eax, 01h
    int 31h
    
    pop ebx
    pop eax

    ret
dpmi_selector_free_ endp

; Set selector (segment) base address
;
; inputs:
;   eax selector
;   edx linear address used for new base address
;
; ouptuts:
; 
;   eax 0 success
;   eax -1 failure
;
public dpmi_selector_set_base_
dpmi_selector_set_base_ proc

    push ebx
    push ecx
    push edx

    ; INT 31h 07h - Set segment base address
    mov ebx, eax
    mov ecx, edx
    shr ecx, 16
    and edx, 0ffffh
    mov eax, 07h
    int 31h 
    jc dpmi_selector_set_base_error
    
    xor eax, eax
    jmp dpmi_selector_set_base_exit
    
dpmi_selector_set_base_error:

    mov eax, -1

dpmi_selector_set_base_exit:

    pop edx
    pop ecx
    pop ebx

    ret
dpmi_selector_set_base_ endp

; Set selector limit
;
; inputs:
;   eax selector
;   edx limit -1 limit for selector
;
; outputs:
;   eax 0 success
;   eax -1 failure

public dpmi_selector_set_limit_
dpmi_selector_set_limit_ proc

    push ebx
    push ecx
    push edx

    ; INT 31h 08H Set selector limit
    ; ax 08h
    ; bx selector
    ; cx:dx segment limit
    mov ebx, eax
    mov ecx, edx
    shr ecx, 16
    and edx, 0ffffh
    mov eax, 08h
    int 31h
    jc dpmi_selector_set_limit_error
    
    xor eax, eax
    jmp dpmi_selector_set_limit_exit
    
dpmi_selector_set_limit_error:

    mov eax, -1

dpmi_selector_set_limit_exit:

    pop edx
    pop ecx
    pop ebx

    ret
dpmi_selector_set_limit_ endp

; Map physical memory to linear memory
;
; inputs:
;   eax physical memory address to map
;   edx length-1 of physical memory region
;
; outputs:
;   eax linear address
;
; destroys:
;   eax
public dpmi_physical2linear_
dpmi_physical2linear_ proc

    push ebx
    push ecx
    push esi
    push edi

    ; INT 31h 0800h - Physical address mapping
    ; ax 0800h
    ; bx:cx physical address of memory
    ; si:di size of region to map (bytes)
    mov ebx, eax
    shr ebx, 16
    mov ecx, eax
    and ecx, 0ffffh
    mov esi, edx
    shr esi, 16
    mov edi, edx
    and edi, 0ffffh
    mov eax, 0800h
    int 31h
    jc dpmi_physical2linear_error
    
    mov eax, ebx
    shl eax, 16
    or eax, ecx
    jmp dpmi_physical2linear_exit
    
dpmi_physical2linear_error:

    mov eax, -1

dpmi_physical2linear_exit:

    pop edi
    pop esi
    pop ecx
    pop ebx

    ret
dpmi_physical2linear_ endp

; Allocate Memory
;
; inputs:
;
;   eax address to store linear block
;   edx address to store memory handle for resizing and freeing
;   ebx number of bytes to allocate
;
; outputs:
;
;   eax 0 success
;   eax -1 failure
;
; destroys:
;   eax 
; 
public dpmi_alloc_
dpmi_alloc_ proc

    push ebx
    push ecx
    push esi
    push edi

    mov [dword ptr eax], 0
    mov [dword ptr edx], 0

    ; INT 31h 0501h Allocate Memory Block
    ; ax 0501h
    ; bx:cx size in bytes
    ; outputs:
    ; cf clear success
    ; cf set error
    push eax
    push edx
    mov ecx, ebx
    shr ebx, 16
    and ecx, 0ffffh
    mov eax, 0501h
    int 31h
    pop edx
    pop eax
    jc dpmi_alloc_error
    
    shl ebx, 16
    and ecx, 0ffffh
    or ebx, ecx
    mov [dword ptr eax], ebx
    
    shl esi, 16
    and edi, 0ffffh
    or esi, edi
    mov [dword ptr edx], esi
    
    xor eax, eax
    jmp dpmi_alloc_exit
    
dpmi_alloc_error:

    mov eax, -1
    
dpmi_alloc_exit:
    
    pop edi
    pop esi
    pop ecx
    pop ebx
    
    ret

dpmi_alloc_ endp

; Free memory block allocated with dpmi_alloc_
;
; inputs:
;   eax handle
;
; destroys:
;   none
;
public dpmi_free_
dpmi_free_ proc

    push eax
    push esi
    push edi

    ; INT 31h 0502h - Free Memory Block
    mov esi, eax
    shr esi, 16
    mov edi, eax
    and edi, 0ffffh
    mov eax, 0502h
    int 31h
    jc dpmi_free_error
    
    xor eax, eax
    jmp dpmi_free_exit
    
dpmi_free_error:

    mov eax, -1
    
dpmi_free_exit:

    pop edi
    pop esi
    pop eax

    ret
dpmi_free_ endp

end
