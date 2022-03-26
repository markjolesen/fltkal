/*
  version.h

  Copyright (c) 2020 Dante University Foundation and Contributors

    Permission to use, copy, modify, and distribute this software for any
    purpose with or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

  DANTE UNIVERSITY OF AMERICA FOUNDATION INC
  P.O. Box 812158
  Wellesley, MA 02482
  USA
  <http://danteuniversity.org/>
*/
#ifndef __version_h__

#  include <stddef.h>

extern unsigned char const *g_program_name;
extern unsigned char const *g_program_brief;
extern unsigned char const *g_version;
extern unsigned char const *g_license_brief;

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    version_print();

#  if defined(__cplusplus)
}
#  endif

#  define __version_h__
#endif
