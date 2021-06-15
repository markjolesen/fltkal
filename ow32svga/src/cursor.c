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

#undef STRIDE
#define STRIDE(l) ((l)*4)

#define CURSOR_PIXELS_MAX 72

struct cursor_back
{
  struct bitmap bmp;
  uint32_t data[STRIDE(CURSOR_PIXELS_MAX) * CURSOR_PIXELS_MAX];
};

static struct cursor_front
{
  struct cursor const *cur;
};

enum cursor_flag
{
  FLAG_POS = 0x1,
  FLAG_BACK = 0x2,
  FLAG_SHAPE = 0x4
};

static struct
{
  enum cursor_flag flag;
  int x;
  int y;
  struct cursor_back back;
  struct cursor_front front;
} _cursor = { 0 };

extern void
  cursor_blt()
{
  struct bitmap bmp;
  struct slice slice;

  if ((FLAG_POS & _cursor.flag) && (FLAG_SHAPE & _cursor.flag))
    {
      bmp.stride = STRIDE(_cursor.front.cur->len_x);
      bmp.len_x = _cursor.front.cur->len_x;
      bmp.len_y = _cursor.front.cur->len_y;
      bmp.bits.ref = _cursor.front.cur->data;

      slice.pos_x = 0;
      slice.pos_y = 0;
      slice.len_x = _cursor.front.cur->len_x;
      slice.len_y = _cursor.front.cur->len_y;

      bitmap_blt(_screen, _cursor.x, _cursor.y, &bmp, &slice, 1, 0);
    }

  return;
}

extern void
  cursor_hide()
{
  struct slice slice;

  if ((FLAG_POS & _cursor.flag) && (FLAG_BACK & _cursor.flag))
    {
      slice.pos_x = 0;
      slice.pos_y = 0;
      slice.len_x = _cursor.back.bmp.len_x;
      slice.len_y = _cursor.back.bmp.len_y;
      bitmap_blt(
        _screen, _cursor.x, _cursor.y, &_cursor.back.bmp, &slice, 0, 0);
      _cursor.flag &= ~FLAG_BACK;
    }

  return;
}

extern void
  cursor_show()
{
  struct slice slice;

  if ((FLAG_POS & _cursor.flag) && (FLAG_SHAPE & _cursor.flag)
      && (0 == (FLAG_BACK & _cursor.flag)))
    {
      slice.pos_x = _cursor.x;
      slice.pos_y = _cursor.y;
      slice.len_x = _cursor.front.cur->len_x;
      slice.len_y = _cursor.front.cur->len_y;

      _cursor.back.bmp.stride = STRIDE(_cursor.front.cur->len_x);
      _cursor.back.bmp.len_x = _cursor.front.cur->len_x;
      _cursor.back.bmp.len_y = _cursor.front.cur->len_y;
      _cursor.back.bmp.bits.buf = &_cursor.back.data;

      bitmap_copy_from_image(&_cursor.back.bmp, _screen, &slice);

      _cursor.flag |= FLAG_BACK;

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

  if (FLAG_SHAPE & _cursor.flag)
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

      if ((_screen->len_x - _cursor.front.cur->hot_x - 2) <= to_x)
        {
          to_x = _screen->len_x - 2;
        }

      if ((_screen->len_y - _cursor.front.cur->hot_y - 2) <= to_y)
        {
          to_y = _screen->len_y - 2;
        }

      _cursor.x = to_x - _cursor.front.cur->hot_x;
      _cursor.y = to_y - _cursor.front.cur->hot_y;

      _cursor.flag |= FLAG_POS;

      cursor_show();
    }
}

extern void
  cursor_shape(struct cursor const *const cur)
{
  if ((ptrdiff_t)cur != (ptrdiff_t)_cursor.front.cur)
    {
      if ((FLAG_POS & _cursor.flag) && (FLAG_SHAPE & _cursor.flag))
        {
          cursor_hide();
          _cursor.x += _cursor.front.cur->hot_x;
          _cursor.y += _cursor.front.cur->hot_y;
        }

      _cursor.front.cur = cur;

      if (FLAG_POS & _cursor.flag)
        {
          _cursor.x -= _cursor.front.cur->hot_x;
          _cursor.y -= _cursor.front.cur->hot_y;
        }

      if ((ptrdiff_t)cur)
        {
          _cursor.flag |= FLAG_SHAPE;
          cursor_show();
        }
      else
        {
          _cursor.flag |= ~FLAG_SHAPE;
        }
    }
  return;
}
