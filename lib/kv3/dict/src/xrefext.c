/*
  kv3_dict_xref_set_external.c

  Copyright (c) 2008-2010, 2014, 2019 Dante University Foundation and Contributors

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
#include "mr7.h"
#include "mstddef.h"
#include "mstring.h"
/**/
#include "dictxref.h"

extern void
  kv3_dict_xref_set_external(struct kv3_dict_xref *const io_xref)
{
  struct kv3_dict_cell *l_cell;
  size_t l_slot;

  do
    {
      if (0 == io_xref)
        {
          break;
        }

      l_cell = &(*io_xref).m_cell[0];

      for (l_slot = 0; kv3_dict_xref_cell_count > l_slot; l_slot++)
        {
          kv3_dict_cell_set_external(l_cell);
          l_cell++;
        }

      l_cell = &(*io_xref).m_cell[(kv3_dict_xref_cell_count - 1)];
      (*l_cell).m_comma_or_cr = mjo_r7_cr;
      (*l_cell).m_space_or_lf = mjo_r7_lf;
    }
  while (0);

  return;
}
