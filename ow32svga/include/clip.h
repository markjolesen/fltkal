/*
 clip.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__clip_h__)

#  include <stddef.h>
#  include <stdint.h>

struct slice
{
  signed pos_x;
  signed pos_y;
  unsigned len_x;
  unsigned len_y;
};

struct clip
{
  signed pos_x1;
  signed pos_y1;
  signed pos_x2;
  signed pos_y2;
};

#  ifdef __cplusplus
extern "C"
{
#  endif

  extern int
    _clip(struct slice *const slice, struct clip const *const clip);

#  ifdef __cplusplus
}
#  endif

#  define __clip_h__
#endif
