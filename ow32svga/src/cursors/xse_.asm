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

public __cursor_se
__cursor_se label dword
    dd 24, 24
    dd 20, 20
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
    dd 0000000h, 0000000h, 0000000h, 0000001h, 0000011h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000002h, 00808a5h, 00606f3h, 0000031h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00c0c97h
    dd 00202fdh, 00000ffh, 00202feh, 00c0c98h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000002h
    dd 00808a4h, 03434f4h, 0a4a4feh, 00a0af2h, 0000035h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00303fch, 0f8f8ffh
    dd 0ffffffh, 0f9f9ffh, 00303fch, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000002h, 00909a5h, 03434f4h
    dd 0f4f4ffh, 0ffffffh, 0afaffeh, 00a0af4h, 000003ah
    dd 0000000h, 0000000h, 0000000h, 0000039h, 00404e0h
    dd 0000004h, 0000000h, 00000feh, 0fefeffh, 0ffffffh
    dd 0ffffffh, 00101feh, 0000034h, 000001ah, 0000000h
    dd 0000000h, 000001bh, 00404f9h, 0b7b7ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0b0b0feh, 00a0af4h, 000003ah
    dd 0000000h, 0000039h, 00a0af4h, 00101feh, 0000007h
    dd 0000000h, 00000feh, 0fefeffh, 0ffffffh, 0ffffffh
    dd 00101feh, 0000035h, 0000031h, 0000000h, 0000000h
    dd 0000000h, 0000042h, 00b0bf4h, 0c1c1ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0b0b0feh, 00a0af4h, 000006ch
    dd 00909f3h, 0b7b7ffh, 00404fch, 0000013h, 000002ah
    dd 00000feh, 0fefeffh, 0ffffffh, 0ffffffh, 00101feh
    dd 0000035h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000046h, 00b0bf6h, 0c1c1ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0b1b1feh, 00a0afbh, 0b7b7ffh
    dd 0ffffffh, 00404fch, 0000037h, 0000032h, 00000feh
    dd 0fefeffh, 0ffffffh, 0ffffffh, 00101feh, 0000035h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000047h, 00c0cf6h, 0bdbdffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00404fch, 0000039h, 0000032h, 00000feh, 0fefeffh
    dd 0ffffffh, 0ffffffh, 00101feh, 0000035h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000047h, 00a0af6h, 0bdbdffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 00404fch
    dd 0000039h, 0000032h, 00000feh, 0fefeffh, 0ffffffh
    dd 0ffffffh, 00101feh, 0000035h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000078h, 01212fah, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00404fch, 0000039h
    dd 0000032h, 00000feh, 0fefeffh, 0ffffffh, 0ffffffh
    dd 00101feh, 0000035h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000039h
    dd 00a0af3h, 0b8b8ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00404fch, 0000039h, 0000032h
    dd 00000feh, 0fefeffh, 0ffffffh, 0ffffffh, 00101feh
    dd 0000035h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000039h, 00909f3h, 0b3b3ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00404fch, 0000039h, 0000032h, 00000feh
    dd 0fefeffh, 0ffffffh, 0ffffffh, 00101feh, 0000035h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00505dch, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00404f8h, 0000036h, 0000032h, 00000feh, 0fefeffh
    dd 0ffffffh, 0ffffffh, 00101feh, 0000035h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 000000ch, 0000031h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000032h, 00000feh, 0fefeffh, 0ffffffh
    dd 0ffffffh, 00101feh, 0000035h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000002fh, 0000033h, 0000031h, 0000031h
    dd 0000031h, 0000031h, 0000031h, 0000031h, 0000032h
    dd 0000030h, 00000feh, 0fefeffh, 0ffffffh, 0ffffffh
    dd 00101feh, 0000035h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 00a0a96h, 00202fdh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00b0bfbh, 0fefeffh, 0ffffffh, 0ffffffh, 00101feh
    dd 0000035h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 00404fbh, 0f4f4ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00101feh, 0000035h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 00101feh
    dd 0fdfdffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00101feh, 0000035h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 00404fbh, 0f4f4ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0dedeffh, 00808f6h, 0000034h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 00b0b8eh, 00303fbh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00707f7h
    dd 0050587h, 0000033h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 000000ch, 0000030h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000031h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000002h, 000002fh, 0000030h, 0000030h
    dd 0000030h, 0000030h, 0000030h, 0000030h, 0000030h
    dd 0000030h, 0000030h, 0000030h, 0000030h, 0000030h
    dd 0000030h, 0000030h, 0000030h, 0000030h, 0000031h
    dd 000001ch

end
