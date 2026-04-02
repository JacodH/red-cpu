; Test every single arithmetic instruction 

; Test ADI
SET reg[a] 3;              a = 3
ADI reg[a] 2 reg[a];       a += 2
OUT reg[a];                Should return 5

; Test ADD
SET reg[a] 7;              a = 7
SET reg[b] 10;             b = 10
ADD reg[a] reg[b] reg[c];  c = a + b
OUT reg[c];                Should return 17

; Test SUI 
SET reg[a] 10;             a = 10
SUI reg[a] 3 reg[a];       a -= 3
OUT reg[a];                Should return 7

; Test SUB
SET reg[a] 20;             a = 20
SET reg[b] 17;             b = 17
SUB reg[a] reg[b] reg[c];  c = a - b
OUT reg[c];                Should return 3

; Test AND

SET reg[a] 1;              a = 1
SET reg[b] 1;              b = 1;

AND reg[a] reg[b] reg[c];  c = a & b
OUT reg[c];                Should return 1

; Test OR
SET reg[a] 0;              a = 0
SET reg[b] 1;              b = 1

OR reg[a] reg[b] reg[c];   c = a | b
OUT reg[c];                Should return 1

; Test XOR
SET reg[a] 0;              a = 0
SET reg[b] 1;              b = 1

XOR reg[a] reg[b] reg[c];  c = a ^ b
OUT reg[c];                Should return 1

; Test NOT
SET reg[a] 0;              a = 0

NOT reg[a] reg[b];         b = !a
OUT reg[b];                Should return 255

; Test SHL + SHR
SET reg[a] 2;              a = 2

SHL reg[a] 2 reg[a];       a = a << 2
OUT reg[a];                Should return 8

SHR reg[a] 2 reg[a];       a = a >> 2
OUT reg[a];                Should return 2

; Test LT + GT
SET reg[a] 10;             a = 10
SET reg[b] 5;              b = 5

LT reg[a] reg[b] reg[c];   c = a < b
OUT reg[c];                Should return 0

GT reg[a] reg[b] reg[c];   c = a > b
OUT reg[c];                Should return 1

; Test EQ + NE
SET reg[a] 10;             a = 10
SET reg[b] 7;              b = 7

EQ reg[a] reg[b] reg[c];   c = (a == b)
OUT reg[c];                Should return 0

NE reg[a] reg[b] reg[c];   c = (a != b)
OUT reg[c];                Should return 1

HLT
