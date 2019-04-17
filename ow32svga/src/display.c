/*
 display.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "image.h"
#include "vbe.h"
#include "dpmi.h"

static int16_t video_mode_restore= -1;

static int
display_create_image_screen(
    int const mode)
{
    struct vbe_mode_block info;
    int rc;
    uint32_t addr;
    size_t line;
    size_t limit;

    do
    {

        rc= vbe_get_mode_block(&info, (int16_t)mode);

        if (rc)
        {
            break;
        }

        _screen= (struct image*)calloc(1, sizeof(*_screen));
        _screen->stride= info.mod_bytes_per_scan_line;
        _screen->width= info.mod_x_resolution;
        _screen->height= info.mod_y_resolution;
        _screen->buf.handle= -1;
        _screen->buf.selector= dpmi_selector_alloc();
        limit= (info.mod_bytes_per_scan_line * info.mod_y_resolution);
        limit= ((limit + (4096-1)) & ~(4096-1));
        addr= dpmi_physical2linear(info.mod_phys_base_ptr, (limit - 1));
        dpmi_selector_set_base(_screen->buf.selector, addr);
        dpmi_selector_set_limit(_screen->buf.selector, (limit - 1));
        _screen->buf.line= (uint8_t**)malloc(_screen->height * sizeof(uint8_t*));

        for (line= 0; _screen->height > line; line++)
        {
            _screen->buf.line[line]= (uint8_t*)(_screen->stride * line);
        }

        _screen->clip.x1= 0;
        _screen->clip.y1= 0;
        _screen->clip.x2= (info.mod_x_resolution - 1);
        _screen->clip.y2= (info.mod_y_resolution - 1);

    }while(0);

    return rc;
}

static int16_t
display_auto_set_mode()
{
    static struct
    {
        size_t width;
        size_t height;
    } res[] =
    {
        {1400, 1050},
        {1024, 768},
        {800, 600},
        {640, 480}
    };
    int mode;
    int rc= -1;
    size_t slot;

    for (slot= 0; (sizeof(res) / sizeof(res[0])) > slot; slot++)
    {
        mode= vbe_query_mode(res[slot].width, res[slot].height, 32);
        if (-1 != mode)
        {
            rc= vbe_set_mode((0x4000 | mode));
            if (0 == rc)
            {
                rc= mode;
                break;
            }
        }
    }

    return rc;
}

extern int
display_init_once()
{
    static enum {
        STATE_UNINITIALIZED,
        STATE_INITIALIZED,
        STATE_ERROR
    } state= STATE_UNINITIALIZED;
    int rc= 0;
    int16_t mode;

    do
    {

        if (STATE_ERROR == state)
        {
            rc= -1;
            break;
        }

        if (STATE_INITIALIZED == state)
        {
            break;
        }

        rc= vbe_query_installed();

        if (rc)
        {
            break;
        }

        video_mode_restore= vbe_get_mode();

        if (-1 == video_mode_restore)
        {
            rc= -1;
            break;
        }

        mode= display_auto_set_mode();

        if (-1 == mode)
        {
            rc= -1;
            break;
        }

        rc= display_create_image_screen(mode);

        if (rc)
        {
            display_deinit_once();
            break;
        }

        state= STATE_INITIALIZED;

    }while(0);

    if (rc)
    {
        state= STATE_ERROR;
    }

    return rc;
}

extern void
display_deinit_once()
{

    if (_screen)
    {
        dpmi_selector_free(_screen->buf.selector);
        free(_screen->buf.line);
        free(_screen);
        _screen= 0;
    }

    if (-1 != video_mode_restore)
    {
        vbe_set_mode(video_mode_restore);
        video_mode_restore= -1;
    }

    vbe_cleanup();

    return;
}
