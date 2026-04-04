#ifndef CPU_H // Check to see if this header has already been loaded
#define CPU_H

#include <stdio.h>
#include <stdint.h>

extern char register_ids[9];

typedef struct {
    uint8_t registers[8];   // The 8 register
    uint8_t RAM[256];       // The 256 bytes of ram
    uint8_t ROM[256];       // The 256 bytes of ROM
    uint8_t PC;             // Program counter
    int running;
} CPU;

void init_cpu(CPU *cpu_ptr);                                  // Takes in a pointer to a CPU struct, clears all registers and memory

void load_program(CPU *cpu_ptr, uint8_t program[], int size); // Function to load a program into memory
void load_ROM(CPU *cpu_ptr, uint8_t rom[], int size); // Function to load ROM into CPU struct
uint8_t fetch(CPU *cpu_ptr, int offset);                      // Returns the instruction at PC + an offset

// Debuggers 
void print_registers(CPU *cpu_ptr);
void print_RAM(CPU *cpu_ptr);
void print_ROM(CPU *cpu_ptr);

#endif