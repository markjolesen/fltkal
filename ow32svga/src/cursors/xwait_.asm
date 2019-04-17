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

public __cursor_wait
__cursor_wait label dword
    dd 24, 24
    dd 12, 12
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
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000088h
    dd 00101fah, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00101fah, 0000086h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000f3h, 00000ffh
    dd 0f3f3ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0f3f3ffh, 00000ffh, 00000f2h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000086h, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 000009dh, 0000032h, 000001bh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00000ffh, 0000033h, 0000033h, 0000031h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 05858ffh, 00d0dffh
    dd 06565ffh, 0cfcfffh, 0aaaaffh, 0ffffffh, 00000ffh
    dd 0000033h, 0000033h, 0000019h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00101feh, 0fdfdffh, 01616ffh, 00000ffh, 00000ffh
    dd 00000ffh, 01010ffh, 0fcfcffh, 00101feh, 0000033h
    dd 0000033h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00b0be6h
    dd 0d0d0ffh, 07f7fffh, 00000ffh, 00000ffh, 00000ffh
    dd 06666ffh, 0cecefeh, 00909e9h, 0000033h, 0000033h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0020270h, 03434f3h
    dd 0fbfbffh, 08181ffh, 02222ffh, 08484ffh, 0f8f8ffh
    dd 02525eah, 000008ah, 0000033h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000002h, 00a0abch, 04040f6h
    dd 0e6e6ffh, 0ffffffh, 0e5e5ffh, 03939f2h, 00303c3h
    dd 0000035h, 0000033h, 000002bh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000004h, 0030392h, 00a0afah
    dd 0fdfdffh, 00a0afah, 00505a0h, 0000036h, 0000033h
    dd 0000033h, 0000016h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000000fh, 01414b5h, 01111f9h, 0fdfdffh
    dd 00f0ff8h, 00b0bbch, 000003eh, 0000033h, 0000023h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 000000ah
    dd 01313e7h, 06e6effh, 0f2f2ffh, 0ffffffh, 0f2f2ffh
    dd 06565f9h, 00909e3h, 0000021h, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 012129eh, 06161fdh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 05757f7h, 007079eh, 0000003h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00f0ff3h, 0dfdfffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ddddffh
    dd 00e0ef4h, 000002bh, 0000003h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00101feh, 0fdfdffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0fdfdffh, 00101feh
    dd 0000033h, 000001dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 0ffffffh, 0eeeeffh, 0a1a1ffh, 06262ffh
    dd 0acacffh, 0ededffh, 0ffffffh, 00000ffh, 0000033h
    dd 000002dh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00000ffh, 0000033h, 0000033h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000088h, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 000009eh, 0000033h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000f3h, 00000ffh, 0f3f3ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0f3f3ffh
    dd 00000ffh, 00000f5h, 0000033h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000086h, 00202fbh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00101fbh
    dd 000009dh, 0000033h, 0000019h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000030h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000031h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000001bh, 0000032h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000032h
    dd 000001ah, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
