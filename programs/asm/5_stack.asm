; Stack test

; Test PUSH
SET reg[a] 0x0a;    a = 10

PUSH reg[a];        push a to stack

CLR reg[a];         a = 0
OUT reg[a];         should return 0

; Test POP
POP reg[a];         pop a from stack
OUT reg[a];         should return 10

; Stack is now empty and pointing at 0xff
CALL $test;

HLT;                This line should be skipped

test:
    POP reg[a];
    OUT reg[a];     Should return 0x1c

; Test RET
SET reg[a] 5;       a = 5

CALL $function;     

OUT reg[a];         Should return 10;

JMP $exit;

function:
    ADI reg[a] 5 reg[a];
    RET;

exit:
    HLT;