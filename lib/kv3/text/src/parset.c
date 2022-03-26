/*
  kv3_text_set_parse.c

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

#ifdef __cplusplus
}
#endif

static void
  push_subject(struct kv3_text_set_group *io_group, unsigned char *io_block)
{
  if (kv3_text_set_max_blocks > (*io_group).m_count)
    {
      (*io_group).m_block[(*io_group).m_count] = io_block;
      (*io_group).m_count++;
    }

  return;
}

static void
  parse_group(struct kv3_text_set_group *io_group, unsigned char *io_block)
{
  unsigned char *l_head;
  unsigned char *l_tail;

  l_head = io_block;

  do
    {
      l_tail
        = (unsigned char *)strchr((char *)l_head, kv3_text_set_list_separator);

      if (l_tail)
        {
          *l_tail++ = 0;
          push_subject(io_group, l_head);
          l_head = l_tail;
        }
      else
        {
          push_subject(io_group, l_head);
          break;
        }
    }
  while (1);

  return;
}

void
  push_group(struct kv3_text_set *const io_set, unsigned char *io_block)
{
  struct kv3_text_set_group *l_group;

  if (kv3_text_set_max_groups > (*io_set).m_count)
    {
      l_group = &(*io_set).m_group[(*io_set).m_count];
      parse_group(l_group, io_block);

      if ((*l_group).m_count)
        {
          (*io_set).m_count++;
        }
    }

  return;
}

static void
  parse_set(struct kv3_text_set *const io_set, unsigned char *io_block)
{
  unsigned char *l_head;
  unsigned char *l_tail;

  l_head = io_block;

  do
    {
      l_tail = (unsigned char *)strchr((char *)l_head,
                                       kv3_text_set_group_separator);

      if (l_tail)
        {
          *l_tail++ = 0;
          push_group(io_set, l_head);
          l_head = l_tail;
        }
      else
        {
          push_group(io_set, l_head);
          break;
        }
    }
  while (1);

  return;
}

extern void
  kv3_text_set_parse(struct kv3_text_set *const io_set,
                     unsigned char **const io_block)
{
  unsigned char *l_tail;
  unsigned char *l_head;

  memset(io_set, 0, sizeof(*io_set));

  l_tail = (*io_block);
  l_head = l_tail;

  do
    {
      if (0 == *l_tail)
        {
          break;
        }

      if (kv3_text_set_close == *l_tail)
        {
          *l_tail = 0;
          parse_set(io_set, l_head);
          break;
        }

      l_tail++;
    }
  while (1);

  (*io_block) = l_tail;

  return;
}
