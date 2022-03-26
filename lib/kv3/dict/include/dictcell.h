/*
  dictcell.h

  Copyright (c) 2008-2010, 2019-2020 Dante University Foundation and Contributors

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
#if !defined(__dictcell_h__)

enum
{
  kv3_dict_cell_octets_max = (128 - 4)
};

struct kv3_dict_cell_str
{
  unsigned char m_text[1 + kv3_dict_cell_octets_max];
};

#  pragma pack(1)
struct kv3_dict_cell
{
  unsigned char m_open;
  unsigned char m_text[kv3_dict_cell_octets_max];
  unsigned char m_close;
  unsigned char m_comma_or_cr;
  unsigned char m_space_or_lf;
};
#  pragma pack()

#  if defined(__cplusplus)
extern "C"
{
#  endif

  extern void
    kv3_dict_cell_copy_str(struct kv3_dict_cell *const, unsigned char const *);

  extern void
    kv3_dict_cell_set_external(struct kv3_dict_cell *const);

  extern void
    kv3_dict_cell_set_internal(struct kv3_dict_cell *const);

#  if defined(__cplusplus)
}
#  endif

#  define __dictcell_h__
#endif
