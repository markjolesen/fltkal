/*
 image.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include "image.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dpmi.h"

struct image *_screen = 0;

extern struct image *
  image_new(size_t const len_x, size_t const len_y, int const stride)
{
  struct image *image;
  size_t limit;
  uint32_t addr;
  uint32_t handle;
  uint32_t selector;
  size_t line;

  limit = stride * len_y;
  limit = ((limit + (4096 - 1)) & ~(4096 - 1));

  dpmi_alloc(&addr, &handle, limit);

  selector = dpmi_selector_alloc();
  dpmi_selector_set_base(selector, addr);
  dpmi_selector_set_limit(selector, (limit - 1));

  image = (struct image *)malloc(sizeof(*image));

  image->stride = stride;
  image->len_x = len_x;
  image->len_y = len_y;
  image->buf.line = (uint8_t **)malloc(len_y * sizeof(uint8_t *));
  image->buf.handle = handle;
  image->buf.selector = selector;

  for (line = 0; image->len_y > line; line++)
    {
      image->buf.line[line] = (uint8_t *)(image->stride * line);
    }

  image->clip.pos_x1 = 0;
  image->clip.pos_y1 = 0;
  image->clip.pos_x2 = (len_x - 1);
  image->clip.pos_y2 = (len_y - 1);

  return image;
}

extern void
  image_free(struct image *const image)
{
  dpmi_selector_free(image->buf.selector);

  if (-1 != image->buf.handle)
    {
      dpmi_free(image->buf.handle);
    }

  free(image->buf.line);
  free(image);

  return;
}
