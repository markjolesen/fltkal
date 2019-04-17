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

public __cursor_hand
__cursor_hand label dword
    dd 24, 24
    dd 0, 3
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0010141h, 00d0de3h
    dd 00101feh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00505f6h, 000003eh, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 00b0bebh, 0b8b8ffh, 0fdfdffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0bebeffh, 00b0bf4h, 0000040h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 00a0aefh, 0bdbdffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0c0c0ffh, 00b0bf5h, 0000043h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0010167h, 00c0cebh, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 00000ffh
    dd 02121ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0c2c2ffh, 00b0bf5h, 0000045h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000030h
    dd 0000033h, 0000033h, 0000033h, 00b0bech, 0b1b1ffh
    dd 0fcfcffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0c4c4ffh, 00505f8h, 0000001h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000010h, 000002fh
    dd 0000033h, 0000033h, 00a0af2h, 0c0c0ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 00101feh, 0000002h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0010198h, 00000ffh, 00000ffh, 00000ffh
    dd 00000ffh, 00000ffh, 01f1fffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 00000ffh, 0000002h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 00a0aefh, 0b9b9ffh, 0fdfdffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0c9c9ffh, 00505ffh
    dd 0000040h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 00b0bebh
    dd 0b4b4ffh, 0fdfdffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0c9c9ffh, 01616ffh, 07878feh, 00606f7h
    dd 0000040h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 000005fh, 00808f0h
    dd 00000ffh, 00000ffh, 00000ffh, 00000ffh, 02020ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0c9c9ffh
    dd 01717ffh, 0b5b5ffh, 0ffffffh, 0a8a8feh, 00606f7h
    dd 0000040h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000030h, 00b0befh, 0b7b7ffh
    dd 0fdfdffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0c9c9ffh, 01717ffh, 0b5b5ffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0a7a7feh, 00606f7h
    dd 000003fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 000000eh, 00a0af0h, 0bcbcffh, 0fdfdffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0c9c9ffh, 01717ffh, 0b5b5ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 05050fbh, 00707b0h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0010166h, 00c0ceah, 00101feh, 00000ffh
    dd 00909fbh, 0bebeffh, 0ffffffh, 0cacaffh, 01717ffh
    dd 0b4b4ffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 08383fah, 00e0eddh, 000001ah, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000030h, 0000033h, 0000033h, 0000033h, 0000065h
    dd 00505f8h, 00000ffh, 00505ffh, 0b3b3ffh, 0ffffffh
    dd 03a3affh, 03c3cffh, 0ffffffh, 0ffffffh, 08585fbh
    dd 00e0edeh, 000003eh, 0000023h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000010h
    dd 000002eh, 0000033h, 0000033h, 0000033h, 0000031h
    dd 0000045h, 00909e4h, 05c5cfah, 0fdfdffh, 03c3cffh
    dd 03d3dffh, 0ffffffh, 08888fbh, 00d0de1h, 0000040h
    dd 000002ah, 0000003h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000001h, 0000022h, 0000033h
    dd 0000044h, 00a0ae4h, 05f5ffbh, 0fefeffh, 0ffffffh
    dd 08888fbh, 00d0de1h, 0000040h, 000002ah, 0000003h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000004h, 000002ch
    dd 0000046h, 00909e6h, 06666fbh, 08787fbh, 00e0ee0h
    dd 000003fh, 000002ch, 0000003h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000004h, 000002ch
    dd 0000047h, 00909e7h, 00d0de0h, 000003fh, 000002ch
    dd 0000004h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000005h, 000002dh
    dd 000003fh, 000003ah, 000002bh, 0000003h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000005h, 000002dh
    dd 000002bh, 0000003h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000003h, 0000002h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
