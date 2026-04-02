; Test every single control instruction 

; Test JMP
SET reg[a] 10;             a = 10
JMP 12;                    Skip over the next instruction
CLR reg[a];
OUT reg[a];                Should return 10

; Test JEI
SET reg[a] 5;              a = 5

JEI 28 reg[a] 5;         if (a == 5) { PC = 0x1c }
CLR reg[a];
OUT reg[a];                Should return 5

; Test JER
SET reg[a] 3;              a = 3
MOV reg[a] reg[b];         b = a

JER 48 reg[a] reg[b];      if (a == b) { PC == #### }
CLR reg[a];
OUT reg[a];                Should return 3

HLT;