/*
 mouse.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to FDOSTUI Library. This work is published
 from: United States.
*/
#ifndef __mouse_h__

#  pragma pack(push, 1);

struct mouse_event
{
  unsigned short int m_btn_state;
  unsigned short int m_curs_col;
  unsigned short int m_curs_row;
};

#  pragma pack(pop);

#  ifdef __cplusplus
extern "C"
{
#  endif

  extern short int mouse_initialized;

  extern int
    mouse_get_event(struct mouse_event *const);

  extern int
    mouse_init();

  extern void
    mouse_deinit();

  extern void
    mouse_set_range(unsigned const, unsigned const);

#  ifdef __cplusplus
}
#  endif

#  define __mouse_h__
#endif
