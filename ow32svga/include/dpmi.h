/*
 dpmi.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright 
 and related or neighboring rights to ow32svga Library. This work is published 
 from: United States.
*/
#if !defined(__DPMI_H__)

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t
dpmi_selector_alloc();

extern void
dpmi_selector_free(
    uint32_t selector);

extern int
dpmi_selector_set_base(
    uint32_t selector,
    uint32_t const linear_address);

extern int
dpmi_selector_set_limit(
    uint32_t selector,
    uint32_t const limit);

extern uint32_t
dpmi_physical2linear(
    uint32_t const physical_address,
    uint32_t const limit);

inline void const*
dpmi_real2linear(
    uint32_t const segoff)
{
    uint32_t seg= ((segoff & ~0xffffL) >> 12);
    uint32_t off= (segoff & 0xffff);
    void const* ptr= (void const*)(seg | off);
    return ptr;
}

extern int
dpmi_alloc(
    uint32_t*const linear_address,
    uint32_t*const handle,
    size_t const size);

extern void
dpmi_free(
    uint32_t handle);

#ifdef __cplusplus
}
#endif

#define __VBE_H__
#endif
