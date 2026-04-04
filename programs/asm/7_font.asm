; VRAM STARTS AT 0xe0

SET reg[a] 0x01;
SET reg[b] 0x00;
CALL $display_char;

SET reg[a] 0x02;
SET reg[b] 0x01;
CALL $display_char;

SET reg[a] 0x03;
SET reg[b] 0x02;
CALL $display_char;

CALL $exit_loop;

display_char:
    ; Parameters
    ; a = char
    ; b = position on screen

    ; Variables
    ; c = rom_ptr
    ; d = bitmap_high
    ; e = bitmap_high
    ; f = vram_ptr

    ; Set pointer for ROM lookup
    SHL reg[a] 1 reg[c];   rom_ptr = char * 2

    ; Load font from ROM
    ROM reg[d] reg[c] 0;   a = bitmap_high
    ROM reg[e] reg[c] 1;   b = bitmap_low

    ; Increment dependent on position (multiplication)
    SHL reg[b] 1 reg[f];     f = b * 2
    ADI reg[f] 0xe0 reg[f];  vram_ptr += vram base

    ; Send bitmaps to vram
    STR reg[d] reg[f] 0;   send low to vram
    STR reg[e] reg[f] 1;   send high to vram
    RET;

exit_loop:
    JMP $exit_loop;

HLT;