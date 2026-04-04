#include <stdio.h>

#include "cpu.h"
#include "instructions.h"

int execute(CPU *cpu_ptr, uint8_t op, uint8_t a, uint8_t b, uint8_t c, int dev) {
    if (dev) {printf("0x%02x #%d | ", cpu_ptr->PC, cpu_ptr->PC/4);}
    switch(op) {
        // In each switch statement, increment cpu_ptr->PC accordingly. 
        case 0x01: // SET 
            if (dev) {printf("SET reg[%02x] %02x\n", a, b);}
            cpu_ptr->registers[a] = b;
            cpu_ptr->PC += 4;
            break;

        case 0x02: // MOV
            if (dev) {printf("MOV reg[%02x] reg[%02x]\n", a, b);}
            cpu_ptr->registers[b] = cpu_ptr->registers[a];
            cpu_ptr->PC += 4;
            break;

        case 0x03: // CLR
            if (dev) {printf("CLR reg[%02x]\n", a);}
            cpu_ptr->registers[a] = 0;
            cpu_ptr->PC += 4;
            break;

        case 0x04: // GET
            if (dev) {printf("GET reg[%02x] reg[%02x] %02x\n", a, b, c);}
            cpu_ptr->registers[a] = cpu_ptr->RAM[cpu_ptr->registers[b] + c];
            cpu_ptr->PC += 4;
            break;

        case 0x05: // STR
            if (dev) {printf("STR r[%02x] r[%02x] %02x\n", a, b, c);}
            cpu_ptr->RAM[cpu_ptr->registers[b] + c] = cpu_ptr->registers[a];
            cpu_ptr->PC += 4;

            break;

        case 0x06: // OUT
            printf("OUT reg[%02x] = [0x%02x | %d]\n", a, cpu_ptr->registers[a], cpu_ptr->registers[a]);
            cpu_ptr->PC += 4;
            break;

        case 0x07: // ROM
            if (dev) {printf("ROM reg[%02x] reg[%02x] %02x\n", a, b, c);}
            cpu_ptr->registers[a] = cpu_ptr->ROM[cpu_ptr->registers[b] + c];
            cpu_ptr->PC += 4;
            break;

        case 0xa1: // ADI
            if (dev) {printf("ADI r[%02x] %02x r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] + b;
            cpu_ptr->PC += 4;
            break;

        case 0xa2: // ADD
            if (dev) {printf("ADD r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] + cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa3: // SUI
            if (dev) {printf("SUI r[%02x] r[%02x] %02x\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] - b;
            cpu_ptr->PC += 4;
            break;
        
        case 0xa4: // SUB
            if (dev) {printf("SUB r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] - cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa5: // AND
            if (dev) {printf("AND r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] & cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa6: // OR
            if (dev) {printf("OR r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] | cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa7: // XOR
            if (dev) {printf("XOR r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] ^ cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa8: // NOT
            if (dev) {printf("NOT r[%02x] r[%02x]\n", a, b);}
            cpu_ptr->registers[b] =  ~cpu_ptr->registers[a];
            cpu_ptr->PC += 4;
            break;

        case 0xa9: // SHL:
            if (dev) {printf("SHL r[%02x] %02x\n", a, b);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] << b;
            cpu_ptr->PC += 4;
            break;

        case 0xaa: // SHR:
            if (dev) {printf("SHR r[%02x] %02x\n", a, b);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] >> b;
            cpu_ptr->PC += 4;
            break;

        case 0xab: // LT:
            if (dev) {printf("LT r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] < cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xac: // GT:
            if (dev) {printf("GT r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] > cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xad: // EQ:
            if (dev) {printf("EQ r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] == cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xae: // NE:
            if (dev) {printf("NE r[%02x] r[%02x] r[%02x]\n", a, b, c);}
            cpu_ptr->registers[c] = cpu_ptr->registers[a] != cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xb1: // NOP:
            cpu_ptr->PC += 4;
            break;

        case 0xb2: // HLT 
            cpu_ptr->running = 0;
            printf("HLT\n");
            break;

        case 0xb3: // JMP
            if (dev) {printf("JMP 0x%02x\n", a);}
            cpu_ptr->PC = a;
            break;

        case 0xb4: // JEI
            if (dev) {printf("JEI 0x%02x, r[%02x] %02x\n", a, b, c);}
            if (cpu_ptr->registers[b] == c) {
                cpu_ptr->PC = a;
            }else {
                cpu_ptr->PC += 4;
            }
            break;

        case 0xb5: // JER
            if (dev) {printf("JER 0x%02x, r[%02x] r[%02x]\n", a, b, c);}
            if (cpu_ptr->registers[b] == cpu_ptr->registers[c]) {
                cpu_ptr->PC = a;
            }else {
                cpu_ptr->PC += 4;
            }
            break;

        case 0xb6: // JMPR
            if (dev) {printf("JMPR r[%02x]\n", a);}
            cpu_ptr->PC = cpu_ptr->registers[a];
            break;

        case 0xb7: // JMIR
            if (dev) {printf("JEIR r[%02x], r[%02x] %02x\n", a, b, c);}
            if (cpu_ptr->registers[b] == c) { cpu_ptr->PC = cpu_ptr->registers[a]; } 
            else cpu_ptr->PC += 4;
            break;

        case 0xb8: // JMRR
            if (dev) {printf("JMRR r[%02x], r[%02x] r[%02x]\n", a, b, c);}
            if (cpu_ptr->registers[b] == cpu_ptr->registers[c]) { cpu_ptr->PC = cpu_ptr->registers[a]; } 
            else cpu_ptr->PC += 4;
            break;

        case 0xc1: // PUSH
            if (dev) {printf("PUSH r[%02x]\n", a);}
            cpu_ptr->RAM[cpu_ptr->registers[0x07]] = cpu_ptr->registers[a];
            cpu_ptr->registers[0x07]--;
            cpu_ptr->PC += 4;
            break;

        case 0xc2: // POP
            if (dev) {printf("POP r[%02x]\n", a);}
            cpu_ptr->registers[0x07]++;
            cpu_ptr->registers[a] = cpu_ptr->RAM[cpu_ptr->registers[0x07]];
            cpu_ptr->PC += 4;
            break;
        
        case 0xc3: // CALL
            if (dev) {printf("CALL 0x%02x\n", a);}
            cpu_ptr->RAM[cpu_ptr->registers[0x07]] = cpu_ptr->PC+4;
            cpu_ptr->registers[0x07]--;

            cpu_ptr->PC = a;
            break;

        case 0xc4: // RET
            if (dev) {printf("RET\n");}
            cpu_ptr->registers[0x07]++;
            cpu_ptr->PC = cpu_ptr->RAM[cpu_ptr->registers[0x07]];
            
            break;

        default: 
            printf("Unknown opcode: 0x%02x\n", op);
            cpu_ptr->running = 0;
            break;
    }

    printf("\n");

    return 0;
}