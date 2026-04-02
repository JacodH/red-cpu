SET reg[a] 0x0a;       a = 10
MOV reg[a] reg[b];     b = a

OUT reg[b];            print(b)   |   Should be 10

SET reg[a] 0x05;       a = 5

OUT reg[a];            print(a)   |   Should be 5
CLR reg[a];            a = 0
OUT reg[a];            print(a)   |   Should be 0

SET reg[a] 0xf0;       a = 0xf0;

STR reg[b] reg[a] 0;   ram[a + 0] = b

CLR reg[b];            b = 0

OUT reg[b];            print(b)   |   Should be 0

GET reg[b] reg[a] 0;   b = ram[a + 0]

OUT reg[b];            print(b)   |   Should be 10
HLT;                   exit