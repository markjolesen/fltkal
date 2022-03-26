/*
  dict.h

  Copyright (c) 2008-2010, 2014, 2019-2020 Dante University Foundation and Contributors

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
#if !defined(__dict_h__)

#  include "dictrow.h"

enum
{
  kv3_dict_row_count_used = 7,
  kv3_dict_row_count = 8,
  kv3_dict_records_max = 2048
};

#  pragma pack(1)
struct kv3_dict
{
  struct kv3_dict_row m_row[kv3_dict_row_count];
};
#  pragma pack()

#  define kv3_dict_filesize_max                                               \
    (sizeof(struct kv3_dict) * kv3_dict_records_max)

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    kv3_dict_set_external(struct kv3_dict *const);

  extern void
    kv3_dict_set_internal(struct kv3_dict *const);

#  if defined(__cplusplus)
}
#  endif

#  define __dict_h__
#endif
