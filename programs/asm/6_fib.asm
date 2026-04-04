SET reg[a] 0;         a = 0
SET reg[b] 1;         b = 1
SET reg[c] 0;         c = 0;

OUT reg[c];

SET reg[d] 0;         d = 0

loop:
    CALL $fib;        
    OUT reg[c];           print(c)

    ADI reg[d] 1 reg[d];  d++;
    JEI $exit reg[d] 10;  if (d == 10) { $exit }

    JMP $loop;            redo loop

fib:
    ADD reg[a] reg[b] reg[c];   c = a + b

    MOV reg[a] reg[b];          move a -> b
    MOV reg[c] reg[a];          move c -> a
    RET;

exit:
    HLT;