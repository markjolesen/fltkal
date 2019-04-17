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

public __cursor_help
__cursor_help label dword
    dd 24, 24
    dd 1, 1
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00404e5h, 0000041h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000002h, 0000052h, 00000b4h, 00000eah, 00000f7h
    dd 00000e3h, 00000b2h, 0000057h, 0000004h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000feh
    dd 00b0bf5h, 0000041h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000021h, 00000c4h
    dd 03a00ffh, 0a800ffh, 0e800ffh, 0ff00ffh, 0e100ffh
    dd 0a600ffh, 03d00ffh, 00000cah, 0000022h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000011h, 00000e2h, 08d00ffh, 0fe00ffh
    dd 0ff00ffh, 0ff00ffh, 0ff00ffh, 0ff00ffh, 0ff00ffh
    dd 0fe00ffh, 09300ffh, 00100ddh, 0000013h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000081h, 06200ffh, 0ff00ffh, 0ff00ffh, 0ff00ffh
    dd 0ff00ffh, 0ff00ffh, 0ff00ffh, 0ff00ffh, 0ff00ffh
    dd 0ff00ffh, 06d00ffh, 0000094h, 0000007h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 00000ddh
    dd 0d500ffh, 0ff00ffh, 0ff00ffh, 0ac00ffh, 02d00ffh
    dd 01900ffh, 07900ffh, 0ff00ffh, 0ff00ffh, 0ff00ffh
    dd 0d700ffh, 00000dbh, 000002ch, 0000004h, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 00000f1h, 0e800ffh
    dd 0ff00ffh, 0cf00ffh, 00400eeh, 0000063h, 0000049h
    dd 00100fbh, 0f800ffh, 0ff00ffh, 0ff00ffh, 0f300ffh
    dd 00000efh, 0000033h, 000001ah, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000088h, 01d00ffh, 04c00ffh
    dd 01100fdh, 0000078h, 0000033h, 000005ch, 02100ffh
    dd 0ff00ffh, 0ff00ffh, 0ff00ffh, 0cf00ffh, 00000d8h
    dd 0000033h, 000002ah, 0000000h, 00000ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000034h, 000006fh, 000004bh
    dd 0000033h, 0000033h, 00000c6h, 09700ffh, 0ff00ffh
    dd 0ff00ffh, 0ff00ffh, 08100ffh, 00000a8h, 0000033h
    dd 000002fh, 0000000h, 00000ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 000001bh, 0000033h, 0000033h
    dd 0000086h, 02f00ffh, 0fb00ffh, 0ff00ffh, 0ff00ffh
    dd 0d700ffh, 00c00f8h, 000004fh, 0000033h, 0000029h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 000000ah, 0000048h, 01300fah
    dd 0db00ffh, 0ff00ffh, 0ff00ffh, 0e400ffh, 02000feh
    dd 000007fh, 0000033h, 0000033h, 000001dh, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0cbcbffh, 0c8c8ffh, 0eeeeffh, 0bfbfffh
    dd 00b0bf7h, 000004bh, 00000cdh, 0b800ffh, 0ff00ffh
    dd 0ff00ffh, 0f400ffh, 02f00ffh, 0000091h, 0000033h
    dd 0000033h, 0000031h, 0000007h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 04c4cf9h, 00606f4h, 00606f9h, 00c0cf8h, 00f0ffbh
    dd 00404fah, 00100f7h, 0f900ffh, 0ff00ffh, 0ff00ffh
    dd 06800ffh, 00000afh, 0000033h, 0000033h, 0000033h
    dd 0000013h, 0000000h, 0000000h, 00000ffh, 0ffffffh
    dd 0d1d1ffh, 03b3bfah, 0fcfcffh, 0ffffffh, 0b7b7ffh
    dd 00e0edfh, 0000033h, 0000048h, 0000067h, 0000085h
    dd 00000cdh, 07800ffh, 0f700ffh, 0ed00ffh, 00f00feh
    dd 0000043h, 0000033h, 0000033h, 0000017h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0fafaffh, 02727f6h
    dd 00404f5h, 0b3b3ffh, 0ffffffh, 0fdfdffh, 01717f6h
    dd 000005bh, 0000030h, 0000031h, 0000031h, 000007dh
    dd 00000fch, 00000ffh, 00000ffh, 00000a6h, 0000033h
    dd 0000033h, 000001fh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 07d7dfbh, 00b0bd1h, 000007fh
    dd 03e3ef5h, 0ffffffh, 0ffffffh, 08585fdh, 00a0ab7h
    dd 000002bh, 0000000h, 0000075h, 04f00ffh, 0e500ffh
    dd 0e400ffh, 04b00ffh, 0000098h, 0000033h, 0000033h
    dd 0000004h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 00909f3h, 0000049h, 000003ah, 00909f5h
    dd 0dfdfffh, 0ffffffh, 0eaeaffh, 00909f8h, 000003eh
    dd 000000ah, 00000e7h, 0e600ffh, 0ff00ffh, 0ff00ffh
    dd 0e300ffh, 00000e6h, 0000033h, 000001dh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0020265h, 0000033h, 0000032h, 00707a3h, 07575fah
    dd 0ffffffh, 0ffffffh, 04f4ff6h, 002028bh, 0000021h
    dd 00000e4h, 0e300ffh, 0ff00ffh, 0ff00ffh, 0e000ffh
    dd 00000e8h, 0000033h, 0000019h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 000004eh, 0000001h
    dd 0000033h, 0000031h, 000002ah, 00e0ef6h, 0f9f9ffh
    dd 0fbfbffh, 04444f7h, 006069dh, 0000031h, 0000085h
    dd 04c00ffh, 0e400ffh, 0e300ffh, 04800ffh, 000009ch
    dd 0000033h, 000002dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000033h
    dd 0000014h, 0000000h, 00b0bc5h, 01c1cf4h, 01414f6h
    dd 00b0bc8h, 0000038h, 0000031h, 000001bh, 0000086h
    dd 00000e9h, 00000e9h, 000009dh, 0000037h, 0000033h
    dd 000002dh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000010h, 0000000h
    dd 0000000h, 000000bh, 0000034h, 000004eh, 0000033h
    dd 0000033h, 0000031h, 000001bh, 0000000h, 000001ah
    dd 0000033h, 0000033h, 0000033h, 0000033h, 000001ah
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000027h, 0000030h, 0000031h
    dd 0000025h, 0000001h, 0000000h, 0000001h, 000001bh
    dd 000002eh, 000002eh, 000001bh, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000002h, 0000009h, 0000007h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
