// drvsys.cxx
//
// "$Id: Fl_System_Driver.cxx 12198 2017-03-14 17:51:20Z manolo $"
//
// A base class for platform specific system calls.
//
// Copyright 2017-2018 The fltkal authors
// Copyright 1998-2016 by Bill Spitzak and others.
//
//                              FLTK License
//                            December 11, 2001
// 
// The FLTK library and included programs are provided under the terms
// of the GNU Library General Public License (LGPL) with the following
// exceptions:
// 
//     1. Modifications to the FLTK configure script, config
//        header file, and makefiles by themselves to support
//        a specific platform do not constitute a modified or
//        derivative work.
// 
//       The authors do request that such modifications be
//       contributed to the FLTK project - send all contributions
//       through the "Software Trouble Report" on the following page:
//  
//            http://www.fltk.org/str.php
// 
//     2. Widgets that are subclassed from FLTK widgets do not
//        constitute a derivative work.
// 
//     3. Static linking of applications and widgets to the
//        FLTK library does not constitute a derivative work
//        and does not require the author to provide source
//        code for the application or widget, use the shared
//        FLTK libraries, or link their applications or
//        widgets against a user-supplied version of FLTK.
// 
//        If you link the application or widget to a modified
//        version of FLTK, then the changes to FLTK must be
//        provided under the terms of the LGPL in sections
//        1, 2, and 4.
// 
//     4. You do not have to provide a copy of the FLTK license
//        with programs that are linked to the FLTK library, nor
//        do you have to identify the FLTK license in your
//        program or documentation as required by section 6
//        of the LGPL.
// 
//        However, programs must still identify their use of FLTK.
//        The following example statement can be included in user
//        documentation to satisfy this requirement:
// 
//            [program/widget] is based in part on the work of
//            the FLTK project (http://www.fltk.org).
// 
//     This library is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Library General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.
// 
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Library General Public License for more details.
// 
//     You should have received a copy of the GNU Library General Public
//     License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
//
//


#include <fl/drvsys.h>
#include <fl/fl.h>
#include <fl/iconfile.h>
#include <fl/fl_utf8.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "flstring.h"
#include <time.h>

const int Fl_System_Driver::fl_NoValue =     0x0000;
const int Fl_System_Driver::fl_WidthValue =  0x0004;
const int Fl_System_Driver::fl_HeightValue = 0x0008;
const int Fl_System_Driver::fl_XValue =      0x0001;
const int Fl_System_Driver::fl_YValue =      0x0002;
const int Fl_System_Driver::fl_XNegative =   0x0010;
const int Fl_System_Driver::fl_YNegative =   0x0020;


Fl_System_Driver::Fl_System_Driver()
{
}


Fl_System_Driver::~Fl_System_Driver()
{
}

void Fl_System_Driver::warning(const char* format, ...) {
  va_list args;
  va_start(args, format);
  Fl::system_driver()->warning(format, args);
  va_end(args);
}

void Fl_System_Driver::warning(const char* format, va_list args) {
  vfprintf(stderr, format, args);
  fputc('\n', stderr);
  fflush(stderr);
}

void Fl_System_Driver::error(const char* format, ...) {
  va_list args;
  va_start(args, format);
  Fl::system_driver()->error(format, args);
  va_end(args);
}

void Fl_System_Driver::error(const char *format, va_list args) {
  vfprintf(stderr, format, args);
  fputc('\n', stderr);
  fflush(stderr);
}

void Fl_System_Driver::fatal(const char* format, ...) {
  va_list args;
  va_start(args, format);
  Fl::system_driver()->fatal(format, args);
  va_end(args);
}

void Fl_System_Driver::fatal(const char *format, va_list args) {
  vfprintf(stderr, format, args);
  fputc('\n', stderr);
  fflush(stderr);
  exit(1);
}

/* the following function was stolen from the X sources as indicated. */

/* Copyright 	Massachusetts Institute of Technology  1985, 1986, 1987 */
/* $XConsortium: XParseGeom.c,v 11.18 91/02/21 17:23:05 rws Exp $ */

