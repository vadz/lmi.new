/* This is public domain. It's not 'Copyright 2005', but including that
 * quoted string keeps my style-conformity script from complaining.
 * Eventually this will become part of MinGW and cygwin, and will then
 * be removed from the lmi cvs. Find the original at:

http://cygwin.com/cgi-bin/cvsweb.cgi/src/winsup/mingw/mingwex/math/expm1.c?cvsroot=src

 */

/*
 * Written 2005 by Gregory W. Chicares <chicares@cox.net>.
 * Adapted to double by Danny Smith <dannysmith@users.sourceforge.net>.
 * Public domain.
 *
 * F2XM1's input is constrained to (-1, +1), so the domain of
 * 'x * LOG2EL' is (-LOGE2L, +LOGE2L). Outside that domain,
 * delegating to exp() handles C99 7.12.6.3/2 range errors.
 *
 * Constants from moshier.net, file cephes/ldouble/constl.c,
 * are used instead of M_LN2 and M_LOG2E, which would not be
 * visible with 'gcc std=c99'.  The use of these extended precision
 * constants also allows gcc to replace them with x87 opcodes.
 */

#include <math.h> /* expl() */
/* Begin local GWC modifications:
 * #include "cephes_mconf.h"
 */
double expm1(double x);
#define LOGE2L  6.9314718055994530941723E-1L
#define LOG2EL  1.4426950408889634073599E0L

/*
 * http://savannah.nongnu.org/projects/lmi
 * email: <chicares@cox.net>
 * snail: Chicares, 186 Belle Woods Drive, Glastonbury CT 06033, USA
 *
 * $Id: expm1.c,v 1.1 2005-04-05 12:36:37 chicares Exp $
 *
 * End local GWC modifications. */

double expm1 (double x)
{
  if (fabs(x) < LOGE2L)
    {
      x *= LOG2EL;
      __asm__("f2xm1" : "=t" (x) : "0" (x));
      return x;
    }
  else
    return exp(x) - 1.0;
}

