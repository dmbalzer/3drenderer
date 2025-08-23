#ifndef SDL_INCLUDED
#define SDL_INCLUDED
#include <SDL3/SDL.h>

/* Initialize SDL Window and Renderer. Returns if should quit */
bool sdl_init(int w, int h);
bool sdl_init_buffer_texture(int w, int h);
/* Check events. Returns if should quit */
bool sdl_do_events(void);
void sdl_render(void* buffer);
void sdl_quit(void);

#endif // SDL_INCLUDED