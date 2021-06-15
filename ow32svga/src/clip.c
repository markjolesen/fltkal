/*
 clip.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include "clip.h"

extern int
  _clip(struct slice *const slice, struct clip const *const clip)
{
  int rc;
  signed value;
  signed diff;

  rc = -1;

  do
    {
      if (0 == slice->len_x)
        {
          break;
        }

      if (0 == slice->len_y)
        {
          break;
        }

      if (clip->pos_x2 < slice->pos_x)
        {
          break;
        }

      if (clip->pos_y2 < slice->pos_y)
        {
          break;
        }

      if (clip->pos_x1 > slice->pos_x)
        {
          diff = (clip->pos_x1 - slice->pos_x);
          slice->pos_x += diff;

          value = (((signed)slice->len_x) - diff);
          slice->len_x = ((0 <= value) ? value : 0);
          continue;
        }

      if (clip->pos_y1 > slice->pos_y)
        {
          diff = (clip->pos_y1 - slice->pos_y);
          slice->pos_y += diff;

          value = (((signed)slice->len_y) - diff);
          slice->len_y = ((0 <= value) ? value : 0);
          continue;
        }

      value = (slice->pos_x + slice->len_x);

      if (clip->pos_x2 < value)
        {
          diff = ((value - clip->pos_x2) - (signed)slice->len_x);
          slice->len_x = ((0 <= diff) ? diff : 0);
          continue;
        }

      value = (slice->pos_y + slice->len_y);

      if (clip->pos_y2 < value)
        {
          diff = ((value - clip->pos_y2) - (signed)slice->len_y);
          slice->len_y = ((0 <= diff) ? diff : 0);
          continue;
        }

      rc = 0;
      break;
    }
  while (1);

  return rc;
}
