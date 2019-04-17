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

public __cursor_arrow
__cursor_arrow label dword
    dd 24, 24
    dd 1, 1
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00404e5h, 0000041h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000feh
    dd 00b0bf5h, 0000041h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c3c3ffh
    dd 00c0cf7h, 000004dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0cbcbffh, 0c8c8ffh, 0eeeeffh, 0bfbfffh
    dd 00b0bf7h, 000004bh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 04c4cf9h, 00606f4h, 00606f9h, 00c0cf8h, 00f0ffbh
    dd 00404fah, 0000041h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0ffffffh
    dd 0d1d1ffh, 03b3bfah, 0fcfcffh, 0ffffffh, 0b7b7ffh
    dd 00e0edfh, 0000033h, 0000048h, 0000067h, 0000085h
    dd 0000052h, 000000dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0fafaffh, 02727f6h
    dd 00404f5h, 0b3b3ffh, 0ffffffh, 0fdfdffh, 01717f6h
    dd 000005bh, 0000030h, 0000031h, 0000031h, 0000032h
    dd 0000032h, 000000bh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 07d7dfbh, 00b0bd1h, 000007fh
    dd 03e3ef5h, 0ffffffh, 0ffffffh, 08585fdh, 00a0ab7h
    dd 000002bh, 0000000h, 0000005h, 000000dh, 0000015h
    dd 0000008h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 00909f3h, 0000049h, 000003ah, 00909f5h
    dd 0dfdfffh, 0ffffffh, 0eaeaffh, 00909f8h, 000003eh
    dd 000000ah, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0020265h, 0000033h, 0000032h, 00707a3h, 07575fah
    dd 0ffffffh, 0ffffffh, 04f4ff6h, 002028bh, 0000021h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 000004eh, 0000001h
    dd 0000033h, 0000031h, 000002ah, 00e0ef6h, 0f9f9ffh
    dd 0fbfbffh, 04444f7h, 006069dh, 0000031h, 0000003h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000033h
    dd 0000014h, 0000000h, 00b0bc5h, 01c1cf4h, 01414f6h
    dd 00b0bc8h, 0000038h, 0000031h, 0000016h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000010h, 0000000h
    dd 0000000h, 000000bh, 0000034h, 000004eh, 0000033h
    dd 0000033h, 0000031h, 000001bh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000027h, 0000030h, 0000031h
    dd 0000025h, 0000001h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
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
