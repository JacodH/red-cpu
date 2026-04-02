# Red
First (ish) attempt at a CPU emulator for a custom-designed CPU. The goals of the Red 1 are: 
1. Fully working stack
2. Calculate the Fibonacci sequence
3. Solve the first 3 digits of PI
4. Render hexadecimal to a VRAM monitor

Specs: 
 - Memory: 256 bytes
 - Registers: 8, (a, b, c, d, e, f, g, z)
 - Stack pointer (SP)
 - Program counter (PC)
 - Fixed instruction size of 4 bytes
 - Only unsigned 
 - Von Neumann architecture

# Syntax
```
Instruction    = OPCODE operands...,
TAR            = Target(s) of instruction 
SRC            = Source(s) of instruction 
DST            = Destination of instruction 
ADDR           = Address
IMM            = Immediate value
SP             = Stack pointer register
PC             = Program counter
Register       = r[a | b | c | d | e | f | g | z]
RAM            = RAM[address]
```

## Table

#### Memory
| Code | Description                             | Name | o1     | o2     | o3  |
| ---- | --------------------------------------- | ---- | ------ | ------ | --- |
| 0x01 | Sets register to immediate              | SET  | r[TAR] | IMM    |     |
| 0x02 | Moves content from register to register | MOV  | r[SRC] | r[DST] |     |
| 0x03 | Clears content in register              | CLR  | r[TAR] |        |     |
| 0x04 | Load from RAM into register             | GET  | r[DST] | r[SRC] | IMM |
| 0x05 | Store register into RAM                 | STR  | r[SRC] | r[DST] | IMM |
| 0x06 | Outputs register to console             | OUT  | r[SRC] |        |     |

#### Arithmetic
| Code | Description                            | Name | o1      | o2      | o3     |
| ---- | -------------------------------------- | ---- | ------- | ------- | ------ |
| 0xa1 | Adds an immediate to a register        | ADI  | r[TAR]  | IMM     | r[DST] |
| 0xa2 | Adds 2 registers                       | ADD  | r[SRC1] | r[SRC2] | r[DST] |
| 0xa3 | Subtracts an immediate from a register | SUI  | r[TAR]  | IMM     | r[DST] |
| 0xa4 | Subtracts a register from a register   | SUB  | r[SRC1] | r[SRC2] | r[DST] |
| 0xa5 | Bitwise AND gate                       | AND  | r[SRC1] | r[SRC2] | r[DST] |
| 0xa6 | Bitwise OR gate                        | OR   | r[SRC1] | r[SRC2] | r[DST] |
| 0xa7 | Bitwise XOR gate                       | XOR  | r[SRC1] | r[SRC2] | r[DST] |
| 0xa8 | Bitwise NOT gate                       | NOT  | r[SRC]  | r[DST]  |        |
| 0xa9 | Bitwise shift left                     | SHL  | r[SRC]  | IMM     | r[DST] |
| 0xaa | Bitwise shift right                    | SHR  | r[SRC]  | IMM     | r[DST] |
| 0xab | Less than comparison                   | LT   | r[SRC1] | r[SRC2] | r[DST] |
| 0xac | Greater than comparison                | GT   | r[SRC1] | r[SRC2] | r[DST] |
| 0xad | Equal comparison                       | EQ   | r[SRC1] | r[SRC2] | r[DST] |
| 0xae | Not equal comparison                   | NE   | r[SRC1] | r[SRC2] | r[DST] |

#### Control
| Code | Description                                                                     | Name | o1     | o2      | o3      |
| ---- | ------------------------------------------------------------------------------- | ---- | ------ | ------- | ------- |
| 0xb1 | No operation                                                                    | NOP  |        |         |         |
| 0xb2 | Stops CPU                                                                       | HLT  |        |         |         |
| 0xb3 | Sets PC to ADDR                                                                 | JMP  | ADDR   |         |         |
| 0xb4 | Sets PC to ADDR if a register matches an immediate                              | JEI  | ADDR   | r[SRC]  | IMM     |
| 0xb5 | Sets PC to ADDR if a register matches another register                          | JER  | ADDR   | r[SRC1] | r[SRC2] |
| 0xb6 | Pushes register to stack, increments stack pointer                              | PUSH | r[SRC] |         |         |
| 0xb7 | Pops content to register, decrementing  stack pointer                            | POP  | r[DST] |         |         |
| 0xb8 | Pushes next instruction address to stack, then sets the program counter to ADDR | CALL | ADDR   |         |         |
| 0xb9 | Pops address from stack into PC                                                 | RET  |        |         |         |

### Implemented 
 - [x] SET
 - [x] MOV
 - [x] CLR
 - [x] GET
 - [x] STR
 - [x] OUT
 - [x] ADI
 - [x] ADD
 - [x] SUI
 - [x] SUB
 - [x] AND
 - [x] OR
 - [x] XOR
 - [x] NOT
 - [x] SHL
 - [x] SHR
 - [x] LT
 - [x] GT
 - [x] EQ
 - [x] NE
 - [x] NOP
 - [x] HLT
 - [x] JMP
 - [ ] JEI
 - [ ] JER
 - [ ] PUSH
 - [ ] POP
 - [ ] CALL
 - [ ] RET

# Emulation
