SET reg[a], 1;               Set register a to 1
SET reg[b], 0;               Set register b to 0

ADD reg[a], reg[b], reg[c];  Add registers a and b, sum to c

MOV reg[a], reg[b];          Move value at register a to b
MOV reg[c], reg[a];          Move value at register c to a

OUT reg[c];                  Output register c

JMP 8;                       Loop back to add logic