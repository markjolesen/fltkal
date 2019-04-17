; Hackneyed cursors

; Copyright (C) Richard Ferreira

; Permission is hereby granted, free of charge, to any person obtaining
; a copy of this software and associated documentation files (the
; "Software"), to deal in the Software without restriction, including
; without limitation the rights to use, copy, modify, merge, publish,
; distribute, sublicense, and/or sell copies of the Software, and to
; permit persons to whom the Software is furnished to do so, subject to
; the following conditions:
; 
; The above copyright notice and this permission notice shall be
; included in all copies or substantial portions of the Software.
; 
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
; EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
; NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR THE COPYRIGHT HOLDERS
; BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
; OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
; THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
; 
; Except as contained in this notice, the name(s) of the above copyright
; holders shall not be used in advertising or otherwise to promote the sale,
; use or other dealings in this Software without prior written authorization.
;


.model flat

.data

public __cursor_s
__cursor_s label dword
    dd 24, 24
    dd 11, 19
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00505ebh, 00000ffh, 00000ffh
    dd 00000ffh, 00404f4h, 0000003h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh
    dd 00303fch, 0000006h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh, 00303fdh
    dd 0000038h, 0000032h, 0000005h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00404fbh
    dd 0f7f7ffh, 0ffffffh, 0ffffffh, 00303fdh, 0000038h
    dd 0000030h, 0000007h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00404fbh, 0f7f7ffh
    dd 0ffffffh, 0ffffffh, 00303fdh, 0000038h, 0000030h
    dd 0000007h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh
    dd 0ffffffh, 00303fdh, 0000038h, 0000030h, 0000007h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh
    dd 00303fdh, 0000038h, 0000030h, 0000007h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh, 00303fdh
    dd 0000038h, 0000030h, 0000007h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00404fbh
    dd 0f7f7ffh, 0ffffffh, 0ffffffh, 00303fdh, 0000038h
    dd 0000030h, 0000007h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000028h, 00404f0h
    dd 00707f5h, 00707f5h, 00707f5h, 00505fdh, 0fafaffh
    dd 0ffffffh, 0ffffffh, 00b0bfch, 00707f7h, 00707f7h
    dd 00707f5h, 00505f3h, 000004fh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0070794h, 02222f6h
    dd 0dfdfffh, 0eeeeffh, 0f4f4ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0f5f5ffh, 0eeeeffh, 0e9e9ffh, 03d3df7h
    dd 00b0bbdh, 0000006h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0070794h, 02c2cf6h
    dd 0f1f1ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0fafaffh, 04848f8h, 00a0acch, 0000037h
    dd 0000031h, 0000031h, 0000010h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 00707a5h, 02e2ef6h
    dd 0f2f2ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0fafaffh
    dd 04848f8h, 00a0acdh, 0000039h, 0000033h, 0000031h
    dd 0000025h, 0000001h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 00707a7h, 02f2ff6h
    dd 0f3f3ffh, 0ffffffh, 0fafaffh, 04848f8h, 00a0acdh
    dd 0000039h, 0000033h, 0000031h, 0000025h, 0000001h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 003035bh, 00c0cech, 00808f6h, 00808f6h
    dd 00808f6h, 00808f6h, 00707f6h, 00000ffh, 07c7cfeh
    dd 0ffffffh, 09797ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00909f0h, 0030361h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00909f0h, 0c9c9ffh, 0eeeeffh, 0eeeeffh, 0eeeeffh
    dd 0eeeeffh, 0eeeeffh, 0eeeeffh, 0fdfdffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0d6d6ffh, 00a0af2h, 0000002h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00505fah
    dd 0f5f5ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00303fdh, 0000036h, 0000018h
    dd 0000000h, 0000000h, 0000000h, 00a0aeeh, 0dbdbffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ededffh, 00404fbh, 0000035h, 0000031h, 0000002h
    dd 0000000h, 0000000h, 0050568h, 00505f9h, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00303fdh
    dd 007079ch, 0000033h, 0000031h, 0000005h, 0000000h
    dd 0000000h, 0000000h, 0000003h, 0000031h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000032h, 0000003h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 000001bh, 0000032h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000032h
    dd 000001eh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
