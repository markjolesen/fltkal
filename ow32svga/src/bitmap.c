/*
 bitmap.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include "bitmap.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern struct bitmap *
  bitmap_new(unsigned const len_x, unsigned const len_y)
{
  struct bitmap *bitmap;
  unsigned limit;

  bitmap = (struct bitmap *)malloc(sizeof(*bitmap));
  bitmap->stride = STRIDE(len_x);
  bitmap->len_x = len_x;
  bitmap->len_y = len_y;
  limit = (bitmap->stride * len_y);
  bitmap->bits.buf = calloc(1, limit);

  return bitmap;
}

extern void
  bitmap_resize(struct bitmap *const bmp,
                unsigned const len_x,
                unsigned const len_y)
{
  unsigned stride;
  unsigned limit;

  stride = STRIDE(len_x);

  if (bmp->stride < stride)
    {
      limit = (stride * len_y);
      bmp->bits.buf = realloc(bmp->bits.buf, limit);
    }

  bmp->stride = stride;
  bmp->len_x = len_x;
  bmp->len_y = len_y;

  return;
}

extern void
  bitmap_free(struct bitmap *const bitmap)
{
  if (bitmap)
    {
      free(bitmap->bits.buf);
      free(bitmap);
    }

  return;
}

extern struct bitmap *
  bitmap_new_from_image(struct image const *const img,
                        struct slice const *const slice)
{
  struct bitmap *bmp;

  bmp = bitmap_new(slice->len_x, slice->len_y);
  bitmap_copy_from_image(bmp, img, slice);

  return bmp;
}

extern void
  bitmap_blt(struct image *const img,
             signed const pos_x,
             signed const pos_y,
             struct bitmap const *const bmp,
             struct slice const *const slice,
             int const use_skip,
             unsigned const skip_color)

{
  uint32_t const *scolors;
  uint32_t __far *dcolors;
  struct slice dest;
  struct slice src;
  unsigned delta_x;
  unsigned delta_y;
  unsigned dest_x;
  unsigned src_x;
  unsigned dest_y;
  unsigned src_y;
  unsigned color;
  int rc;

  do
    {
      dest.pos_x = pos_x;
      dest.len_x = bmp->len_x;
      dest.pos_y = pos_y;
      dest.len_y = bmp->len_y;

      rc = _clip(&dest, &img->clip);

      if (rc)
        {
          break;
        }

      delta_x = dest.pos_x - pos_x;
      delta_y = dest.pos_y - pos_y;

      src.pos_x = slice->pos_x + delta_x;
      src.pos_y = slice->pos_y + delta_y;
      src.len_x = dest.len_x;
      src.len_y = dest.len_y;

      dest_y = dest.pos_y;
      src_y = src.pos_y;

      do
        {
          if (dest.pos_y + dest.len_y <= dest_y)
            {
              break;
            }

          dcolors = (uint32_t __far *)MK_FP(img->buf.selector,
                                            img->buf.line[dest_y]);

          scolors
            = (uint32_t *)&((uint8_t *)bmp->bits.buf)[(bmp->stride * src_y)];

          dest_x = dest.pos_x;
          src_x = src.pos_x;

          do
            {
              if (dest.pos_x + dest.len_x <= dest_x)
                {
                  break;
                }

              color = scolors[src_x];

              if (!(use_skip && (skip_color == color)))
                {
                  dcolors[dest_x] = color;
                }

              dest_x++;
              src_x++;
            }
          while (1);

          src_y++;
          dest_y++;
        }
      while (1);
    }
  while (0);

  return;
}

extern void
  bitmap_copy_from_image(struct bitmap *const bmp,
                         struct image const *const img,
                         struct slice const *const slice)
{
  uint32_t *dbits;
  uint32_t const __far *sbits;
  struct slice src;
  unsigned dest_x;
  unsigned src_x;
  unsigned dest_y;
  unsigned src_y;
  unsigned delta_y;
  unsigned delta_x;
  int rc;

  do
    {
      src.pos_x = slice->pos_x;
      src.pos_y = slice->pos_y;
      src.len_x = slice->len_x;
      src.len_y = slice->len_y;

      rc = _clip(&src, &img->clip);

      if (rc)
        {
          bmp->stride = 0;
          bmp->len_x = 0;
          bmp->len_y = 0;
          break;
        }

      bmp->stride = src.len_x * sizeof(uint32_t);
      bmp->len_x = src.len_x;
      bmp->len_y = src.len_y;

      delta_x = slice->len_x - src.len_x;
      delta_y = slice->len_y - src.len_y;

      dest_y = delta_y;
      src_y = src.pos_y;

      do
        {
          if (src.pos_y + src.len_y <= src_y)
            {
              break;
            }

          dbits
            = (uint32_t *)&((uint8_t *)bmp->bits.buf)[(bmp->stride * dest_y)];

          sbits
            = (uint32_t __far *)MK_FP(img->buf.selector, img->buf.line[src_y]);

          dest_x = delta_x;
          src_x = src.pos_x;

          do
            {
              if (src.pos_x + src.len_x <= src_x)
                {
                  break;
                }

              dbits[dest_x] = sbits[src_x];

              dest_x++;
              src_x++;
            }
          while (1);

          src_y++;
          dest_y++;
        }
      while (1);
    }
  while (0);

  return;
}
