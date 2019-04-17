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

public __cursor_e
__cursor_e label dword
    dd 24, 24
    dd 20, 11
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
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0040466h, 00a0af1h, 00808f6h, 00c0ceah, 003035bh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000001h, 00707f5h
    dd 0d5d5ffh, 0eeeeffh, 0ccccffh, 00909f1h, 0000002h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 000002ah, 0000000h
    dd 0000000h, 0000000h, 0000004h, 00202fdh, 0ffffffh
    dd 0ffffffh, 0f9f9ffh, 00303fch, 0000031h, 0000019h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00202fbh, 0050585h, 0000000h
    dd 0000000h, 0000004h, 00202fdh, 0ffffffh, 0ffffffh
    dd 0f9f9ffh, 00303fdh, 0000033h, 0000031h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00202fdh, 02121f5h, 006068eh, 0000000h
    dd 0000004h, 00202fdh, 0ffffffh, 0ffffffh, 0f9f9ffh
    dd 00303fdh, 0000033h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00202fdh, 0eaeaffh, 02828f6h, 006069ch, 0000005h
    dd 00303fdh, 0ffffffh, 0ffffffh, 0f9f9ffh, 00303fdh
    dd 0000033h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00202fdh
    dd 0fbfbffh, 0ececffh, 02828f7h, 00808a2h, 00303fdh
    dd 0ffffffh, 0ffffffh, 0f9f9ffh, 00303fdh, 0000033h
    dd 0000032h, 0000000h, 0000000h, 0000006h, 00404f3h
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00808fch, 0fdfdffh
    dd 0ffffffh, 0eeeeffh, 02929f6h, 00303fdh, 0ffffffh
    dd 0ffffffh, 0f9f9ffh, 00303fdh, 0000033h, 0000032h
    dd 0000000h, 0000000h, 000000bh, 00606fah, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0efefffh, 08080feh, 0ffffffh, 0ffffffh
    dd 0f9f9ffh, 00303fdh, 0000033h, 0000032h, 0000000h
    dd 0000000h, 000000bh, 00606fah, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0f9f9ffh
    dd 00303fdh, 0000033h, 0000032h, 0000000h, 0000000h
    dd 000000bh, 00606fah, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0f7f7ffh
    dd 09d9dffh, 0ffffffh, 0ffffffh, 0f9f9ffh, 00303fdh
    dd 0000033h, 0000032h, 0000000h, 0000000h, 0000007h
    dd 00303f9h, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00e0efbh
    dd 0fdfdffh, 0ffffffh, 0f7f7ffh, 03d3df7h, 00404fdh
    dd 0ffffffh, 0ffffffh, 0f9f9ffh, 00303fdh, 0000033h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000004h, 0000031h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 00202fdh, 0fbfbffh
    dd 0f7f7ffh, 03d3df7h, 00909c4h, 00303fdh, 0ffffffh
    dd 0ffffffh, 0f9f9ffh, 00303fdh, 0000033h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000003h
    dd 0000033h, 0000031h, 0000031h, 0000031h, 0000031h
    dd 0000031h, 0000031h, 00202fdh, 0f4f4ffh, 04141f6h
    dd 00909c2h, 000003ch, 00404fch, 0ffffffh, 0ffffffh
    dd 0f9f9ffh, 00303fdh, 0000033h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000005h
    dd 0000007h, 0000007h, 0000007h, 0000007h, 0000007h
    dd 0000007h, 00202fdh, 03a3af5h, 00909c0h, 0000035h
    dd 0000039h, 00404fch, 0ffffffh, 0ffffffh, 0f9f9ffh
    dd 00303fdh, 0000033h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00101fch, 00909b0h, 0000035h, 0000033h, 0000037h
    dd 00404fch, 0ffffffh, 0ffffffh, 0f9f9ffh, 00303fdh
    dd 0000033h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000051h
    dd 0000004h, 0000033h, 0000031h, 0000029h, 00404fbh
    dd 0ffffffh, 0ffffffh, 0f9f9ffh, 00303fdh, 0000033h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000001h
    dd 0000033h, 0000022h, 0000002h, 00707f6h, 0e1e1ffh
    dd 0ffffffh, 0e2e2ffh, 00707f7h, 0000033h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000010h
    dd 0000000h, 0000000h, 005056dh, 00808f5h, 00000ffh
    dd 00404fch, 0060690h, 0000033h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 0000032h, 0000033h
    dd 0000033h, 0000033h, 0000031h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 000001bh, 0000031h, 0000030h
    dd 0000031h, 000001bh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000003h, 0000007h, 0000004h
    dd 0000000h

end
