/*
 bitmap.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to ow32svga Library. This work is published
 from: United States.
*/
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

extern struct bitmap*
bitmap_new(
    size_t const width,
    size_t const height)
{
    struct bitmap* bitmap;
    size_t limit;

    limit= (width * height * 4);
    bitmap= (struct bitmap*)malloc(sizeof(*bitmap));
    bitmap->width= width;
    bitmap->height= height;
    bitmap->bits.buf= calloc(1, limit);
    bitmap->stride= width;

    return bitmap;
}

extern void
bitmap_free(
    struct bitmap*const bitmap)
{

    if (bitmap)
    {
        free(bitmap->bits.buf);
        free(bitmap);
    }
  
    return;
}

extern struct bitmap*
bitmap_new_from_image(
    struct image const*const src,
    int const src_x,
    int const src_y,
    size_t const src_w,
    size_t const src_h)
{
    struct bitmap* bitmap;
    uint32_t* dbits;
    uint32_t const __far* sbits;
    int y;
    int x;
    size_t row;
    size_t col;

    bitmap= bitmap_new(src_w, src_h);
    dbits= (uint32_t*)bitmap->bits.buf;

    for (row= 0, y= src_y; (src_h > row) && (src->height > y); row++, y++)
    {
        if (0 <= y)
        {
            sbits= (uint32_t const __far *)MK_FP(src->buf.selector, src->buf.line[y]);
            for (col= 0, x= src_x; (src_w > col) && (src->width > x); col++, x++)
            {
                if (0 <= x)
                {
                    dbits[col]= sbits[x];
                }
            }
        }
        dbits+= bitmap->stride;
    }

    return bitmap;
}

extern void
bitmap_xy1bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    int const src_x,
    int const src_y)
{

    do
    {

        if ((0 == src_x) && (0 == src_y))
        {
            bitmap_1bpp_blt(dest, dest_x, dest_y, src, 0xffffff);
            break;
        }

    }while(0);

    return;
}

extern void
bitmap_xy24bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    int const src_x,
    int const src_y)
{
    struct bitmap bmp;
    uint32_t color;
    uint32_t *dbits;
    uint8_t* line;
    uint8_t* sbits;
    size_t limit;
    size_t row;
    size_t col;

    do
    {

        if ((0 == src_x) && (0 == src_y))
        {
            bitmap_24bpp_blt(dest, dest_x, dest_y, src);
            break;
        }

        if (0 > src_x)
        {
            break;
        }

        if (0 > src_y)
        {
            break;
        }

        if (src->width <= src_x)
        {
            break;
        }

        if (src->height <= src_y)
        {
            break;
        }

        bmp.width= (src->width - src_x);
        bmp.height= (src->height - src_y); 
        limit= (bmp.width * bmp.height * 4);
        bmp.bits.buf= calloc(1, limit);
        bmp.stride= bmp.width;

        dbits= bmp.bits.buf;

        for (row= src_y; row < src->height; row++)
        {
            line= &((uint8_t*)src->bits.buf)[row * src->stride * 3];
            sbits= &line[src_x * 3];
            for (col= 0; col < bmp.width; col++)
            {
                color= (*sbits++);
                color|= (*sbits++ << 8);
                color|= (*sbits++ << 16);
                *dbits++= color;
            }
        }

        bitmap_32bpp_blt(dest, dest_x, dest_y, &bmp);
        free(bmp.bits.buf);

    }while(0);


    return;
}

extern void
bitmap_xy32bpp_blt(
    struct image *const dest,
    int const dest_x,
    int const dest_y,
    struct bitmap const*const src,
    int const src_x,
    int const src_y)
{
    struct bitmap bmp;
    uint32_t *dbits;
    uint32_t* line;
    uint32_t* sbits;
    uint32_t color;
    size_t limit;
    size_t row;
    size_t col;

    do
    {

        if ((0 == src_x) && (0 == src_y))
        {
            bitmap_32bpp_blt(dest, dest_x, dest_y, src);
            break;
        }

        if (0 > src_x)
        {
            break;
        }

        if (0 > src_y)
        {
            break;
        }

        if (src->width <= src_x)
        {
            break;
        }

        if (src->height <= src_y)
        {
            break;
        }

        bmp.width= (src->width - src_x);
        bmp.height= (src->height - src_y); 
        limit= (bmp.width * bmp.height * 4);
        bmp.bits.buf= calloc(1, limit);
        bmp.stride= bmp.width;

        dbits= bmp.bits.buf;

        for (row= src_y; row < src->height; row++)
        {
            line= &((uint32_t*)src->bits.buf)[row * src->stride];
            sbits= &line[src_x];
            for (col= 0; col < bmp.width; col++)
            {
                color= (*sbits++);
                *dbits++= color;
            }
        }

        bitmap_32bpp_blt(dest, dest_x, dest_y, &bmp);
        free(bmp.bits.buf);

    }while(0);


    return;
}
