/*
 cursor.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include "cursor.h"

#include <string.h>

#include "bitmap.h"

struct cursor_back
{
  struct bitmap bmp;
  uint32_t data[CURSOR_PIXELS_MAX * CURSOR_PIXELS_MAX];
};

enum cursor_mask
{
  CURSOR_MASK_NONE = 0x0,
  CURSOR_MASK_POS = 0x1,
  CURSOR_MASK_BACK = 0x2,
  CURSOR_MASK_SHAPE = 0x4
};

static struct
{
  enum cursor_mask mask;
  int x;
  int y;
  struct cursor_back back;
  struct cursor const *front;
} _cursor = { CURSOR_MASK_NONE };

static void
  cursor_blt()
{
  struct bitmap bmp;
  struct slice slice;

  if ((CURSOR_MASK_POS & _cursor.mask) && (CURSOR_MASK_SHAPE & _cursor.mask))
    {
      bmp.stride = (_cursor.front->len_x * sizeof(uint32_t));
      bmp.len_x = _cursor.front->len_x;
      bmp.len_y = _cursor.front->len_y;
      bmp.bits.buf = (void *)_cursor.front->data;

      slice.pos_x = 0;
      slice.pos_y = 0;
      slice.len_x = _cursor.front->len_x;
      slice.len_y = _cursor.front->len_y;

      bitmap_blt(_screen, _cursor.x, _cursor.y, &bmp, &slice, 1, 0);
    }

  return;
}

extern void
  cursor_hide()
{
  struct slice slice;

  if ((CURSOR_MASK_POS & _cursor.mask) && (CURSOR_MASK_BACK & _cursor.mask))
    {
      _cursor.back.bmp.bits.buf = (void *)_cursor.back.data;

      slice.pos_x = 0;
      slice.pos_y = 0;
      slice.len_x = _cursor.back.bmp.len_x;
      slice.len_y = _cursor.back.bmp.len_y;

      bitmap_blt(
        _screen, _cursor.x, _cursor.y, &_cursor.back.bmp, &slice, 0, 0);

      _cursor.mask &= ~CURSOR_MASK_BACK;
    }

  return;
}

extern void
  cursor_show()
{
  struct slice slice;

  if ((CURSOR_MASK_POS & _cursor.mask) && (CURSOR_MASK_SHAPE & _cursor.mask)
      && (0 == (CURSOR_MASK_BACK & _cursor.mask)))
    {
      _cursor.back.bmp.bits.buf = (void *)_cursor.back.data;

      slice.pos_x = _cursor.x;
      slice.pos_y = _cursor.y;
      slice.len_x = _cursor.front->len_x;
      slice.len_y = _cursor.front->len_y;

      bitmap_copy_from_image(&_cursor.back.bmp, _screen, &slice);

      _cursor.mask |= CURSOR_MASK_BACK;

      cursor_blt();
    }

  return;
}

extern void
  cursor_pos(int32_t const dest_x, int32_t const dest_y)
{
  int32_t to_x;
  int32_t to_y;

  to_x = dest_x;
  to_y = dest_y;

  if (CURSOR_MASK_SHAPE & _cursor.mask)
    {
      cursor_hide();

      if (0 > to_x)
        {
          to_x = 0;
        }

      if (0 > to_y)
        {
          to_y = 0;
        }

      if ((_screen->len_x - _cursor.front->hot_x - 2) <= to_x)
        {
          to_x = _screen->len_x - 2;
        }

      if ((_screen->len_y - _cursor.front->hot_y - 2) <= to_y)
        {
          to_y = _screen->len_y - 2;
        }

      _cursor.x = to_x - _cursor.front->hot_x;
      _cursor.y = to_y - _cursor.front->hot_y;

      _cursor.mask |= CURSOR_MASK_POS;

      cursor_show();
    }
}

extern void
  cursor_shape(struct cursor const *const cur)
{
  if ((ptrdiff_t)cur != (ptrdiff_t)_cursor.front)
    {
      if ((CURSOR_MASK_POS & _cursor.mask)
          && (CURSOR_MASK_SHAPE & _cursor.mask))
        {
          cursor_hide();
          _cursor.x += _cursor.front->hot_x;
          _cursor.y += _cursor.front->hot_y;
        }

      _cursor.front = cur;

      if (CURSOR_MASK_POS & _cursor.mask)
        {
          _cursor.x -= _cursor.front->hot_x;
          _cursor.y -= _cursor.front->hot_y;
        }

      if ((ptrdiff_t)cur)
        {
          _cursor.mask |= CURSOR_MASK_SHAPE;
          cursor_show();
        }
      else
        {
          _cursor.mask |= ~CURSOR_MASK_SHAPE;
        }
    }
  return;
}
