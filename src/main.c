#include <stdio.h>
#include <stdint.h>

#include "cpu.h"
#include "instructions.h"

int main() {
    printf("Emulator for the RED1 CPU.\n");

    CPU cpu;

    init_cpu(&cpu);

    uint8_t program_test[] = {
        0x01, 0x00, 0x00, 0x00, 
        0xa8, 0x00, 0x01, 0x00, 
        0x06, 0x01, 0x00, 0x00, 
        0x01, 0x00, 0x01, 0x00, 
        0xa8, 0x00, 0x01, 0x00,
        0x06, 0x01, 0x00, 0x00, 
        0xb2, 0x00, 0x00, 0x00,
    };
    int program_size = sizeof(program_test);

    load_program(&cpu, program_test, program_size);

    while(cpu.running) {
        // print_registers(&cpu);
        // print_RAM(&cpu);

        getchar();
        
        uint8_t op = fetch(&cpu, 0);
        uint8_t a = fetch(&cpu, 1);
        uint8_t b = fetch(&cpu, 2);
        uint8_t c = fetch(&cpu, 3);
        
        execute(&cpu, op, a, b, c);
    }
    

    return 0;
}