/*
 Permission to use, copy, modify, distribute, and sell this software and its
 documentation for any purpose is hereby granted without fee, provided that
 the above copyright notice appear in all copies and that both that
 copyright notice and this permission notice appear in supporting
 documentation, and that the name of M.I.T. not be used in advertising or
 publicity pertaining to distribution of the software without specific,
 written prior permission.  M.I.T. makes no representations about the
 suitability of this software for any purpose.  It is provided "as is"
 without express or implied warranty.
 */

/*
 *    XParseGeometry parses strings of the form
 *   "=<width>x<height>{+-}<xoffset>{+-}<yoffset>", where
 *   width, height, xoffset, and yoffset are unsigned integers.
 *   Example:  "=80x24+300-49"
 *   The equal sign is optional.
 *   It returns a bitmask that indicates which of the four values
 *   were actually found in the string.  For each value found,
 *   the corresponding argument is updated;  for each value
 *   not found, the corresponding argument is left unchanged.
 */

static int ReadInteger(char* string, char** NextString)
{
  int Result = 0;
  int Sign = 1;
  
  if (*string == '+')
    string++;
  else if (*string == '-') {
    string++;
    Sign = -1;
  }
  for (; (*string >= '0') && (*string <= '9'); string++) {
    Result = (Result * 10) + (*string - '0');
  }
  *NextString = string;
  if (Sign >= 0)
    return (Result);
  else
    return (-Result);
}

int Fl_System_Driver::XParseGeometry(const char* string, int* x, int* y,
                   unsigned int* width, unsigned int* height)
{
  int mask = Fl_System_Driver::fl_NoValue;
  char *strind;
  unsigned int tempWidth = 0, tempHeight = 0;
  int tempX = 0, tempY = 0;
  char *nextCharacter;
  
  if ( (string == NULL) || (*string == '\0')) return(mask);
  if (*string == '=')
    string++;  /* ignore possible '=' at beg of geometry spec */
  
  strind = (char *)string;
  if (*strind != '+' && *strind != '-' && *strind != 'x') {
    tempWidth = ReadInteger(strind, &nextCharacter);
    if (strind == nextCharacter)
      return (0);
    strind = nextCharacter;
    mask |= fl_WidthValue;
  }
  
  if (*strind == 'x' || *strind == 'X') {
    strind++;
    tempHeight = ReadInteger(strind, &nextCharacter);
    if (strind == nextCharacter)
      return (0);
    strind = nextCharacter;
    mask |= fl_HeightValue;
  }
  
  if ((*strind == '+') || (*strind == '-')) {
    if (*strind == '-') {
      strind++;
      tempX = -ReadInteger(strind, &nextCharacter);
      if (strind == nextCharacter)
        return (0);
      strind = nextCharacter;
      mask |= fl_XNegative;
      
    } else {
      strind++;
      tempX = ReadInteger(strind, &nextCharacter);
      if (strind == nextCharacter)
        return(0);
      strind = nextCharacter;
    }
    mask |= fl_XValue;
    if ((*strind == '+') || (*strind == '-')) {
      if (*strind == '-') {
        strind++;
        tempY = -ReadInteger(strind, &nextCharacter);
        if (strind == nextCharacter)
          return(0);
        strind = nextCharacter;
        mask |= fl_YNegative;
        
      } else {
        strind++;
        tempY = ReadInteger(strind, &nextCharacter);
        if (strind == nextCharacter)
          return(0);
        strind = nextCharacter;
      }
      mask |= fl_YValue;
    }
  }
  
  /* If strind isn't at the end of the string the it's an invalid
   geometry specification. */
  
  if (*strind != '\0') return (0);
  
  if (mask & fl_XValue)
    *x = tempX;
  if (mask & fl_YValue)
    *y = tempY;
  if (mask & fl_WidthValue)
    *width = tempWidth;
  if (mask & fl_HeightValue)
    *height = tempHeight;
  return (mask);
}

