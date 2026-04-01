#include <stdio.h>

#include "cpu.h"
#include "instructions.h"

int execute(CPU *cpu_ptr, uint8_t op, uint8_t a, uint8_t b, uint8_t c) {
    switch(op) {
        // In each switch statement, increment cpu_ptr->PC accordingly. 
        case 0x01: // SET 
            cpu_ptr->registers[a] = b;
            cpu_ptr->PC += 4;
            break;

        case 0x02: // MOV
            cpu_ptr->registers[b] = cpu_ptr->registers[a];
            cpu_ptr->PC += 4;
            break;

        case 0x03: // CLR
            cpu_ptr->registers[a] = 0;
            cpu_ptr->PC += 4;
            break;

        case 0x04: // GET
            cpu_ptr->registers[a] = cpu_ptr->RAM[cpu_ptr->registers[b] + c];
            cpu_ptr->PC += 4;
            break;

        case 0x05: // STR
            printf("Storing to address: %02x", cpu_ptr->registers[b] + c);
            cpu_ptr->RAM[cpu_ptr->registers[b] + c] = cpu_ptr->registers[a];
            cpu_ptr->PC += 4;
            break;

        case 0x06: // OUT
            printf("OUT [%c=0x%02x | %d]\n", register_ids[a], cpu_ptr->registers[a], cpu_ptr->registers[a]);
            cpu_ptr->PC += 4;
            break;

        case 0xa1: // ADI
            cpu_ptr->registers[c] = cpu_ptr->registers[a] + b;
            cpu_ptr->PC += 4;
            break;

        case 0xa2: // ADD
            cpu_ptr->registers[c] = cpu_ptr->registers[a] + cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa3: // SUI
            cpu_ptr->registers[c] = cpu_ptr->registers[a] - b;
            cpu_ptr->PC += 4;
            break;
        
        case 0xa4: // SUB
            cpu_ptr->registers[c] = cpu_ptr->registers[a] - cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa5: // AND
            cpu_ptr->registers[c] = cpu_ptr->registers[a] & cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa6: // OR
            cpu_ptr->registers[c] = cpu_ptr->registers[a] | cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa7: // XOR
            cpu_ptr->registers[c] = cpu_ptr->registers[a] ^ cpu_ptr->registers[b];
            cpu_ptr->PC += 4;
            break;

        case 0xa8: // NOT
            cpu_ptr->registers[b] =  ~cpu_ptr->registers[a];
            cpu_ptr->PC += 4;
            break;

        case 0xb2: // HLT 
            cpu_ptr->running = 0;
            printf("HLT\n");
            break;

        case 0xb3: // JMP
            cpu_ptr->PC = a;
            break;

        default: 
            printf("Unknown opcode: 0x%02x\n", op);
            cpu_ptr->running = 0;
            break;
    }

    return 0;
}