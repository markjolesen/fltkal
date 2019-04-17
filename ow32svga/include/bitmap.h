/*
 bitmap.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__BITMAP_H__)

#include <stddef.h>
#include <stdint.h>
#include "image.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 0)
struct bitmap
{
    int stride;
    size_t width;
    size_t height;
    union
    {
        void const* ref;
        void* buf;
    }bits;
};
#pragma pack(pop)

extern struct bitmap*
bitmap_new(
    size_t const width,
    size_t const height);

extern struct bitmap*
bitmap_new_from_image(
    struct image const*const src,
    int const src_x,
    int const src_y,
    size_t const src_w,
    size_t const src_h);

extern  void
bitmap_free(
    struct bitmap*const bmp);

extern void
bitmap_1bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    uint32_t const color);

extern void
bitmap_xy1bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    int const src_x,
    int const src_y);

extern void
bitmap_8bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    uint32_t const color);

extern void
bitmap_24bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src);

extern void
bitmap_xy24bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    int const src_x,
    int const src_y);

extern void
bitmap_32bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src);

extern void
bitmap_xy32bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    int const src_x,
    int const src_y);

#ifdef __cplusplus
}
#endif

#define __BITMAP_H__
#endif
