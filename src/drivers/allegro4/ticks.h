// ticks.h
//
// Time wrapper for the Fast Light Tool Kit (FLTK)
//
// Copyright 2018 The fltkal authors
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
#if !defined(__TICKS_H__)

#include <time.h>
#include <math.h>

/**
Abstract time type
*/
#if defined(__DJGPP__)
typedef uclock_t ticks_t;
#elif defined(__WATCOMC__)
typedef clock_t ticks_t;
#else
typedef struct timespec ticks_t;
#endif

/**
Set a time type to the current time
\param[in,out] ticks time object to intialize
\returns none
*/
inline void
ticks_set(ticks_t& ticks)
{
#if defined(__DJGPP__)
  ticks = uclock();
#elif defined(__WATCOMC__)
  ticks = clock();
#else
  clock_gettime(CLOCK_REALTIME, &ticks);
#endif
  return;
}

/**
Set a time type in seconds
\param[in] seconds time in seconds
\param[out] ticks time object to initialize
\returns none
*/
inline void
ticks_convert(ticks_t& ticks, double const seconds)
{

#if defined(__DJGPP__)

  ticks = static_cast<ticks_t>((UCLOCKS_PER_SEC * seconds));

#elif defined(__WATCOMC__)

  ticks = static_cast<ticks_t>((CLOCKS_PER_SEC * seconds));

#else

  if (0 < seconds)
  {
    double integral;
    double fract = modf(seconds, &integral);

    ticks.tv_sec = integral;
    ticks.tv_nsec = (fract * 1000000000L);
  }

  else
  {
    ticks.tv_sec = 0;
    ticks.tv_nsec = 0;
  }

#endif

  return;
}

/**
Subtract time
\param[out] result time object to place result in
\param[in] begin begining time object
\param[in] end ending time object
\returns none
*/
inline void
ticks_subtract(ticks_t& result, ticks_t const& begin, ticks_t const& end)
{

#if defined(__DJGPP__) || defined(__WATCOMC__)

  result = (end - begin);

#else

  long sec_diff = (end.tv_sec - begin.tv_sec);
  long nsec_diff = (end.tv_nsec - begin.tv_nsec);

  if (0 < nsec_diff)
  {
    result.tv_sec = sec_diff;
    result.tv_nsec = nsec_diff;
  }

  else
  {
    result.tv_sec = sec_diff - 1;
    result.tv_nsec = nsec_diff + 1000000000L;
  }

#endif

  return;
}

/**
Elapse a time object
\param[in,out] ticks time object to elapse
\param[in] elapsed elapsed time to subtract from ticks
\returns none
*/
inline void
ticks_elapse(ticks_t& ticks, ticks_t const& elapsed)
{

#if defined(__DJGPP__) || defined(__WATCOMC__)

  ticks -= elapsed;

#else

  long sec_diff = (ticks.tv_sec - elapsed.tv_sec);
  long nsec_diff = (ticks.tv_nsec - elapsed.tv_nsec);

  if (0 > nsec_diff)
  {
    sec_diff--;
    nsec_diff += 1000000000L;
  }

  ticks.tv_sec = sec_diff;
  ticks.tv_nsec = nsec_diff;

#endif

  return;
}

#define __TICKS_H__
#endif
