/*
 image.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__IMAGE_H__)

#  include <i86.h>
#  include <stddef.h>
#  include <stdint.h>

#  include "clip.h"

#  ifdef __cplusplus
extern "C"
{
#  endif

#  pragma pack(push, 0)
  struct image
  {
    signed stride;
    unsigned len_x;
    unsigned len_y;
    struct
    {
      uint8_t **line;
      unsigned handle;
      unsigned selector;
    } buf;
    struct clip clip;
  };
#  pragma pack(pop)

  extern struct image *_screen;

  extern struct image *
    image_new(unsigned const, unsigned const, int const);

  extern void
    image_free(struct image *const);

  inline void
    image_set_clip(struct image *const img,
                   unsigned const x1,
                   unsigned const y1,
                   unsigned const x2,
                   unsigned const y2)
  {
    img->clip.pos_x1 = x1;
    img->clip.pos_y1 = y1;
    img->clip.pos_x2 = x2;
    img->clip.pos_y2 = y2;

    return;
  }

  extern void
    image_blt_exact(struct image *const, struct image const *const);

  extern void
    image_noclip_blt(struct image *const,
                     signed const,
                     signed const,
                     struct image const *const);

  extern void
    image_fill(struct image *const, unsigned const);

  extern void
    image_fill_area(struct image *const,
                    signed const,
                    signed const,
                    unsigned const,
                    unsigned const,
                    uint32_t const);

  extern void
    image_pixel_put(struct image *const,
                    signed const,
                    signed const,
                    uint32_t const);

  inline void
    image_noclip_pixel_put(struct image *const img,
                           signed const pos_x,
                           signed const pos_y,
                           uint32_t const color)
  {
    *(unsigned __far *)MK_FP(img->buf.selector,
                             img->buf.line[pos_y] + (4 * pos_x))
      = color;

    return;
  }

  inline unsigned
    image_noclip_pixel_get(struct image const *const img,
                           int const pos_x,
                           int const pos_y)
  {
    return *(unsigned __far *)MK_FP(img->buf.selector,
                                    img->buf.line[pos_y] + (4 * pos_x));
  }

  extern void
    image_line(struct image *const,
               signed const,
               signed const,
               signed const,
               signed const,
               uint32_t const);

  extern void
    image_lineh(struct image *const,
                signed const,
                signed const,
                unsigned const,
                uint32_t const);

  extern void
    image_lineh_xor(struct image *const,
                    signed const,
                    signed const,
                    unsigned const);

  extern void
    image_linev(struct image *const,
                signed const,
                signed const,
                unsigned const,
                unsigned const);

  extern void
    image_linev_xor(struct image *const,
                    signed const,
                    signed const,
                    unsigned const);

#  ifdef __cplusplus
}
#  endif

#  define __IMAGE_H__
#endif
