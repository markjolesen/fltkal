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

public __cursor_n
__cursor_n label dword
    dd 24, 24
    dd 11, 3
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
    dd 0040466h, 00606f7h, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00404fbh, 0070781h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00b0beeh
    dd 0d9d9ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ececffh, 00404fah, 0000003h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00505fah, 0f5f5ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00303fdh, 0000037h, 000001eh, 0000000h
    dd 0000000h, 0000000h, 00909f0h, 0cdcdffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0d8d8ffh
    dd 00a0af4h, 0000035h, 0000032h, 0000003h, 0000000h
    dd 0000000h, 003035bh, 00a0aefh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 07d7dfeh
    dd 0ffffffh, 09898ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00909f4h, 0030382h
    dd 0000033h, 0000031h, 0000005h, 0000000h, 0000000h
    dd 0000000h, 0000003h, 0000032h, 0000033h, 0000033h
    dd 0000034h, 00707afh, 02e2ef6h, 0f2f2ffh, 0ffffffh
    dd 0fafaffh, 04747f7h, 00a0acch, 0000039h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000031h, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000001ah, 0000031h, 0000034h, 00707adh
    dd 02d2df6h, 0f1f1ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0fafaffh, 04747f7h, 00a0acch, 0000039h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000032h, 0000019h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 007078fh, 02727f4h, 0eeeeffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0fafaffh, 04747f7h, 00a0ac8h, 0000008h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0060691h, 02121f6h, 0dedeffh, 0eeeeffh, 0f5f5ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0f6f6ffh, 0eeeeffh
    dd 0e8e8ffh, 03a3af9h, 00b0bc4h, 0000007h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000029h, 00505f1h
    dd 00808f6h, 00808f6h, 00808f7h, 00606fdh, 0fafaffh
    dd 0ffffffh, 0ffffffh, 00c0cfch, 00808f8h, 00808f8h
    dd 00808f8h, 00606f6h, 0000069h, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000001bh, 0000031h, 00404fch, 0f7f7ffh, 0ffffffh
    dd 0ffffffh, 00303fdh, 0000038h, 0000033h, 0000033h
    dd 0000033h, 0000031h, 0000024h, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000008h, 0000032h
    dd 0000033h, 00404fch, 0f7f7ffh, 0ffffffh, 0ffffffh
    dd 00303fdh, 0000038h, 0000031h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000010h, 0000000h, 0000000h
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
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00606edh
    dd 00000ffh, 00000ffh, 00000ffh, 00404f8h, 0000036h
    dd 0000030h, 0000007h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000003h
    dd 0000032h, 0000033h, 0000033h, 0000033h, 0000030h
    dd 0000007h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000002h, 0000032h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000005h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
