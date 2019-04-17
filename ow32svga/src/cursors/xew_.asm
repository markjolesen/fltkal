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

public __cursor_ew
__cursor_ew label dword
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
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000007h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0010153h, 00202f5h, 0000001h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00303efh, 000004ch, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0010153h, 00d0df5h, 00101ffh, 0000003h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00101feh
    dd 00c0cf6h, 001014dh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0010153h, 00c0cf6h
    dd 0cbcbffh, 00101feh, 0000030h, 000000eh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00101feh, 0cbcbffh
    dd 00d0df6h, 0010150h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0010153h, 00c0cf6h, 0cbcbffh, 0ffffffh
    dd 00101feh, 0000034h, 000000fh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00101feh, 0fdfdffh, 0cdcdffh
    dd 00d0df6h, 0010150h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0010153h
    dd 00d0df5h, 0ceceffh, 0ffffffh, 0ffffffh, 00d0dfbh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00b0bfbh, 0fefeffh, 0ffffffh, 0cacaffh
    dd 00c0cf7h, 000004ch, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0010153h, 00c0cf6h, 0cbcbffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0cdcdffh
    dd 00d0df6h, 0010150h, 0000000h, 0000000h, 0000000h
    dd 0010149h, 00d0df5h, 0ceceffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0cacaffh
    dd 00c0cf7h, 0010144h, 0000000h, 0000000h, 0000045h
    dd 00c0cf5h, 0cacaffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0c7c7ffh, 00c0cf7h
    dd 0000059h, 0000000h, 0000000h, 0000000h, 000004bh
    dd 00c0cf6h, 0c8c8ffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ccccffh, 00d0df7h, 0000071h, 0000031h
    dd 000001dh, 0000000h, 0000000h, 0000003h, 001016dh
    dd 00c0cf7h, 0cacaffh, 0ffffffh, 0ffffffh, 00e0efch
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00b0bfch, 0fefeffh, 0ffffffh, 0c7c7ffh
    dd 00c0cf7h, 000006dh, 0000033h, 0000031h, 000001ch
    dd 0000000h, 0000000h, 0000000h, 0000004h, 0000068h
    dd 00c0cf6h, 0c8c8ffh, 0ffffffh, 00101feh, 0000035h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 0000033h
    dd 00101feh, 0fdfdffh, 0ccccffh, 00d0df7h, 0000071h
    dd 0000033h, 0000031h, 000001eh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000005h, 0000069h
    dd 00c0cf6h, 0c8c8ffh, 00101feh, 0000033h, 0000033h
    dd 0000033h, 0000033h, 0000033h, 0000033h, 00101feh
    dd 0cacaffh, 00d0df7h, 0000071h, 0000033h, 0000031h
    dd 000001eh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000005h, 000006ch
    dd 00c0cf7h, 00101ffh, 0000032h, 000000fh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 00101feh, 00c0cf7h
    dd 000006dh, 0000033h, 0000031h, 000001eh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000005h, 001016dh
    dd 00202f5h, 0000031h, 000000fh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00303ebh, 0000065h, 0000033h
    dd 0000031h, 0000020h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000006h, 0000031h
    dd 0000032h, 000000fh, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000001h, 0000027h, 0000032h, 000001fh
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000006h, 000002dh
    dd 000000dh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000023h, 000001fh, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000001h, 0000000h, 0000000h, 0000000h, 0000000h
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
