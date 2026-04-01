SET reg[a], 1;
SET reg[b], 1;
XOR reg[a], reg[b], reg[c];
OUT reg[c];                   Should return 0;

SET reg[a], 0;

XOR reg[a], reg[b], reg[c];
OUT reg[c];                   Should return 1

SET reg[b], 0; 

XOR reg[a], reg[b], reg[c];
OUT reg[c];                   Should return 0;
HLT;