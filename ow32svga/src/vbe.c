/*
 vbe.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include "vbe.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dpmi.h"

struct vbe_info_block _vbe_info;
static size_t *vbe_modes = 0;
static size_t vbe_mode_count = 0;

extern void
  vbe_cleanup()
{
  free(vbe_modes);
  vbe_modes = 0;
}

extern int
  vbe_query_installed()
{
  static enum {
    STATE_UNINITIALIZED,
    STATE_INITIALIZED,
    STATE_ERROR
  } state
    = STATE_UNINITIALIZED;
  int rc = 0;
  size_t slot;
  int16_t *modes;

  do
    {
      if (STATE_ERROR == state)
        {
          rc = -1;
          break;
        }

      if (STATE_INITIALIZED == state)
        {
          break;
        }

      rc = vbe_get_info_block(&_vbe_info);

      if (rc)
        {
          break;
        }

      if (0x41534556 != *((uint32_t *)&_vbe_info.vbe_signature[0]))
        {
          rc = -1;
          break;
        }

      if (0x0300 < _vbe_info.vbe_version)
        {
          rc = -1;
          break;
        }

      modes = (int16_t *)dpmi_real2linear(_vbe_info.vbe_video_mode_ptr);

      for (vbe_mode_count = 0; - 1 != modes[vbe_mode_count]; vbe_mode_count++)
        ;

      if (0 == modes)
        {
          rc = -1;
          break;
        }

      vbe_modes = (size_t *)calloc(vbe_mode_count, sizeof(size_t));

      for (slot = 0; vbe_mode_count > slot; slot++)
        {
          vbe_modes[slot] = (size_t)modes[slot];
        }

      state = STATE_INITIALIZED;
    }
  while (0);

  if (rc)
    {
      state = STATE_ERROR;
    }

  return rc;
}

extern int
  vbe_query_mode(size_t const width, size_t const height, size_t const depth)
{
  struct vbe_mode_block info;
  int rc;
  size_t slot;
  int mode;

  do
    {
      mode = -1;

      rc = vbe_query_installed();

      if (rc)
        {
          break;
        }

      for (slot = 0; vbe_mode_count > slot; slot++)
        {
          rc = vbe_get_mode_block(&info, vbe_modes[slot]);

          if (rc)
            {
              continue;
            }

          if (0x90 != (0x90 & info.mod_attr))
            {
              continue;
            }

          if (4 != info.mod_memory_model && 6 != info.mod_memory_model)
            {
              continue;
            }

          if (depth != (size_t)info.mod_bits_per_pixel)
            {
              continue;
            }

          if ((width == (size_t)info.mod_x_resolution)
              && (height == (size_t)info.mod_y_resolution))
            {
              mode = (int)vbe_modes[slot];
              break;
            }
        }
    }
  while (0);

  return mode;
}
