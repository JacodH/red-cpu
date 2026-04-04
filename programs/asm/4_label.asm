; Testing labeled jumps 
; For loop test 
; Should print 1,2,3,4,5,6,7,8,9,10, HLT

SET reg[a] 0;
add:
    ADI reg[a] 1 reg[a];
    OUT reg[a];
    JEI $exit reg[a] 10;
    JMP $add;

exit:
    HLT;
