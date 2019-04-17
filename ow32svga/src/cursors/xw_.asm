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

public __cursor_w
__cursor_w label dword
    dd 24, 24
    dd 3, 11
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
    dd 0050569h, 00808f3h, 00000ffh, 00606f7h, 0040467h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00707f5h
    dd 0dedeffh, 0ffffffh, 0dadaffh, 00909f3h, 0000002h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000feh, 0fefeffh
    dd 0ffffffh, 0fdfdffh, 00101feh, 0000032h, 0000018h
    dd 0000000h, 0000000h, 000002eh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000feh, 0fefeffh, 0ffffffh
    dd 0fdfdffh, 00101feh, 0000033h, 0000031h, 0000000h
    dd 0070794h, 00303f6h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000feh, 0fefeffh, 0ffffffh, 0fdfdffh
    dd 00101feh, 0000033h, 0000033h, 0070797h, 02525f5h
    dd 00505fah, 0000000h, 0000008h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000feh, 0fefeffh, 0ffffffh, 0fdfdffh, 00101feh
    dd 0000034h, 00707ach, 02828f4h, 0e4e4ffh, 00505fah
    dd 000001dh, 0000031h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000feh
    dd 0fefeffh, 0ffffffh, 0fefeffh, 00000ffh, 00707b2h
    dd 02e2ef5h, 0f1f1ffh, 0f5f5ffh, 00505fah, 0000031h
    dd 0000031h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000feh, 0fefeffh
    dd 0ffffffh, 0fefeffh, 00000ffh, 03232f6h, 0f2f2ffh
    dd 0ffffffh, 0f9f9ffh, 00808fch, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00303f5h, 0000003h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000feh, 0fefeffh, 0ffffffh
    dd 0ffffffh, 08282feh, 0f4f4ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00303fch, 0000009h, 0000001h, 0000000h, 0000000h
    dd 0000000h, 00000feh, 0fefeffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 00303fdh
    dd 0000036h, 0000031h, 0000000h, 0000000h, 0000000h
    dd 00000feh, 0fefeffh, 0ffffffh, 0ffffffh, 09191ffh
    dd 0f7f7ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00303fdh, 0000038h
    dd 0000033h, 0000000h, 0000000h, 0000000h, 00000feh
    dd 0fefeffh, 0ffffffh, 0ffffffh, 00000ffh, 03c3cf7h
    dd 0f7f7ffh, 0ffffffh, 0f9f9ffh, 00808fch, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00303f7h, 0000035h, 0000033h
    dd 0000000h, 0000000h, 0000000h, 00000feh, 0fefeffh
    dd 0ffffffh, 0ffffffh, 00000ffh, 00808beh, 03a3af6h
    dd 0f7f7ffh, 0f5f5ffh, 00505fbh, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000000h
    dd 0000000h, 0000000h, 00000feh, 0fefeffh, 0ffffffh
    dd 0ffffffh, 00000ffh, 0000035h, 00808bch, 03a3af6h
    dd 0ececffh, 00505fbh, 0000033h, 0000031h, 0000031h
    dd 0000031h, 0000031h, 0000031h, 0000031h, 0000031h
    dd 0000031h, 0000031h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 00000feh, 0fefeffh, 0ffffffh, 0ffffffh
    dd 00000ffh, 0000034h, 0000035h, 00808bah, 03535f7h
    dd 00505fbh, 0000033h, 0000032h, 0000007h, 0000007h
    dd 0000007h, 0000007h, 0000007h, 0000007h, 0000007h
    dd 0000007h, 0000005h, 0000000h, 0000000h, 0000000h
    dd 00000feh, 0fefeffh, 0ffffffh, 0ffffffh, 00101ffh
    dd 0000034h, 0000033h, 0000004h, 00909bbh, 00303f9h
    dd 0000033h, 0000031h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000feh
    dd 0fefeffh, 0ffffffh, 0ffffffh, 00101feh, 0000035h
    dd 0000033h, 0000000h, 0000004h, 0000065h, 0000031h
    dd 0000031h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00606f8h, 0e4e4ffh
    dd 0ffffffh, 0d7d7ffh, 00909f5h, 0000033h, 0000033h
    dd 0000000h, 0000000h, 0000001h, 0000025h, 0000031h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0060676h, 00505f9h, 00000ffh
    dd 00909f3h, 0030381h, 0000033h, 0000033h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 0000010h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 0000032h, 0000033h
    dd 0000033h, 0000033h, 0000031h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000020h, 0000031h, 0000030h
    dd 0000031h, 0000018h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000004h, 0000007h, 0000003h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
