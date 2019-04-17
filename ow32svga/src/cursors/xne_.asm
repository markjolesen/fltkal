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

public __cursor_ne
__cursor_ne label dword
    dd 24, 24
    dd 20, 3
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
    dd 0000000h, 00b0b90h, 00303fbh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00909f2h, 0040462h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000003h
    dd 00404fbh, 0f6f6ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0d6d6ffh, 00a0af1h, 0000007h
    dd 0000000h, 0000000h, 0000000h, 0000004h, 00202fdh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0fbfbffh, 00202fdh, 0000031h, 000001ch
    dd 0000000h, 0000000h, 0000003h, 00303fbh, 0f8f8ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0fbfbffh, 00202fdh, 0000033h, 0000031h, 0000000h
    dd 0000000h, 0000000h, 00b0ba0h, 00101feh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 01515fah, 0ffffffh, 0ffffffh, 0fbfbffh
    dd 00202fdh, 0000033h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000009h, 0000030h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000037h
    dd 00303fdh, 0ffffffh, 0ffffffh, 0fbfbffh, 00202fdh
    dd 0000033h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000020h, 000002eh, 000002eh
    dd 000002dh, 000002ch, 000002ch, 000002ch, 000002ch
    dd 000002ch, 000002ch, 000002ch, 0000030h, 00303fdh
    dd 0ffffffh, 0ffffffh, 0fbfbffh, 00202fdh, 0000033h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00404dfh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00404f2h, 0000001h, 0000005h, 00303fdh, 0ffffffh
    dd 0ffffffh, 0fbfbffh, 00202fdh, 0000033h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000003ch, 00a0af3h, 0bcbcffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 00101feh
    dd 0000002h, 0000005h, 00303fdh, 0ffffffh, 0ffffffh
    dd 0fbfbffh, 00202fdh, 0000033h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000040h, 00a0af6h, 0bebeffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 00101feh, 0000035h
    dd 0000034h, 00303fdh, 0ffffffh, 0ffffffh, 0fbfbffh
    dd 00202fdh, 0000033h, 0000032h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000007ch, 01515f9h, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 00101feh, 0000035h, 0000036h
    dd 00303fdh, 0ffffffh, 0ffffffh, 0fbfbffh, 00202fdh
    dd 0000033h, 0000032h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 000003eh, 00b0bf4h
    dd 0bebeffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00101feh, 0000035h, 0000036h, 00303fdh
    dd 0ffffffh, 0ffffffh, 0fbfbffh, 00202fdh, 0000033h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000003eh, 00b0bf4h, 0bfbfffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00101feh, 0000035h, 0000036h, 00303fdh, 0ffffffh
    dd 0ffffffh, 0fbfbffh, 00202fdh, 0000033h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000044h
    dd 00b0bf4h, 0c3c3ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0afaffeh, 00e0efah, 0bfbfffh, 0ffffffh, 00101feh
    dd 0000035h, 0000036h, 00303fdh, 0ffffffh, 0ffffffh
    dd 0fbfbffh, 00202fdh, 0000033h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000044h, 00b0bf4h, 0c3c3ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0afaffeh, 00a0af4h
    dd 0000089h, 00a0af6h, 0bfbfffh, 00101feh, 0000035h
    dd 0000036h, 00303fdh, 0ffffffh, 0ffffffh, 0fbfbffh
    dd 00202fdh, 0000033h, 0000032h, 0000000h, 0000000h
    dd 000001dh, 00404fah, 0bbbbffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0aeaefeh, 00a0af4h, 000005bh, 0000033h
    dd 0000065h, 00b0bf6h, 00101ffh, 0000035h, 0000036h
    dd 00303fdh, 0ffffffh, 0ffffffh, 0fbfbffh, 00202fdh
    dd 0000033h, 0000032h, 0000000h, 0000000h, 0000003h
    dd 00909aeh, 03a3af4h, 0f6f6ffh, 0ffffffh, 0aeaefeh
    dd 00a0af4h, 000005ah, 0000033h, 0000033h, 0000030h
    dd 000004eh, 00303ech, 0000034h, 0000036h, 00303fdh
    dd 0ffffffh, 0ffffffh, 0fbfbffh, 00202fdh, 0000033h
    dd 0000032h, 0000000h, 0000000h, 0000000h, 0000003h
    dd 00808afh, 03a3af6h, 0a5a5feh, 00a0af4h, 000005ah
    dd 0000033h, 0000033h, 0000030h, 0000009h, 0000000h
    dd 000000ch, 0000031h, 0000035h, 00404fch, 0fbfbffh
    dd 0ffffffh, 0f5f5ffh, 00404fch, 0000033h, 0000032h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000003h
    dd 00909b9h, 00707f5h, 000005ah, 0000033h, 0000033h
    dd 0000030h, 000000ah, 0000000h, 0000000h, 0000000h
    dd 000000ch, 000002bh, 00c0ca0h, 00404fch, 00000ffh
    dd 00202feh, 00c0caah, 0000033h, 0000032h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000003h
    dd 0000032h, 0000031h, 0000033h, 0000031h, 000000ah
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 000000ah, 0000031h, 0000033h
    dd 0000033h, 0000033h, 0000031h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000001h
    dd 0000022h, 0000031h, 000000bh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000023h, 0000033h, 0000033h
    dd 0000032h, 000001bh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000005h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
