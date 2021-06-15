/*
   Bressenham Algorithim to plot a line
*/
#include <stdlib.h>

#include "image.h"

extern void
  image_line(struct image *const image,
             int const x0,
             int const y0,
             int const x1,
             int const y1,
             uint32_t const color)
{
  int dx = abs(x1 - x0);
  int sx = (x0 < x1) ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = (y0 < y1) ? 1 : -1;
  int err = (dx + dy);
  int e2;
  int x = x0;
  int y = y0;

  do
    {
      if (x0 == x1)
        {
          if (y1 > y0)
            {
              dy = y1 - y0 + 1;
              y = y0;
            }
          else
            {
              dy = y0 - y1 + 1;
              y = y1;
            }
          image_linev(image, x0, y, dy, color);
          break;
        }

      if (y0 == y1)
        {
          if (x1 > x0)
            {
              dx = x1 - x0 + 1;
              x = x0;
            }
          else
            {
              dx = x0 - x1 + 1;
              x = x1;
            }
          image_lineh(image, x, y0, dx, color);
          break;
        }

      for (;;)
        {
          if ((0 <= x) && (image->len_x > x) && (0 <= y) && (image->len_y > y))
            {
              image_noclip_pixel_put(image, x, y, color);
            }
          if (x == x1 && y == y1)
            break;
          e2 = 2 * err;
          if (e2 >= dy)
            {
              err += dy;
              x += sx;
            }
          if (e2 <= dx)
            {
              err += dx;
              y += sy;
            }
        }
    }
  while (0);

  return;
}
