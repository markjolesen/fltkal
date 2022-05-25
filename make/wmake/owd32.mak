# CC0 1.0 Universal --- Public Domain
#
# To the extent possible under law, Mark J. Olesen has waived all copyright
# and related or neighboring rights to this file (owd32.mak). 
# This work is published from: United States.
#
# Full text of this license can be found in '${KV3_HOME}/licenses/CC-CC0'
# or visit 'https://creativecommons.org/publicdomain/zero/1.0/legalcode.txt' or
# send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
#

EXENAME = kv3
SFX = d32
CXXFLAGS = -mf -3r -bt=DOS $(CFLAGS) $(CXXFLAGS)
CXX = wpp386
LINK = wlink

!include owdir.mif

!include owbldexe.mif
