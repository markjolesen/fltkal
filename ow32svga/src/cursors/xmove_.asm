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

public __cursor_move
__cursor_move label dword
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
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0060678h
    dd 004046bh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0050582h, 01f1ff4h, 01818f5h
    dd 0040472h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 005057ch, 01e1ef5h, 0e6e6ffh, 0e2e2ffh, 01919f6h
    dd 005057fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 005057ch, 01e1ef5h
    dd 0e6e6ffh, 0ffffffh, 0ffffffh, 0e2e2ffh, 01a1af7h
    dd 0050580h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0050583h, 02020f4h, 0e8e8ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0e1e1ffh, 01818f7h
    dd 005057fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0050585h
    dd 00000ffh, 00000ffh, 00000ffh, 01010fbh, 0ffffffh
    dd 0fcfcffh, 00a0afch, 00000ffh, 00000ffh, 00000ffh
    dd 003037fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0050585h, 01b1bf5h, 00404fah
    dd 0000000h, 000001eh, 00303fdh, 0ffffffh, 0fafaffh
    dd 00202fdh, 0000033h, 0000039h, 00202fdh, 01818f7h
    dd 0050580h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050585h, 01e1ef5h, 0ddddffh, 00404fah, 000001bh
    dd 0000037h, 00303fdh, 0ffffffh, 0f9f9ffh, 00303fdh
    dd 0000033h, 0000038h, 00404fch, 0e2e2ffh, 01919f7h
    dd 0040487h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0050585h, 01f1ff4h
    dd 0e8e8ffh, 0fafaffh, 00808fch, 00000ffh, 00000ffh
    dd 00f0ffah, 0ffffffh, 0fcfcffh, 00909fch, 00000ffh
    dd 00000ffh, 01010f9h, 0ffffffh, 0e1e1ffh, 01818f7h
    dd 003037fh, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 005057ch, 01f1ff4h, 0e8e8ffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0e1e1ffh, 01818f7h
    dd 005057ah, 0000000h, 0000000h, 0000000h, 0000000h
    dd 005057ch, 01f1ff4h, 0e8e8ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0e1e1ffh, 01818f7h, 0040487h
    dd 0000017h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050585h, 01f1ff5h, 0e8e8ffh, 0fafaffh, 00a0afch
    dd 00000ffh, 00000ffh, 01212fbh, 0ffffffh, 0fcfcffh
    dd 00b0bfch, 00000ffh, 00000ffh, 01414fbh, 0ffffffh
    dd 0e1e1ffh, 01818f7h, 003038eh, 0000033h, 0000031h
    dd 0000016h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050589h, 01d1df7h, 0ddddffh, 00404fbh, 0000033h
    dd 0000039h, 00404fch, 0ffffffh, 0f9f9ffh, 00303fdh
    dd 0000033h, 0000039h, 00404fch, 0e2e2ffh, 01919f7h
    dd 004048eh, 0000033h, 0000033h, 0000031h, 0000015h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050592h, 01b1bf7h, 00404fbh, 0000033h, 0000038h
    dd 00404fch, 0ffffffh, 0f9f9ffh, 00303fdh, 0000033h
    dd 0000038h, 00202fdh, 01818f7h, 004048eh, 0000033h
    dd 0000033h, 0000031h, 0000017h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050591h, 00000ffh, 00000ffh, 00000ffh, 01111f9h
    dd 0ffffffh, 0fcfcffh, 00909fch, 00000ffh, 00000ffh
    dd 00000feh, 0030372h, 0000032h, 0000033h, 0000031h
    dd 0000017h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 005058ah, 01d1df7h, 0e6e6ffh, 0ffffffh, 0ffffffh
    dd 0ffffffh, 0ffffffh, 0e2e2ffh, 01919f7h, 0040472h
    dd 0000002h, 0000033h, 0000031h, 0000017h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 005058ah, 01d1df7h, 0e6e6ffh, 0ffffffh, 0ffffffh
    dd 0e2e2ffh, 01919f7h, 004048eh, 0000033h, 0000033h
    dd 0000033h, 0000016h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050589h, 01d1df7h, 0e6e6ffh, 0e2e2ffh, 01a1af7h
    dd 005058eh, 0000033h, 0000033h, 0000031h, 0000017h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050591h, 01f1ff6h, 01919f7h, 005058fh, 0000033h
    dd 0000033h, 0000031h, 0000017h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0050587h, 0040488h, 0000033h, 0000033h, 0000031h
    dd 0000017h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 000001bh, 0000031h, 0000031h, 0000017h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000018h, 0000016h, 0000000h, 0000000h, 0000000h
    dd 0000000h, 0000000h, 0000000h, 0000000h, 0000000h
    dd 0000000h

end
