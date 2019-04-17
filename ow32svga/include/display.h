/*
 display.h

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright 
 and related or neighboring rights to ow32svga Library. This work is published 
 from: United States.
*/
#if !defined(__DISPLAY_H__)

#ifdef __cplusplus
extern "C" {
#endif

extern int
display_init_once();

extern void
display_deinit_once();

#ifdef __cplusplus
}
#endif

#define __DISPLAY_H__
#endif