unsigned Fl_System_Driver::utf8towc(const char* src, unsigned srclen, wchar_t* dst, unsigned dstlen) {
  const char* p = src;
  const char* e = src+srclen;
  unsigned count = 0;
  if (dstlen) for (;;) {
    if (p >= e) {
      dst[count] = 0;
      return count;
    }
    if (!(*p & 0x80)) { /* ascii */
      dst[count] = *p++;
    } else {
      int len; unsigned ucs = fl_utf8decode(p,e,&len);
      p += len;
      dst[count] = (wchar_t)ucs;
    }
    if (++count == dstlen) {dst[count-1] = 0; break;}
  }
  /* we filled dst, measure the rest: */
  while (p < e) {
    if (!(*p & 0x80)) p++;
    else {
      int len; fl_utf8decode(p,e,&len);
      p += len;
    }
    ++count;
  }
  return count;
}

unsigned Fl_System_Driver::utf8fromwc(char* dst, unsigned dstlen, const wchar_t* src, unsigned srclen)
{
  unsigned i = 0;
  unsigned count = 0;
  if (dstlen) for (;;) {
    unsigned ucs;
    if (i >= srclen) {dst[count] = 0; return count;}
    ucs = src[i++];
    if (ucs < 0x80U) {
      dst[count++] = ucs;
      if (count >= dstlen) {dst[count-1] = 0; break;}
    } else if (ucs < 0x800U) { /* 2 bytes */
      if (count+2 >= dstlen) {dst[count] = 0; count += 2; break;}
      dst[count++] = 0xc0 | (ucs >> 6);
      dst[count++] = 0x80 | (ucs & 0x3F);
    } else if (ucs >= 0x10000) {
      if (ucs > 0x10ffff) {
        ucs = 0xfffd;
        goto J1;
      }
      if (count+4 >= dstlen) {dst[count] = 0; count += 4; break;}
      dst[count++] = 0xf0 | (ucs >> 18);
      dst[count++] = 0x80 | ((ucs >> 12) & 0x3F);
      dst[count++] = 0x80 | ((ucs >> 6) & 0x3F);
      dst[count++] = 0x80 | (ucs & 0x3F);
    } else {
J1:
      /* all others are 3 bytes: */
      if (count+3 >= dstlen) {dst[count] = 0; count += 3; break;}
      dst[count++] = 0xe0 | (ucs >> 12);
      dst[count++] = 0x80 | ((ucs >> 6) & 0x3F);
      dst[count++] = 0x80 | (ucs & 0x3F);
    }
  }
  /* we filled dst, measure the rest: */
  while (i < srclen) {
    unsigned ucs = src[i++];
    if (ucs < 0x80U) {
      count++;
    } else if (ucs < 0x800U) { /* 2 bytes */
      count += 2;
    } else if (ucs >= 0x10000 && ucs <= 0x10ffff) {
      count += 4;
    } else {
      count += 3;
    }
  }
  return count;
}

unsigned Fl_System_Driver::utf8to_mb(const char* src, unsigned srclen, char* dst, unsigned dstlen) {
  wchar_t lbuf[1024];
  wchar_t* buf = lbuf;
  unsigned length = fl_utf8towc(src, srclen, buf, 1024);
  int ret; // note: wcstombs() returns unsigned(length) or unsigned(-1)
  if (length >= 1024) {
    buf = (wchar_t*)(malloc((length+1)*sizeof(wchar_t)));
    fl_utf8towc(src, srclen, buf, length+1);
  }
  if (dstlen) {
    ret = wcstombs(dst, buf, dstlen);
    if (ret >= (int)dstlen-1) ret = wcstombs(0,buf,0);
  } else {
    ret = wcstombs(0,buf,0);
  }
  if (buf != lbuf) free(buf);
  if (ret >= 0) return (unsigned)ret;
  // on any errors we return the UTF-8 as raw text...
  if (srclen < dstlen) {
    memcpy(dst, src, srclen);
    dst[srclen] = 0;
  } else {
    // Buffer insufficent or buffer query
  }
  return srclen;
}

