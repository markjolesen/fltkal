/*
 bitmap.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__BITMAP_H__)

#  include <stddef.h>
#  include <stdint.h>

#  include "image.h"

#  pragma pack(push, 0)
struct bitmap
{
  signed stride;
  unsigned len_x;
  unsigned len_y;
  union
  {
    void const *ref;
    void *buf;
  } bits;
};
#  pragma pack(pop)

#  define STRIDE(l) (((((l)*32) + 31) / 32) * 4)

#  ifdef __cplusplus
extern "C"
{
#  endif

  extern struct bitmap *
    bitmap_new(unsigned const, unsigned const);

  extern struct bitmap *
    bitmap_new_from_image(struct image const *const,
                          struct slice const *const);

  extern void
    bitmap_free(struct bitmap *const);

  extern void
    bitmap_resize(struct bitmap *const, unsigned const, unsigned const);

  extern void
    bitmap_blt(struct image *const,
               signed const,
               signed const,
               struct bitmap const *const,
               struct slice const *const,
               int const,
               unsigned const);

  extern void
    bitmap_8bpp_blt(struct image *constdest,
                    signed const,
                    signed const,
                    struct bitmap const *const,
                    uint32_t const);

  extern void
    bitmap_copy_from_image(struct bitmap *const dest,
                           struct image const *const src,
                           struct slice const *const slice);

#  ifdef __cplusplus
}
#  endif

#  define __BITMAP_H__
#endif
