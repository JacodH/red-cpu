
#ifndef INSTRUCTIONS_H // Check to see if this header has already been loaded
#define INSTRUCTIONS_H

int execute(CPU *cpu_ptr, uint8_t op, uint8_t a, uint8_t b, uint8_t c);

void print_program(uint8_t program[], int program_size);

#endif