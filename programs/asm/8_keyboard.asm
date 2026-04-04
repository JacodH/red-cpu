loop:
    CALL $poll;
    JMP $loop;

poll:
    GET reg[a] reg[b] 0xe6;
    OUT reg[a];
    RET;