unsigned Fl_System_Driver::utf8from_mb(char* dst, unsigned dstlen, const char* src, unsigned srclen) {
  wchar_t lbuf[1024];
  wchar_t* buf = lbuf;
  int length;
  unsigned ret;
  length = mbstowcs(buf, src, 1024);
  if (length >= 1024) {
    length = mbstowcs(0, src, 0)+1;
    buf = (wchar_t*)(malloc(length*sizeof(wchar_t)));
    mbstowcs(buf, src, length);
  }
  if (length >= 0) {
    ret = fl_utf8fromwc(dst, dstlen, buf, length);
    if (buf != lbuf) free(buf);
    return ret;
  }
  // errors in conversion return the UTF-8 unchanged
  if (srclen < dstlen) {
    memcpy(dst, src, srclen);
    dst[srclen] = 0;
  } else {
    // Buffer insufficent or buffer query
  }
  return srclen;
}

int Fl_System_Driver::clocale_printf(FILE *output, const char *format, va_list args) {
  return vfprintf(output, format, args);
}

int Fl_System_Driver::filename_expand(char *to,int tolen, const char *from) {
  char *temp = new char[tolen];
  strlcpy(temp,from, tolen);
  char *start = temp;
  char *end = temp+strlen(temp);
  
  int ret = 0;
  
  for (char *a=temp; a<end; ) {	// for each slash component
    char *e; for (e=a; e<end && *e != '/'; e++) {/*empty*/} // find next slash
    const char *value = 0; // this will point at substitute value
    switch (*a) {
      case '~':	// a home directory name
        if (e <= a+1) {	// current user's directory
          value = getenv("HOME");
        } else {	// another user's directory
          char t = *e; *(char *)e = 0;
          value = getpwnam(a+1);
          *(char *)e = t;
        }
        break;
      case '$':		/* an environment variable */
      {char t = *e; *(char *)e = 0; value = getenv(a+1); *(char *)e = t;}
        break;
    }
    if (value) {
      // substitutions that start with slash delete everything before them:
      if (value[0] == '/') start = a;
      int t = (int) strlen(value); if (value[t-1] == '/') t--;
      if ((end+1-e+t) >= tolen) end += tolen - (end+1-e+t);
      memmove(a+t, e, end+1-e);
      end = a+t+(end-e);
      *end = '\0';
      memcpy(a, value, t);
      ret++;
    } else {
      a = e+1;
    }
  }
  strlcpy(to, start, tolen);
  delete[] temp;
  return ret;
}

int Fl_System_Driver::file_browser_load_directory(const char *directory, char *filename,
                                                  size_t name_size, dirent ***pfiles, Fl_File_Sort_F *sort)
{
  return filename_list(directory, pfiles, sort);
}

int Fl_System_Driver::file_type(const char *filename)
{
  return Fl_File_Icon::ANY;
}

void Fl_System_Driver::add_fd(int fd, int when, Fl_FD_Handler cb, void *d)
{
  // nothing to do, reimplement in driver if needed
}

void Fl_System_Driver::add_fd(int fd, Fl_FD_Handler cb, void *d)
{
  // nothing to do, reimplement in driver if needed
}

void Fl_System_Driver::remove_fd(int fd, int when)
{
  // nothing to do, reimplement in driver if needed
}

void Fl_System_Driver::remove_fd(int fd)
{
  // nothing to do, reimplement in driver if needed
}

FILE *Fl_System_Driver::fopen(const char* f, const char *mode) {
  return ::fopen(f, mode);
}

void Fl_System_Driver::open_callback(void (*)(const char *)) {
}

// Get elapsed time since Jan 1st, 1970.
void Fl_System_Driver::gettime(time_t *sec, int *usec) {
  *sec =  time(NULL);
  *usec = 0;
}

//
// End of "$Id: Fl_System_Driver.cxx 12198 2017-03-14 17:51:20Z manolo $".
//