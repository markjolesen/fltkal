// timeout.cxx
//
// Timeout class for the Fast Light Tool Kit (FLTK)
// (derived from Fl_X11_Screen_Driver.cxx)
//
// Copyright 2018 The fltkal authors
// Copyright 2018 by Bill Spitzak and others.
//
//                              FLTK License
//                            December 11, 2001
//
// The FLTK library and included programs are provided under the terms
// of the GNU Library General Public License (LGPL) with the following
// exceptions:
//
//     1. Modifications to the FLTK configure script, config
//        header file, and makefiles by themselves to support
//        a specific platform do not constitute a modified or
//        derivative work.
//
//       The authors do request that such modifications be
//       contributed to the FLTK project - send all contributions
//       through the "Software Trouble Report" on the following page:
//
//            http://www.fltk.org/str.php
//
//     2. Widgets that are subclassed from FLTK widgets do not
//        constitute a derivative work.
//
//     3. Static linking of applications and widgets to the
//        FLTK library does not constitute a derivative work
//        and does not require the author to provide source
//        code for the application or widget, use the shared
//        FLTK libraries, or link their applications or
//        widgets against a user-supplied version of FLTK.
//
//        If you link the application or widget to a modified
//        version of FLTK, then the changes to FLTK must be
//        provided under the terms of the LGPL in sections
//        1, 2, and 4.
//
//     4. You do not have to provide a copy of the FLTK license
//        with programs that are linked to the FLTK library, nor
//        do you have to identify the FLTK license in your
//        program or documentation as required by section 6
//        of the LGPL.
//
//        However, programs must still identify their use of FLTK.
//        The following example statement can be included in user
//        documentation to satisfy this requirement:
//
//            [program/widget] is based in part on the work of
//            the FLTK project (http://www.fltk.org).
//
//     This library is free software; you can redistribute it and/or
//     modify it under the terms of the GNU Library General Public
//     License as published by the Free Software Foundation; either
//     version 2 of the License, or (at your option) any later version.
//
//     This library is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//     Library General Public License for more details.
//
//     You should have received a copy of the GNU Library General Public
//     License along with FLTK.  If not, see <http://www.gnu.org/licenses/>.
//
#include "timeout.h"
#include <stdlib.h>

timeout::timeout() :
    first_(0),
    free_(0)
{
    return;
}

timeout::~timeout()
{
    clear();
}

void timeout::clear(struct slot *const head)
{
    struct slot *s;
    struct slot *n;

    s = head;

    do
    {
        if (0 == s)
        {
            break;
        }
        n = s->next;
        free(s);
        s = n;
    }
    while (1);

    return;
}

void timeout::clear()
{

    clear(first_);
    clear(free_);

    return;
}

bool timeout::contains(Fl_Timeout_Handler cb, void *arg)
{
    bool found = false;
    struct slot *s = first_;

    do
    {

        if (0 == s)
        {
            break;
        }

        found = (cb == s->cb && arg == s->arg);

        if (found)
        {
            break;
        }

        s = s->next;

    }
    while (1);

    return found;
}

void timeout::link(double const seconds, Fl_Timeout_Handler cb, void *arg)
{
    struct slot *s = free_;

    if (s)
    {
        free_ = s->next;
    }
    else
    {
        s = reinterpret_cast<struct slot *>(malloc(sizeof(*s)));
    }

    s->timer.set(seconds);
    s->seconds = seconds;
    s->cb = cb;
    s->arg = arg;

    struct slot **p = &first_;
    while (*p && (*p)->seconds <= seconds)
    {
        p = &((*p)->next);
    }

    s->next = *p;
    *p = s;

    return;
}

void timeout::add(double const seconds, Fl_Timeout_Handler cb, void *arg)
{
    link(seconds, cb, arg);
}

void timeout::repeat(double const seconds, Fl_Timeout_Handler cb, void *arg)
{
    link(seconds, cb, arg);
}

void timeout::elapse(ticks_t const &elapsed)
{
    struct slot *s;

    do
    {

        if (0 == first_)
        {
            break;
        }

        for (s = first_; s; s = s->next)
        {
            s->timer.elapse(elapsed);
        }

        do
        {

            if (false == first_->timer.expired())
            {
                break;
            }

            Fl_Timeout_Handler cb = first_->cb;
            void *arg = first_->arg;

            s = first_;
            first_ = s->next;
            s->next = free_;
            free_ = s;

            (*cb)(arg);

            if (0 == first_)
            {
                break;
            }

        }
        while (0);

    }
    while (0);

    return;
}

void timeout::remove(Fl_Timeout_Handler cb, void *arg)
{

    for (struct slot **p = &first_; *p;)
    {
        struct slot *s = *p;
        if (s->cb == cb && (s->arg == arg || !arg))
        {
            *p = s->next;
            s->next = free_;
            free_ = s;
        }
        else
        {
            p = &(s->next);
        }
    }

    return;
}
