# CC0 1.0 Universal --- Public Domain
#
# To the extent possible under law, Mark J. Olesen has waived all copyright
# and related or neighboring rights to this file (owd32.mak). 
# This work is published from: United States.
#
# This file is part of the mjo libraray.
#
# Full text of this license can be found in '${MJO_HOME}/licenses/CC-CC0'
# or visit 'https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt' or
# send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
#

LIBNAME=kv3
SFX=d32
CFLAGS= -mf -3r -bt=DOS $(CFLAGS)
CC=wcc386

!include owdir.mif

!include owbldlib.mif
