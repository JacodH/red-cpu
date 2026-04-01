SET reg[a], 6;              Set register a to 6
SET reg[b], 5;              Set register b to 5
SUB reg[a], reg[b], reg[c]; Subtract a by b, send result to c
OUT reg[c];                 Should print out 1, (6-5)
HLT;                        