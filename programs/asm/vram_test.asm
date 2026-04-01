SET reg[a] 25;             Set register A to high bitmap of char A

SET reg[b] e0;             Set register B to pointer to ram address of vram for first char

STR reg[a] reg[b] 0;       Send reg[a] vram!
SET reg[a] 75;             Set reg[a] to low bitmap of char a

STR reg[a] reg[b] 1;       Send reg[a] NEXT vram!

SET reg[a] 46;             High bitmap of char B
STR reg[a] reg[b] 2;       Send reg[a] NEXT vram!

SET reg[a] 57;             Low bitmap of char B
STR reg[a] reg[b] 3;       Send reg[a] NEXT vram!

SET reg[a] 74;             High bitmap of char C
STR reg[a] reg[b] 4;       Send reg[a] NEXT vram!

SET reg[a] 47;             Low bitmap of char C
STR reg[a] reg[b] 5;       Send reg[a] NEXT vram!

HLT;