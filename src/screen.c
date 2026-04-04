#include <SDL2/SDL.h>
#include "screen.h"
#include "cpu.h"

struct Screen create_screen(int width, int height, int scale) {

    // Init screen struct (defined in screen.h)
    struct Screen screen = {
        .window = NULL,
        .renderer = NULL,
        .width = width, 
        .height = height,
        .scale = scale,
    };
    
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 1) {printf("SDL ERROR"); exit(1); };

    // Create window
    screen.window = SDL_CreateWindow("Red 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.width*screen.scale, screen.height*screen.scale, 0);
    if (screen.window == NULL) { printf("SDL ERROR on loading window"); exit(1);}

    // Create renderer
    screen.renderer = SDL_CreateRenderer(screen.window, -1, 0);
    if (screen.renderer == NULL) { printf("SDL ERROR on creating renderer"); exit(1);}

    return screen;
}
void check_input(struct Screen *screen, CPU *cpu_ptr) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            screen_cleanup(screen);
        }
        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;
            // printf("key pressed: 0x%02x\n", (uint8_t)key);
            if (32 <= key && key <= 126) {
                cpu_ptr->RAM[0xE6] = (uint8_t)key;
            }
        }
        if (key == SDLK_UP) {cpu_ptr->RAM[0xE6] = 0x80;}
        if (key == SDLK_DOWN) {cpu_ptr->RAM[0xE6] = 0x81;}
        if (key == SDLK_LEFT) {cpu_ptr->RAM[0xE6] = 0x82;}
        if (key == SDLK_RIGHT) {cpu_ptr->RAM[0xE6] = 0x83;}
        if (key == SDLK_RETURN) {cpu_ptr->RAM[0xE6] = 0x0D;}
        if (key == SDLK_BACKSPACE) {cpu_ptr->RAM[0xE6] = 0x08;}
    }

}

void clear_screen(struct Screen *screen) {
    // Set bg to black
    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 255);
    SDL_RenderClear(screen->renderer);
}

void draw_vram(struct Screen *screen, uint8_t high, uint8_t low, int xoff, int yoff) {

    // Set color to red
    SDL_SetRenderDrawColor(screen->renderer, 210, 1, 33, 255);
    
    // Draw vram
    uint16_t full = ((uint16_t)high << 8) | low; 
    int y = -1; 
    for (int i = 0; i < 16; i++) {
        if (i % 4 == 0) {y++;}
        if (full & 0b1000000000000000) {
            // Draw pixel
            // printf("(%d, %d)\n", i%8, y);
            draw_pixel(screen, (i%4) + xoff, y + yoff);
        }else {
            // Clear pixel
        }
        full = full << 1;
    }
}

void draw_logo(struct Screen *screen) {
    // Set color to red
    SDL_SetRenderDrawColor(screen->renderer, 210, 1, 33, 255);

    // Draw R
    draw_pixel(screen, 1, 0);
    draw_pixel(screen, 2, 0);

    draw_pixel(screen, 1, 1);
    draw_pixel(screen, 3, 1);

    draw_pixel(screen, 1, 2);
    draw_pixel(screen, 2, 2);

    draw_pixel(screen, 1, 3);
    draw_pixel(screen, 3, 3);
    
    // Draw E
    draw_pixel(screen, 4+1, 0);
    draw_pixel(screen, 4+2, 0);
    draw_pixel(screen, 4+3, 0);

    draw_pixel(screen, 4+1, 1);

    draw_pixel(screen, 4+1, 2);
    draw_pixel(screen, 4+2, 2);

    draw_pixel(screen, 4+1, 3);
    draw_pixel(screen, 4+2, 3);
    draw_pixel(screen, 4+3, 3);

    // Draw D
    draw_pixel(screen, 8+1, 0);
    draw_pixel(screen, 8+2, 0);

    draw_pixel(screen, 8+1, 1);
    draw_pixel(screen, 8+3, 1);

    draw_pixel(screen, 8+1, 2);
    draw_pixel(screen, 8+3, 2);

    draw_pixel(screen, 8+1, 3);
    draw_pixel(screen, 8+2, 3);
}

void screen_cleanup(struct Screen *screen) {
    SDL_DestroyRenderer(screen->renderer);
    SDL_DestroyWindow(screen->window);
    SDL_Quit();
    exit(0);
}

void draw_pixel(struct Screen *screen, int x, int y) {
    SDL_Rect myRect = {x*screen->scale, y*screen->scale, screen->scale, screen->scale}; // x, y, width, height

    // Draw a filled rectangle
    SDL_RenderFillRect(screen->renderer, &myRect);
}
