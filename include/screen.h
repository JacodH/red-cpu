#ifndef SCREEN_H
#define SCREEN_H

#include "cpu.h"

struct Screen {
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    int width;
    int height;
    int scale;
};

struct Screen create_screen(int width, int height, int scale);
void check_input(struct Screen *screen, CPU *cpu_ptr);

void clear_screen(struct Screen *screen);
void draw_vram(struct Screen *screen, uint8_t high, uint8_t low, int xoff, int yoff);

void draw_logo(struct Screen *screen);

void screen_cleanup(struct Screen *screen);
void draw_pixel(struct Screen *screen, int x, int y);

#endif