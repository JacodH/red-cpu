; Echos keyboard input to monitor
; Only echos chars in font: 
; 0,1,2,3,4,5,6,7,8,9,a,b,c,d,e,f

loop:
    CALL $poll;
    JMP $loop;

poll:
    SET reg[a] 0;
    SET reg[b] 0;
    GET reg[a] reg[b] 0xe6;     Get last pressed key
    
    OUT reg[a];

    JEI $exit reg[a] 0xd0;      if key == escape, exit

    CALL $ascii_to_font_ptr;

    SET reg[b] 0;
    CALL $display_char;
    RET;

ascii_to_font_ptr:
    ; Parameters
    ; a = value !!! reg[a] MUST be a hexadecimal !!!

    ; Variables
    ; b = comparison_value
    ; c = comparison_result

    ; Check if a is a number
    SET reg[b] 0x40;
    LT reg[a] reg[b] reg[c];      if (reg[a] < 0x40) c = 1 
    JEI $is_number reg[c] 0x01;   a is a number 0-9

    ; Must be a character         a is a char a-f 
    JMP $is_letter;
is_number:
    SUI reg[a] 0x30 reg[a];    reg[a] += 0x30
    RET; returns from ascii_to_font_ptr
is_letter:
    SUI reg[a] 0x57 reg[a];
    RET; returns from ascii_to_font_ptr


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

exit:
    HLT;