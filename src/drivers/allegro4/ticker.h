// ticker.h
//
// Ticker class for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018-2019 The fltkal authors
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
#if !defined(__TICKER_H__)

#  include "ticks.h"

class ticker
{
public:
  ticker();

  virtual ~ticker();

  bool
    expired() const;

  void
    set(double const seconds);

  void
    reset();

  void
    elapse(ticks_t const &elapsed);

protected:
  bool expired_;
  ticks_t expiry_;
  ticks_t ticker_;

private:
  ticker(ticker const &);

  ticker &
    operator=(ticker const &);
};

inline ticker::ticker() : expired_(true), expiry_(), ticker_()
{
  return;
}

inline ticker::~ticker()
{
  return;
}

inline void
  ticker::set(double const seconds)
{
  if (seconds > 0)
    {
      expired_ = false;
      ticks_convert(expiry_, seconds);
    }

  else
    {
      expired_ = true;
      ticks_convert(expiry_, 0);
    }

  ticker_ = expiry_;
}

inline void
  ticker::reset()
{
  ticker_ = expiry_;
  expired_ = false;
}

inline bool
  ticker::expired() const
{
  return expired_;
}

inline void
  ticker::elapse(ticks_t const &elapsed)
{
  do
    {
      if (expired_)
        {
          break;
        }

      ticks_elapse(ticker_, elapsed);

#  if defined(__DJGPP__) || defined(__WATCOMC__)

      if (0 > ticker_)
#  else
      if (0 > ticker_.tv_sec || 0 > ticker_.tv_nsec)
#  endif
        {
          expired_ = true;
        }
    }
  while (0);

  return;
}

#  define __TICKER_H__
#endif
