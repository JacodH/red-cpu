#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#include "cpu.h"
#include "instructions.h"
#include "screen.h"

#undef main
int main() {
    printf("Emulator for the red-CPU.\n");

    // Create CPU struct
    CPU cpu;

    // Create screen that is 12x4 pixels in size
    struct Screen screen = create_screen(3*4, 1*4, 50);

    init_cpu(&cpu);

    uint8_t program_test[] = {
        0x01, 0x00, 0x25, 0x00,
        0x01, 0x01, 0xe0, 0x00,
        0x05, 0x00, 0x01, 0x00,
        0x01, 0x00, 0x75, 0x00,
        0x05, 0x00, 0x01, 0x01,
        0x01, 0x00, 0x46, 0x00,
        0x05, 0x00, 0x01, 0x02,
        0x01, 0x00, 0x57, 0x00,
        0x05, 0x00, 0x01, 0x03,
        0x01, 0x00, 0x74, 0x00,
        0x05, 0x00, 0x01, 0x04,
        0x01, 0x00, 0x47, 0x00,
        0x05, 0x00, 0x01, 0x05,
        0xb2, 0x00, 0x00, 0x00,
    };
    int program_size = sizeof(program_test);

    load_program(&cpu, program_test, program_size);

    while(cpu.running) {

        // Update CPU
        print_registers(&cpu);
        print_RAM(&cpu);

        uint8_t op = fetch(&cpu, 0);
        uint8_t a = fetch(&cpu, 1);
        uint8_t b = fetch(&cpu, 2);
        uint8_t c = fetch(&cpu, 3);
        
        execute(&cpu, op, a, b, c);

        // Render VRAM

        // Checks to see if the user tried to close the window 
        check_close(&screen);

        clear_screen(&screen);

        draw_vram(&screen, cpu.RAM[0xe0], cpu.RAM[0xe1], 0, 0);
        draw_vram(&screen, cpu.RAM[0xe2], cpu.RAM[0xe3], 4, 0);
        draw_vram(&screen, cpu.RAM[0xe4], cpu.RAM[0xe5], 8, 0);
        // draw_logo(&screen);
        
        // Update buffer
        SDL_RenderPresent(screen.renderer);
        
        SDL_Delay(10);
    }
    
    printf("\nCLOSING\n");

    SDL_Delay(5000);

    return 0;
}