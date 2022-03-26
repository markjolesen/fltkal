/*
  kv3_text_cell_parse.c

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

   This file is part of kv3

   DANTE UNIVERSITY OF AMERICA FOUNDATION INC
   P.O. Box 812158
   Wellesley, MA 02482
   USA
   <http://danteuniversity.org/>
*/
#include "mstddef.h"
#include "mstring.h"
#include "mu8.h"
/**/
#include "textcell.h"

#ifdef __cplusplus
extern "C"
{
#endif

  extern void
    kv3_text_set_parse(struct kv3_text_set *const, unsigned char **const);

  extern void
    kv3_text_subject_parse(unsigned char const **const, unsigned char **const);

  extern void
    kv3_text_link_parse(struct kv3_text_link *const, unsigned char **const);

  extern void
    kv3_text_cell_parse(struct kv3_text_cell *const, unsigned char *);

#ifdef __cplusplus
}
#endif

static void
  kv3_text_cell_push(struct kv3_text_cell *const io_cell,
                     unsigned char *io_block)
{
  struct kv3_text_seg *l_seg;

  if (kv3_text_cell_max_segs > (*io_cell).m_count)
    {
      mjo_u8_trim(io_block);

      if (*io_block)
        {
          l_seg = &(*io_cell).m_seg[(*io_cell).m_count];

          memset(l_seg, 0, sizeof(*l_seg));

          (*l_seg).m_variant = kv3_text_block_variant_text;
          (*l_seg).m_block.m_str = io_block;

          (*io_cell).m_count++;
        }
    }

  return;
}

extern void
  kv3_text_cell_parse(struct kv3_text_cell *const io_cell,
                      unsigned char *io_block)
{
  unsigned char *l_head;
  struct kv3_text_seg *l_seg;
  unsigned char *l_tail;

  memset(io_cell, 0, sizeof(*io_cell));

  l_head = io_block;
  l_tail = io_block;

  do
    {
      if (0 == *l_tail)
        {
          kv3_text_cell_push(io_cell, l_head);
          break;
        }

      switch (*l_tail)
        {
        case kv3_text_subject_open:
          *l_tail++ = 0;

          kv3_text_cell_push(io_cell, l_head);

          l_seg = &(*io_cell).m_seg[(*io_cell).m_count];
          memset(l_seg, 0, sizeof(*l_seg));
          kv3_text_subject_parse(&(*l_seg).m_block.m_str, &l_tail);

          if (l_seg->m_block.m_str)
            {
              if (kv3_text_cell_max_segs > (*io_cell).m_count)
                {
                  l_seg->m_variant = kv3_text_block_variant_subject;
                  (*io_cell).m_count++;
                }
            }

          l_head = l_tail;
          break;
        case kv3_text_link_open:
          *l_tail++ = 0;

          kv3_text_cell_push(io_cell, l_head);

          l_seg = &(*io_cell).m_seg[(*io_cell).m_count];
          memset(l_seg, 0, sizeof(*l_seg));
          kv3_text_link_parse(&(*l_seg).m_block.m_link, &l_tail);

          if (-1 != (ssize_t)l_seg->m_block.m_link.m_slot)
            {
              if (kv3_text_cell_max_segs > (*io_cell).m_count)
                {
                  l_seg->m_variant = kv3_text_block_variant_link;
                  (*io_cell).m_count++;
                }
            }

          l_head = l_tail;
          break;
        case kv3_text_set_open:
          *l_tail++ = 0;

          kv3_text_cell_push(io_cell, l_head);

          l_seg = &(*io_cell).m_seg[(*io_cell).m_count];
          memset(l_seg, 0, sizeof(*l_seg));
          kv3_text_set_parse(&(*l_seg).m_block.m_set, &l_tail);

          if (l_seg->m_block.m_set.m_count)
            {
              if (kv3_text_cell_max_segs > (*io_cell).m_count)
                {
                  l_seg->m_variant = kv3_text_block_variant_set;
                  (*io_cell).m_count++;
                }
            }

          l_head = l_tail;
          break;
        default:
          l_tail++;
          break;
        }
    }
  while (1);

  return;
}
