/*
 cursor.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__CURSOR_H__)

#include <stddef.h>
#include <stdint.h>
#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 0)
struct cursor
{
    uint32_t width;
    uint32_t height;
    uint32_t hot_x;
    uint32_t hot_y;
    uint32_t data;
};
#pragma pack(pop)

extern struct cursor* _cursor_current;

extern struct cursor _cursor_arrow;
extern struct cursor _cursor_crossh;
extern struct cursor _cursor_e;
extern struct cursor _cursor_ew;
extern struct cursor _cursor_hand;
extern struct cursor _cursor_help;
extern struct cursor _cursor_insert;
extern struct cursor _cursor_move;
extern struct cursor _cursor_n;
extern struct cursor _cursor_ne;
extern struct cursor _cursor_nesw;
extern struct cursor _cursor_ns;
extern struct cursor _cursor_nw;
extern struct cursor _cursor_nwse;
extern struct cursor _cursor_s;
extern struct cursor _cursor_se;
extern struct cursor _cursor_sw;
extern struct cursor _cursor_w;
extern struct cursor _cursor_wait;

extern void
cursor_blt(
    struct image*const image,
    int32_t const dest_x,
    int32_t const dest_y,
    struct cursor const*const cursor);

extern void
cursor_image_to_backing(
    struct image const*const image,
    int32_t const img_x,
    int32_t const img_y,
    uint32_t const cursor_len_x /*precond: max 72*/,
    uint32_t const cursor_len_y /*precond: max 72*/);

extern void
cursor_backing_to_image(
    struct image*const image);

#ifdef __cplusplus
}
#endif

#define __CURSOR_H__
#endif
