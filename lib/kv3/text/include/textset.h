/*
  textset.h

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
#if !defined(__textset_h__)

#  include "mr7.h"
#  include "mstddef.h"
#  include "mxywh.h"

enum
{
  kv3_text_set_max_blocks = 8,
  kv3_text_set_max_groups = 8,
  kv3_text_set_open = mjo_r7_lbrace,
  kv3_text_set_close = mjo_r7_rbrace,
  kv3_text_set_group_separator = mjo_r7_colon,
  kv3_text_set_list_separator = mjo_r7_pipe
};

struct kv3_text_set_group
{
  unsigned char const *m_block[kv3_text_set_max_blocks];
  size_t m_selected;
  size_t m_count;
};

struct kv3_text_set
{
  struct kv3_text_set_group m_group[kv3_text_set_max_groups];
  size_t m_count;
  size_t m_selected;
  struct mjo_xywh m_bbox;
};

#  define __textset_h__
#endif
