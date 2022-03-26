/*
  text.h

  Copyright (c) 2008-2011, 2020 Dante University Foundation and Contributors

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
#if !defined(__text_h__)

#  include "dict.h"
#  include "textcell.h"

struct kv3_text
{
  struct kv3_dict m_dict;
  struct kv3_text_cell m_cell[kv3_dict_row_count][kv3_dict_row_cell_count];
  size_t m_len_x[kv3_dict_row_cell_count];
  int m_is_hidden;
};

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    kv3_text_parse_once(struct kv3_text *const);

#  if defined(__cplusplus)
}
#  endif

#  define __text_h__
#endif
