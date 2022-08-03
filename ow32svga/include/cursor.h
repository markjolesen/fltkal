/*
 cursor.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#if !defined(__cursor_h__)

#  include <stddef.h>
#  include <stdint.h>

#  include "image.h"

#  define CURSOR_PIXELS_MAX 72

#  ifdef __cplusplus
extern "C"
{
#  endif

#  pragma pack(push, 0)
  struct cursor
  {
    unsigned len_x;
    unsigned len_y;
    unsigned hot_x;
    unsigned hot_y;
    unsigned data[1];
  };
#  pragma pack(pop)

  extern struct cursor _cursor_arrow;
  extern struct cursor _cursor_crossh;
  extern struct cursor _cursor_e;
  extern struct cursor _cursor_ew;
  extern struct cursor _cursor_hand;
  extern struct cursor _cursor_help;
  extern struct cursor _cursor_insert;
  extern struct cursor _cursor_move;
  extern struct cursor _cursor_n;
  extern struct cursor _cursor_ne;
  extern struct cursor _cursor_nesw;
  extern struct cursor _cursor_ns;
  extern struct cursor _cursor_nw;
  extern struct cursor _cursor_nwse;
  extern struct cursor _cursor_s;
  extern struct cursor _cursor_se;
  extern struct cursor _cursor_sw;
  extern struct cursor _cursor_w;
  extern struct cursor _cursor_wait;

  extern void
    cursor_pos(signed const, signed const);

  extern void
    cursor_shape(struct cursor const *const);

  extern void
    cursor_hide();

  extern void
    cursor_show();

#  ifdef __cplusplus
}
#  endif

#  define __cursor_h__
#endif
