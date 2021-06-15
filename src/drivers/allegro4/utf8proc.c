/* -*- mode: c; c-basic-offset: 2; tab-width: 2; indent-tabs-mode: nil -*- */
/*
 *  Copyright (c) 2015 Steven G. Johnson, Jiahao Chen, Peter Colberg, Tony
 * Kelman, Scott P. Jones, and other contributors. Copyright (c) 2009 Public
 * Software Group e. V., Berlin, Germany
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 */

/*
 *  This library contains derived data from a modified version of the
 *  Unicode data files.
 *
 *  The original data files are available at
 *  http://www.unicode.org/Public/UNIDATA/
 *
 *  Please notice the copyright statement in the file "utf8proc_data.c".
 */

/*
 *  File name:    utf8proc.c
 *
 *  Description:
 *  Implementation of libutf8proc.
 */

#include "utf8proc.h"

#define utf_cont(ch) (((ch)&0xc0) == 0x80)
UTF8PROC_DLLEXPORT utf8proc_ssize_t
  utf8proc_iterate(const utf8proc_uint8_t *str,
                   utf8proc_ssize_t strlen,
                   utf8proc_int32_t *dst)
{
  utf8proc_uint32_t uc;
  const utf8proc_uint8_t *end;

  *dst = -1;
  if (!strlen)
    return 0;
  end = str + ((strlen < 0) ? 4 : strlen);
  uc = *str++;
  if (uc < 0x80)
    {
      *dst = uc;
      return 1;
    }
  // Must be between 0xc2 and 0xf4 inclusive to be valid
  if ((uc - 0xc2) > (0xf4 - 0xc2))
    return UTF8PROC_ERROR_INVALIDUTF8;
  if (uc < 0xe0)
    { // 2-byte sequence
      // Must have valid continuation character
      if (str >= end || !utf_cont(*str))
        return UTF8PROC_ERROR_INVALIDUTF8;
      *dst = ((uc & 0x1f) << 6) | (*str & 0x3f);
      return 2;
    }
  if (uc < 0xf0)
    { // 3-byte sequence
      if ((str + 1 >= end) || !utf_cont(*str) || !utf_cont(str[1]))
        return UTF8PROC_ERROR_INVALIDUTF8;
      // Check for surrogate chars
      if (uc == 0xed && *str > 0x9f)
        return UTF8PROC_ERROR_INVALIDUTF8;
      uc = ((uc & 0xf) << 12) | ((*str & 0x3f) << 6) | (str[1] & 0x3f);
      if (uc < 0x800)
        return UTF8PROC_ERROR_INVALIDUTF8;
      *dst = uc;
      return 3;
    }
  // 4-byte sequence
  // Must have 3 valid continuation characters
  if ((str + 2 >= end) || !utf_cont(*str) || !utf_cont(str[1])
      || !utf_cont(str[2]))
    return UTF8PROC_ERROR_INVALIDUTF8;
  // Make sure in correct range (0x10000 - 0x10ffff)
  if (uc == 0xf0)
    {
      if (*str < 0x90)
        return UTF8PROC_ERROR_INVALIDUTF8;
    }
  else if (uc == 0xf4)
    {
      if (*str > 0x8f)
        return UTF8PROC_ERROR_INVALIDUTF8;
    }
  *dst = ((uc & 7) << 18) | ((*str & 0x3f) << 12) | ((str[1] & 0x3f) << 6)
         | (str[2] & 0x3f);
  return 4;
}

UTF8PROC_DLLEXPORT utf8proc_ssize_t
  utf8proc_encode_char(utf8proc_int32_t uc, utf8proc_uint8_t *dst)
{
  if (uc < 0x00)
    {
      return 0;
    }
  else if (uc < 0x80)
    {
      dst[0] = (utf8proc_uint8_t)uc;
      return 1;
    }
  else if (uc < 0x800)
    {
      dst[0] = (utf8proc_uint8_t)(0xC0 + (uc >> 6));
      dst[1] = (utf8proc_uint8_t)(0x80 + (uc & 0x3F));
      return 2;
      // Note: we allow encoding 0xd800-0xdfff here, so as not to change
      // the API, however, these are actually invalid in UTF-8
    }
  else if (uc < 0x10000)
    {
      dst[0] = (utf8proc_uint8_t)(0xE0 + (uc >> 12));
      dst[1] = (utf8proc_uint8_t)(0x80 + ((uc >> 6) & 0x3F));
      dst[2] = (utf8proc_uint8_t)(0x80 + (uc & 0x3F));
      return 3;
    }
  else if (uc < 0x110000)
    {
      dst[0] = (utf8proc_uint8_t)(0xF0 + (uc >> 18));
      dst[1] = (utf8proc_uint8_t)(0x80 + ((uc >> 12) & 0x3F));
      dst[2] = (utf8proc_uint8_t)(0x80 + ((uc >> 6) & 0x3F));
      dst[3] = (utf8proc_uint8_t)(0x80 + (uc & 0x3F));
      return 4;
    }
  else
    return 0;
}
