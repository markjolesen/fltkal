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

public __cursor_nesw
__cursor_nesw label dword
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
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000006h
    dd 00303f2h, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00404f5h
    dd 0000004h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 001014bh
    dd 01010f3h, 0d1d1ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00606fah, 0000007h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0010151h
    dd 00f0ff5h, 0d2d2ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00606fah, 0000015h, 000000eh
    dd 0000001h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000003h, 00707ceh
    dd 06969fbh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00606fbh, 0000036h, 0000031h, 000000eh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000000eh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000003h, 00a0aafh, 04141f4h, 0f8f8ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00606fbh, 0000039h, 0000030h, 000000fh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00303f5h, 002025dh, 0000000h, 0000000h, 0000003h
    dd 00a0ab0h, 04141f4h, 0f8f8ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 00606fbh
    dd 0000039h, 0000030h, 000000fh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00101fdh
    dd 01313f5h, 002025dh, 0000003h, 00a0ab0h, 04141f4h
    dd 0f8f8ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0fbfbffh
    dd 07070fbh, 0d1d1ffh, 0ffffffh, 00606fbh, 0000039h
    dd 0000030h, 000000fh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00202fdh, 0d9d9ffh
    dd 01313f6h, 00707cch, 04141f4h, 0f8f8ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0fbfbffh, 04a4af7h, 00808d6h
    dd 00f0ff6h, 0d1d1ffh, 00606fbh, 0000039h, 0000030h
    dd 000000fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00202fdh, 0ffffffh, 0d9d9ffh
    dd 06f6ffch, 0f9f9ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0fbfbffh, 04a4af7h, 00a0ac6h, 0000037h, 0010173h
    dd 00f0ff6h, 00303fdh, 0000039h, 0000030h, 000000fh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00202fdh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0fbfbffh, 04a4af7h
    dd 00a0ac6h, 0000037h, 0000033h, 0000033h, 0010172h
    dd 00202f8h, 0000037h, 0000030h, 0000010h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00202fdh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0fbfbffh, 04a4af7h, 00b0bc7h, 0000037h
    dd 0000033h, 0000033h, 0000031h, 0000024h, 0000030h
    dd 0000031h, 0000030h, 0000010h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00202fdh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 07575fch, 00808d9h, 0000037h, 0000033h, 0000033h
    dd 0000031h, 0000024h, 0000001h, 0000001h, 0000027h
    dd 0000033h, 0000010h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00202fdh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0dadaffh
    dd 01414f7h, 003037fh, 0000033h, 0000031h, 0000024h
    dd 0000001h, 0000000h, 0000000h, 0000001h, 0000023h
    dd 000000bh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00202fdh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0dadaffh
    dd 01414f7h, 003037eh, 0000024h, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00404f4h, 00909f7h, 00909f8h, 00909f9h
    dd 00909f9h, 00909f9h, 00909f9h, 00909f9h, 00404fch
    dd 00101fbh, 000001ah, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000027h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000032h
    dd 000002ch, 0000004h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000026h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000032h
    dd 000002ch, 0000004h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000016h, 0000026h, 0000028h, 0000028h, 0000028h
    dd 0000028h, 0000028h, 0000029h, 0000029h, 0000028h
    dd 000000dh, 0000000h, 0000000h, 0000000h, 0000000h
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
    dd 0000000h

end
