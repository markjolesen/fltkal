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

public __cursor_ns
__cursor_ns label dword
    dd 24, 24
    dd 12, 12
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000040h, 0000040h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000048h
    dd 00b0bf4h, 00c0cf5h, 0000048h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000047h, 00c0cf4h, 0c7c7ffh
    dd 0ccccffh, 00d0df5h, 0000056h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000047h, 00c0cf4h, 0c7c7ffh, 0ffffffh, 0ffffffh
    dd 0ccccffh, 00d0df7h, 0000057h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000047h, 00c0cf4h
    dd 0c7c7ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ccccffh, 00d0df7h, 0000058h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000047h, 00c0cf4h, 0c7c7ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ccccffh, 00d0df7h, 0000058h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000047h
    dd 00c0cf4h, 0c7c7ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ccccffh, 00d0df7h, 0000058h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000002h, 00303efh, 00000ffh
    dd 00000ffh, 00000ffh, 00b0bfch, 0fdfdffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00f0ffch, 00000ffh, 00000ffh
    dd 00000ffh, 00303f2h, 0000012h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 000000fh
    dd 0000031h, 00101feh, 0fcfcffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00202feh, 0000035h, 0000033h, 0000033h
    dd 0000033h, 0000031h, 0000010h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 0000031h, 0000033h
    dd 00101feh, 0fcfcffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00202feh, 0000035h, 0000032h, 0000033h, 0000033h
    dd 0000033h, 0000031h, 0000001h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00101fdh
    dd 0fcfcffh, 0ffffffh, 0ffffffh, 0ffffffh, 00202feh
    dd 0000035h, 0000033h, 0000001h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00101fdh, 0fcfcffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00202feh, 0000035h
    dd 0000033h, 0000001h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00101fdh, 0fcfcffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00202feh, 0000035h, 0000033h
    dd 0000001h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00101fdh, 0fcfcffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00202feh, 0000035h, 0000033h, 0000001h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000007h, 00202f4h, 00000ffh, 00000ffh, 00000ffh
    dd 00a0afbh, 0fdfdffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00e0efbh, 00000ffh, 00000ffh, 00000ffh, 00202f3h
    dd 0000006h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 001014ch, 00d0df5h, 0cacaffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0cfcfffh, 00e0ef5h, 0010151h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 001014ch, 00d0df7h, 0cacaffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0cfcfffh
    dd 00e0ef7h, 0010174h, 0000033h, 0000033h, 0000031h
    dd 0000001h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0010156h, 00d0df7h, 0cacaffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0cfcfffh, 00e0ef7h, 0010174h
    dd 0000033h, 0000033h, 0000031h, 0000010h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0010156h, 00d0df7h, 0cacaffh, 0ffffffh, 0ffffffh
    dd 0cfcfffh, 00e0ef7h, 0010174h, 0000033h, 0000033h
    dd 0000031h, 0000010h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0010156h, 00d0df7h, 0cacaffh, 0cfcfffh, 00e0ef7h
    dd 0010174h, 0000033h, 0000033h, 0000031h, 0000010h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 001015ch, 00d0df7h, 00e0ef8h, 0010174h, 0000033h
    dd 0000033h, 0000031h, 0000010h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0010152h, 001016ah, 0000033h, 0000033h, 0000031h
    dd 000000fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000000eh, 0000031h, 0000031h, 000000eh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000000ch, 000000ch, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
