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

public __cursor_sw
__cursor_sw label dword
    dd 24, 24
    dd 3, 20
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
    dd 0000011h, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00c0c98h
    dd 00202feh, 00000ffh, 00202fdh, 00c0c9ah, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000030h, 00707f3h
    dd 00909a8h, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00202fch, 0f9f9ffh
    dd 0ffffffh, 0f9f9ffh, 00202fch, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000031h, 00a0af1h, 0a2a2feh, 03636f5h
    dd 00909aah, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00000ffh, 0000033h, 000001ch, 00404e6h
    dd 000003bh, 0000000h, 0000000h, 0000000h, 0000031h
    dd 00a0af1h, 0adadfeh, 0ffffffh, 0f5f5ffh, 03535f6h
    dd 00909b0h, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00000ffh, 0000034h, 0000034h, 00101ffh, 00a0af4h
    dd 000003bh, 0000000h, 0000031h, 00a0af1h, 0aeaefeh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0b9b9ffh, 00404fbh
    dd 0000030h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 00000ffh
    dd 0000034h, 0000035h, 00303fdh, 0babaffh, 00a0af6h
    dd 000006bh, 00a0af1h, 0aeaefeh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0c3c3ffh, 00c0cf7h, 0000069h, 0000031h
    dd 0000017h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00000ffh, 0000034h
    dd 0000035h, 00303fdh, 0ffffffh, 0babaffh, 00c0cfbh
    dd 0aeaefeh, 0ffffffh, 0ffffffh, 0ffffffh, 0c2c2ffh
    dd 00b0bf7h, 0000069h, 0000033h, 0000032h, 000002dh
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00000ffh, 0000034h, 0000035h
    dd 00303fdh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0c4c4ffh, 00c0cf7h, 0000069h
    dd 0000033h, 0000033h, 000002fh, 0000006h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00000ffh, 0000034h, 0000035h, 00303fdh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0c4c4ffh, 00c0cf7h, 0000069h, 0000033h, 0000033h
    dd 000002fh, 0000007h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00000ffh, 0000034h, 0000035h, 00303fdh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 01313fah
    dd 000008fh, 0000033h, 0000033h, 0000030h, 0000008h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 00000ffh
    dd 0000034h, 0000035h, 00303fdh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0babaffh, 00a0af6h
    dd 0000062h, 0000030h, 0000009h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00000ffh, 0000034h
    dd 0000035h, 00303fdh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0babaffh, 00a0af7h
    dd 000004bh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00000ffh, 0000034h, 0000033h
    dd 00303f4h, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00404e3h
    dd 0000006h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00000ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00000ffh, 0000034h, 0000031h, 0000000h
    dd 0000009h, 0000030h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000032h, 000002fh
    dd 0000006h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00000ffh, 0000034h, 0000031h, 0000000h, 0000007h
    dd 0000032h, 0000031h, 0000031h, 0000031h, 0000031h
    dd 0000031h, 0000031h, 0000031h, 0000033h, 0000024h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00000ffh, 0ffffffh, 0ffffffh, 0ffffffh, 00d0dfch
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00202fdh, 00b0b99h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00000ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0f6f6ffh, 00303fch, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00000ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00000ffh, 000002dh, 0000017h, 0000000h
    dd 0000000h, 0000000h, 00808f3h, 0dcdcffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0f6f6ffh
    dd 00303fch, 0000034h, 0000032h, 0000001h, 0000000h
    dd 0000000h, 0040466h, 00808f4h, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00303fch, 00b0ba5h
    dd 0000033h, 0000032h, 0000002h, 0000000h, 0000000h
    dd 0000000h, 0000007h, 0000031h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000032h, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000027h, 0000031h, 0000030h, 0000030h
    dd 0000030h, 0000030h, 0000030h, 0000030h, 0000030h
    dd 0000030h, 0000030h, 0000030h, 0000030h, 0000030h
    dd 0000030h, 0000030h, 0000030h, 0000030h, 0000029h
    dd 0000000h

end
