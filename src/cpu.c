#include <stdio.h>

#include "cpu.h"
#include "instructions.h"

char register_ids[9] = "ABCDEFGZ";

void init_cpu(CPU *cpu_ptr) {
    for (int i = 0; i < 8; i++) {cpu_ptr->registers[i] = 0; }    // Clear all registers 
    for (int i = 0; i < 256; i++) {cpu_ptr->RAM[i] = 0; }; // Clear all RAM

    for (int i = 0; i < 256; i++) {cpu_ptr->ROM[i] = 0; }; // Clear all RAM

    cpu_ptr->registers[7] = 255;

    cpu_ptr->PC = 0;   // Set program counter to 0
    cpu_ptr->running = 1;
}

void load_program(CPU *cpu_ptr, uint8_t program[], int size) {
    for (int i = 0; i < size; i++) {
        cpu_ptr->RAM[i] = program[i];
    }
}

void load_ROM(CPU *cpu_ptr, uint8_t rom[], int size) {
    for (int i = 0; i < size; i++) {
        cpu_ptr->ROM[i] = rom[i];
    }
}

uint8_t fetch(CPU *cpu_ptr, int offset) {
    return cpu_ptr->RAM[cpu_ptr->PC + offset];
}

void print_registers(CPU *cpu_ptr) {
    printf("Registers: \n");
    for (int i = 0; i < 8; i++) {
        printf("[%c=0x%02x] ", register_ids[i], cpu_ptr->registers[i]);
    }
    printf("\n");
    printf("[PC=0x%02x]\n", cpu_ptr->PC);
}

void print_RAM(CPU *cpu_ptr) {
    printf("\nMemory\n   ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", i);
    }

    for (int i = 0; i < 256; i++) {
        if (i % 16 == 0) {
            printf("\n%02x ", i);
        }
        if (i == cpu_ptr->PC) {
            printf("%02x<", cpu_ptr->RAM[i]); // Arrow towards PC
        }else if(i == cpu_ptr->registers[7]) {
            printf("%02x<", cpu_ptr->RAM[i]); // Arrow towards SP
        }
        else {
            printf("%02x ", cpu_ptr->RAM[i]);
        }
    }
    printf("\n");
}

void print_ROM(CPU *cpu_ptr) {
    printf("\nROM\n   ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", i);
    }

    for (int i = 0; i < 256; i++) {
        if (i % 16 == 0) {
            printf("\n%02x ", i);
        }
        printf("%02x ", cpu_ptr->ROM[i]);
    }
    printf("\n");
}