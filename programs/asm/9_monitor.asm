; Monitor program
; Read any RAM address

; Controls 
; Use left and right arrow keys to go to the next and previous address 
; Use up and down to skip +4 bytes or -4 bytes
; Press R to print RAM to emulator console

; Notes / Constants
; right_arrow = 0x83
; left_arrow  = 0x82
; down_arrow  = 0x81
; up_arrow    = 0x80
; g           = address pointer

SET reg[g] 0x00;

; Render 0x00 first
CALL $draw_address_ptr;

loop:
    ; Get input
    CALL $poll;

    ; Handle input, then go to $draw_address_ptr
    ; Handle address pointer control
    JEI $increment_address_pointer reg[a] 0x83;
    JEI $increment_address_pointer_4 reg[a] 0x81;

    JEI $decrement_address_pointer reg[a] 0x82;
    JEI $decrement_address_pointer_4 reg[a] 0x80;

    JEI $print_ram reg[a] 0x72;

    ; No new input, re-loop
    JMP $loop;

draw_address_ptr:
    ; Draw first char at address pointer
    GET reg[a] reg[g] 0;

    SHR reg[a] 4 reg[a]; 
    SHL reg[a] 4 reg[a];
    SHR reg[a] 4 reg[a];

    SET reg[b] 1;
    CALL $display_char;

    ; Draw second char at address pointer
    GET reg[a] reg[g] 0;

    SHL reg[a] 4 reg[a];
    SHR reg[a] 4 reg[a]; 

    SET reg[b] 2;
    CALL $display_char;

    JMP $loop;

; Can definitely shorten these functions if needed
increment_address_pointer:
    ADI reg[g] 1 reg[g];
    JMP $draw_address_ptr;

increment_address_pointer_4:
    ADI reg[g] 4 reg[g];
    JMP $draw_address_ptr;

decrement_address_pointer:
    SUI reg[g] 1 reg[g];
    JMP $draw_address_ptr;

decrement_address_pointer_4:
    SUI reg[g] 4 reg[g];
    JMP $draw_address_ptr;

print_ram:
    RAM;
    JMP $loop;

poll:
    ; Poll for keyboard input
    ; Sets reg[a] to last pressed key
    ; If its escape it will auto exit the program
    
    ; Parameters 
    ; None

    ; Variables
    ; a = ascii output
    ; b = zero
    SET reg[a] 0;
    SET reg[b] 0;


    GET reg[a] reg[b] 0xe7;        Read new key flag

    ; Display a pixel for input flag
    STR reg[a] reg[b] 0xe0; 

    JEI $no_new_key reg[a] 0x00;   if (key == 0) { no new key }

    ; if it didn't jump that means there is a new key
    STR reg[b] reg[b] 0xe7;        Set input flag to zero
    GET reg[a] reg[b] 0xe6;        Get last pressed key

    JEI $exit reg[a] 0xd0;         if key == escape, exit
    RET;                           Return to where $poll was called

no_new_key:
    SET reg[a] 0;
    RET;                           Return to where $poll was called


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