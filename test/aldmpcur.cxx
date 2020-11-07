/*
 aldumpcur.cxx

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to xcur2asm.c. This work is published
 from: United States.
*/
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fl/fl.h>
#include <fl/fl_enums.h>
#include <fl/windbl.h>
#include <fl/btn.h>
#include <allegro.h>

static void
dump_license(FILE *fp)
{

fprintf(fp,
"; Hackneyed cursors\r\n"
";\r\n"
"; Copyright (C) Richard Ferreira\r\n"
";\r\n"
"; Permission is hereby granted, free of charge, to any person obtaining\r\n"
"; a copy of this software and associated documentation files (the\r\n"
"; \"Software\"), to deal in the Software without restriction, including\r\n"
"; without limitation the rights to use, copy, modify, merge, publish,\r\n"
"; distribute, sublicense, and/or sell copies of the Software, and to\r\n"
"; permit persons to whom the Software is furnished to do so, subject to\r\n"
"; the following conditions:\r\n"
"; \r\n"
"; The above copyright notice and this permission notice shall be\r\n"
"; included in all copies or substantial portions of the Software.\r\n"
"; \r\n"
"; THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\r\n"
"; EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\r\n"
"; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\r\n"
"; NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR THE COPYRIGHT HOLDERS\r\n"
"; BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION\r\n"
"; OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH\r\n"
"; THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\r\n"
"; \r\n"
"; Except as contained in this notice, the name(s) of the above copyright\r\n"
"; holders shall not be used in advertising or otherwise to promote the sale,\r\n"
"; use or other dealings in this Software without prior written authorization.\r\n"
";\r\n"
"\r\n\r\n");

};

static void dump_bitmap(
    BITMAP const*const bmp,
    int const hot_x,
    int const hot_y,
    char const *file,
    char const* label)
{
    size_t x;
    size_t y;
    size_t col;
    uint32_t* bits;
    FILE *fp;

    fp= fopen(file, "wb");

    if (0 == fp)
    {
        return;
    }

    dump_license(fp);

    fprintf(fp, ".model flat\r\n\r\n");
    fprintf(fp, ".data\r\n\r\n");
    fprintf(fp, "public %s\r\n", label);

    fprintf(fp, "%s label dword\r\n", label);
    fprintf(fp, "    dd %d, %d\r\n", bmp->w, bmp->h);
    fprintf(fp, "    dd %d, %d\r\n", hot_x, hot_y);

    col= 0;
    fprintf(fp, "    dd ");

    for (y= 0; bmp->h > y; y++)
    {
        bits= (uint32_t*)bmp->line[y];
        for (x= 0; bmp->w > x; x++)
        {

            if (5 == col) 
            {
                fprintf(fp, "\r\n");
                fprintf(fp, "    dd ");
                col= 0;
            }

            if (col)
            {
                fprintf(fp, ", ");
            }

	    if (0xff00ff != *bits)
	    {
		fprintf(fp, "0%06xh", *bits);
	    }
	    else
	    {
		fprintf(fp, "0%06xh", 0);
	    }
            bits++;
            col++;
        }
    }

    fprintf(fp, "\r\n\r\nend\r\n");

    fclose(fp);

}

extern BITMAP* cursor_get(int &hot_x, int &hot_y, Fl_Cursor const c);

void dump_cb(Fl_Widget*, void*)
{
    int hot_x, hot_y;
    BITMAP* bmp;

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_CROSS);
    dump_bitmap(bmp, hot_x, hot_y, "xcrossh_.asm", "__cursor_crossh");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_WAIT);
    dump_bitmap(bmp, hot_x, hot_y, "xwait_.asm", "__cursor_wait");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_INSERT);
    dump_bitmap(bmp, hot_x, hot_y, "xinsert_.asm", "__cursor_insert");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_HAND);
    dump_bitmap(bmp, hot_x, hot_y, "xhand_.asm", "__cursor_hand");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_HELP);
    dump_bitmap(bmp, hot_x, hot_y, "xhelp_.asm", "__cursor_help");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_MOVE);
    dump_bitmap(bmp, hot_x, hot_y, "xmove_.asm", "__cursor_move");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_NS);
    dump_bitmap(bmp, hot_x, hot_y, "xns_.asm", "__cursor_ns");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_WE);
    dump_bitmap(bmp, hot_x, hot_y, "xwe_.asm", "__cursor_we");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_NWSE);
    dump_bitmap(bmp, hot_x, hot_y, "xnwse_.asm", "__cursor_nwse");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_NESW);
    dump_bitmap(bmp, hot_x, hot_y, "xnesw_.asm", "__cursor_nesw");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_N);
    dump_bitmap(bmp, hot_x, hot_y, "xn_.asm", "__cursor_n");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_NE);
    dump_bitmap(bmp, hot_x, hot_y, "xne_.asm", "__cursor_ne");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_E);
    dump_bitmap(bmp, hot_x, hot_y, "xe_.asm", "__cursor_e");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_SE);
    dump_bitmap(bmp, hot_x, hot_y, "xse_.asm", "__cursor_se");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_S);
    dump_bitmap(bmp, hot_x, hot_y, "xs_.asm", "__cursor_s");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_SW);
    dump_bitmap(bmp, hot_x, hot_y, "xsw_.asm", "__cursor_sw");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_W);
    dump_bitmap(bmp, hot_x, hot_y, "xw_.asm", "__cursor_w");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_NW);
    dump_bitmap(bmp, hot_x, hot_y, "xnw_.asm", "__cursor_nw");

    bmp= cursor_get(hot_x, hot_y, FL_CURSOR_NONE);
    dump_bitmap(bmp, hot_x, hot_y, "xnone_.asm", "__cursor_none");

    return;
}

int main(int argc, char ** argv)
{
  Fl_Double_Window* window = new Fl_Double_Window(40,30);

  Fl_Button* btn= new Fl_Button(0,0,40,30,"Dump");
  btn->callback(dump_cb);

  window->end();
  window->show();
  return Fl::run();
}
