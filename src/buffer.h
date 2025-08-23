#ifndef BUFFER_INCLUDED
#define BUFFER_INCLUDED

#include <SDL3/SDL.h>

void buffer_init(int w, int h);
void buffer_free(void);
Uint32* buffer_get(void);
void buffer_clear(Uint32 c);
void buffer_draw_pixel(int x, int y, Uint32 c);
void buffer_draw_grid(void);
void buffer_draw_rect(int x, int y, int w, int h, Uint32 c);

#endif // BUFFER_INCLUDED