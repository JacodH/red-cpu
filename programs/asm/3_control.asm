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

JER 48 reg[a] reg[b];      if (a == b) { PC == 48 }
CLR reg[a];
OUT reg[a];                Should return 3

; Test JMPR
SET reg[a] 10;             a = 10
SET reg[b] 68;             b = $68

JMPR reg[b];               Skip over the next instruction
CLR reg[a];
OUT reg[a];                Should return 10

; Test JEIR Jumps to register stored address if r[src] == immediate
SET reg[a] 7;              a = 7
SET reg[b] 0x58;           b = 0x58

JEIR reg[b] reg[a] 7;      if (a == 7) { PC = reg[b] }
CLR reg[a];
OUT reg[a];                Should return 7

; Test JERR 
SET reg[a] 6;              a = 6
SET reg[b] 6;              b = 6
SET reg[c] 0x70;           c = 0x70

JMRR reg[c] reg[a] reg[b]; if (a == b) { PC == reg[c] }
CLR reg[a];
OUT reg[a];                Should return 6

; Full test suit: [10, 5, 3, 10, 7, 6]

HLT;