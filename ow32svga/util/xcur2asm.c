/*
 xcur2asm.c

 License CC0 PUBLIC DOMAIN

 To the extent possible under law, Mark J. Olesen has waived all copyright
 and related or neighboring rights to xcur2asm.c. This work is published
 from: United States.
*/
/*
 * gcc -o xcur2asm xcur2asm.c -lXcursor
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xcursor/Xcursor.h>

static void
license_dump()
{

printf(
"; Hackneyed cursors\r\n\r\n"
"; Copyright (C) Richard Ferreira\r\n\r\n"
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

static void
image_dump(
	XcursorImage const*const image,
	char const* label,
	size_t const size)
{
	size_t col;
	size_t x;
	size_t y;
	uint8_t a;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t const* bits;

	license_dump();

	printf(".model flat\r\n\r\n");
	printf(".data\r\n\r\n");
	printf("public %s\r\n", label);

	printf("%s label dword\r\n", label);
	printf("    dd %ld, %ld\r\n", size, size);
	printf("    dd %d, %d\r\n", image->xhot, image->yhot);

	bits= (uint8_t const*)image->pixels;

	col= 0;
	printf("    dd ");

	for (y= 0; image->height > y; y++)
	{
		for (x= 0; image->width > x; x++)
		{
			if (5 == col) 
			{
				printf("\r\n");
				printf("    dd ");
				col= 0;
			}

			if (col)
			{
				printf(", ");
			}

			a= *bits++;
			r= *bits++;
			g= *bits++;
			b= *bits++;

			printf("0%02x%02x%02xh", r, g, b);
			col++;
		}
	}

	printf("\r\n\r\nend\r\n");

	return;
}

int main(int argc, char **argv)
{
	int rc;
	FILE *fp;
	XcursorImage* image;
	size_t size;

	rc= -1;
	fp= 0;

	do
	{

		if (4 != argc)
		{
			printf("Usage: %s infile label size\n", argv[0]);
			break;
		}

		fp= fopen(argv[1], "rb");

		if (!fp)
		{
			printf("Unable to open '%s'\n", argv[1]);
			break;
		}

		size= atoi(argv[3]);
		image= XcursorFileLoadImage(fp, size);

		if (image)
		{
			image_dump(image, argv[2], size);
		}


	}while(0);

	if (fp)
	{
		fclose(fp);
	}

	return rc;
}
