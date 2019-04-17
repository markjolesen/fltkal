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

public __cursor_nw
__cursor_nw label dword
    dd 24, 24
    dd 3, 3
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
    dd 0040462h, 00808f3h, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00303fch, 00b0b96h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00b0beeh
    dd 0d6d6ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0f8f8ffh, 00505fbh, 0000010h, 0000001h
    dd 0000000h, 0000000h, 0000000h, 00404fbh, 0f7f7ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00404fch, 0000036h, 000002eh, 0000001h
    dd 0000000h, 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0f9f9ffh
    dd 00505fbh, 0000037h, 0000030h, 000000ah, 0000000h
    dd 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh
    dd 01313fbh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00202feh, 00b0bb3h
    dd 0000033h, 0000030h, 000000ah, 0000000h, 0000000h
    dd 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh, 00404fch
    dd 0000039h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000031h, 0000007h, 0000000h, 0000000h, 00404fbh
    dd 0f7f7ffh, 0ffffffh, 0ffffffh, 00404fch, 0000039h
    dd 0000031h, 000002dh, 000002ch, 000002ch, 000002ch
    dd 000002eh, 000002eh, 000002eh, 000002eh, 000002eh
    dd 000002eh, 000002eh, 000002eh, 000002eh, 000001fh
    dd 0000000h, 0000000h, 0000000h, 00404fbh, 0f7f7ffh
    dd 0ffffffh, 0ffffffh, 00404fch, 0000039h, 0000031h
    dd 00404f1h, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00303e4h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh
    dd 0ffffffh, 00404fch, 0000039h, 0000031h, 00101feh
    dd 0fdfdffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0c2c2ffh, 00b0bf4h, 0000042h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh
    dd 00404fch, 0000039h, 0000031h, 00101feh, 0fdfdffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0bfbfffh
    dd 00b0bf7h, 0000066h, 0000033h, 0000033h, 000002dh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh, 00404fch
    dd 0000039h, 0000031h, 00101feh, 0fdfdffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 01a1af9h, 0000095h
    dd 0000033h, 0000033h, 0000031h, 000000bh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00404fbh
    dd 0f7f7ffh, 0ffffffh, 0ffffffh, 00404fch, 0000039h
    dd 0000031h, 00101feh, 0fdfdffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ccccffh, 00d0df6h, 0000071h
    dd 0000031h, 000000bh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00404fbh, 0f7f7ffh
    dd 0ffffffh, 0ffffffh, 00404fch, 0000039h, 0000031h
    dd 00101feh, 0fdfdffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ccccffh, 00d0df6h, 000005dh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh
    dd 0ffffffh, 00404fch, 0000039h, 0000031h, 00101feh
    dd 0fdfdffh, 0bfbfffh, 00b0bfbh, 0a9a9feh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0c7c7ffh, 00c0cf7h, 0000051h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh
    dd 00404fch, 0000039h, 0000031h, 00101feh, 0bdbdffh
    dd 00a0af7h, 0000086h, 00a0af3h, 0a8a8feh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0c7c7ffh, 00c0cf7h, 0000052h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00404fbh, 0f7f7ffh, 0ffffffh, 0ffffffh, 00404fch
    dd 0000039h, 0000031h, 00101feh, 00a0af5h, 0000066h
    dd 0000033h, 0000057h, 00a0af3h, 0a8a8feh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0bfbfffh, 00404fch, 000002ch
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00404fbh
    dd 0f7f7ffh, 0ffffffh, 0ffffffh, 00404fch, 0000039h
    dd 0000031h, 00404e3h, 0000041h, 0000033h, 0000033h
    dd 0000031h, 000003dh, 00a0af3h, 0a7a7feh, 0ffffffh
    dd 0f7f7ffh, 03c3cf7h, 00909beh, 0000033h, 000000bh
    dd 0000000h, 0000000h, 0000000h, 00606f8h, 0f1f1ffh
    dd 0ffffffh, 0fbfbffh, 00505fbh, 0000038h, 0000031h
    dd 0000005h, 0000001h, 0000033h, 0000031h, 000000bh
    dd 0000000h, 0000034h, 00a0af3h, 09f9ffeh, 03c3cf7h
    dd 00909beh, 0000035h, 0000033h, 0000031h, 0000004h
    dd 0000000h, 0000000h, 00b0b90h, 00202fdh, 00000ffh
    dd 00202feh, 00c0cb2h, 0000033h, 0000031h, 0000005h
    dd 0000000h, 000002ch, 000000bh, 0000000h, 0000000h
    dd 0000000h, 0000035h, 00808f3h, 00909beh, 0000035h
    dd 0000033h, 0000031h, 0000021h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000032h, 0000033h
    dd 0000033h, 0000033h, 0000031h, 0000004h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000001bh, 0000032h, 0000033h, 0000031h
    dd 0000021h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 000001dh, 0000033h, 0000033h
    dd 0000033h, 0000022h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000000ch, 0000032h, 0000021h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000005h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
