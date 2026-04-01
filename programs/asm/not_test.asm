SET reg[a] 0;
NOT reg[a], reg[b];
OUT reg[b];            Should return 255

SET reg[a] 1;
NOT reg[a], reg[b];
OUT reg[b];            Should return 254

HLT;