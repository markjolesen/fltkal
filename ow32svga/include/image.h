/*
 image.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__IMAGE_H__)

#include <stddef.h>
#include <stdint.h>
#include <i86.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 0)
struct image
{
    int32_t stride;
    uint32_t width;
    uint32_t height;
    struct
    {
        uint8_t** line;
        uint32_t handle;
        uint32_t selector;
    }buf;
    struct
    {
        uint32_t x1;
        uint32_t y1;
        uint32_t x2;
        uint32_t y2;
    }clip;
};
#pragma pack(pop)

extern struct image* _screen;

extern struct image*
image_new(
    size_t const width,
    size_t const height,
    int const stride);

extern  void
image_free(
    struct image*const image);

inline void
image_set_clip(
    struct image*const image,
    uint32_t const x1,
    uint32_t const y1,
    uint32_t const x2,
    uint32_t const y2)
{

    image->clip.x1= x1;
    image->clip.y1= y1;
    image->clip.x2= x2;
    image->clip.y2= y2;

    return;
}

extern void
image_blt_exact(
    struct image *const dest,
    struct image const*const src);

extern void
image_noclip_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct image const*const src);

extern void
image_fill(
    struct image*const image,
    uint32_t const color);

extern void
image_fill_area(
    struct image*const image,
    int const x,
    int const y,
    size_t const len_x,
    size_t const len_y,
    uint32_t const color);

extern void
image_pixel_put(
    struct image*const image,
    int const x,
    int const y,
    uint32_t const color);

inline void
image_noclip_pixel_put(
    struct image*const image,
    int const x,
    int const y,
    uint32_t const color)
{

    *(uint32_t __far*)MK_FP(
       image->buf.selector,
       image->buf.line[y] + (4 * x))=
       color;

    return;
}

inline uint32_t
image_noclip_pixel_get(
    struct image const*const image,
    int const x,
    int const y)
{
    return *(uint32_t __far*)MK_FP(
       image->buf.selector,
       image->buf.line[y] + (4 * x));
}

extern void
image_line(
    struct image*const image,
    int const x0,
    int const y0,
    int const x1,
    int const y1,
    uint32_t const color);

extern void
image_lineh(
    struct image*const image,
    int const x,
    int const y,
    size_t const len,
    uint32_t const color);

extern void
image_lineh_xor(
    struct image*const image,
    int const x,
    int const y,
    size_t const len);

extern void
image_linev(
    struct image*const image,
    int const x,
    int const y,
    size_t const len,
    uint32_t const color);

extern void
image_linev_xor(
    struct image*const image,
    int const x,
    int const y,
    size_t const len);

#ifdef __cplusplus
}
#endif

#define __IMAGE_H__
#endif
