/*
  version.c

  Copyright (c) 2020-2022 Dante University Foundation and Contributors

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

  This file is part of kv3

  DANTE UNIVERSITY OF AMERICA FOUNDATION INC
  P.O. Box 812158
  Wellesley, MA 02482
  USA
  <http://danteuniversity.org/>
*/
#include "version.h"

#include <stdio.h>

unsigned char const *g_program_name = (unsigned char const *)"kv3";

unsigned char const *g_program_brief
  = (unsigned char const *)"Verb Conjugator";

unsigned char const *g_version = (unsigned char const *)"2022.04.13";

unsigned char const *g_copyright = (unsigned char const *)
  "Copyright (c) 2020-2022 Dante University Foundation and Contributors";

unsigned char const *g_license_brief = (unsigned char const *)
  "The 2-Clause BSD License "
  "<https://opensource.org/licenses/BSD-2-Clause>\n"
  "There is NO WARRANTY, this software is provided \"AS IS.\"\n";

extern void
  version_print()
{
  printf("\n%s %s\n", g_program_name, g_version);
  printf("%s\n", g_copyright);
  printf("%s\n", g_license_brief);

  return;
}
