/*
  version.c

  Copyright (c) 2020 Dante University Foundation and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

     1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY Dante University Foundation ``AS IS'' AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL Dante University Foundation OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of Dante University Foundation.

  Dante University Foundation
  P.O. Box 812158
  Wellesley, MA 02482
  USA
  www.danteuniversity.org
*/
#include <stdio.h>

unsigned char const *g_program_name = (unsigned char const *)"kv3tocsv";

unsigned char const *g_program_brief
  = (unsigned char const *)"Export kv3 database to CSV";

unsigned char const *g_version = (unsigned char const *)"2020.07.04";

unsigned char const *g_copyright = (unsigned char const *)
  "Copyright (c) 2020 " "Dante University Foundation and Contributors";

unsigned char const *g_license_brief = (unsigned char const *)
  "The 2-Clause BSD License "
  "<https://opensource.org/licenses/BSD-2-Clause>\n"
  "There is NO WARRANTY, this software is provided \"AS IS.\"\n";

extern void
  version_print()
{
  printf("%s %s\n", g_program_name, g_version);
  printf("%s\n", g_copyright);
  printf("%s\n", g_license_brief);
  printf("\n");

  return;
}
