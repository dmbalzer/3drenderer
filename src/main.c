#include <SDL3/SDL.h>
#include "sdl.h"

const int window_w = 960;
const int window_h = 640;
int quit = 0;

const bool* keys = NULL;

Uint32* buffer = NULL;

void buffer_init(void) {
	buffer = (Uint32*)SDL_malloc(sizeof(Uint32) * window_w * window_h);
}

void buffer_free(void) {
	SDL_free(buffer);
}

void buffer_clear(Uint32 c) {
	for ( int i = 0; i < window_w * window_h; i++ ) {
		buffer[i] = c;
	}
}

void buffer_draw_grid(void) {
	for ( int x = 0; x < window_w; x += 10 ) {
		for ( int y = 0; y < window_h; y += 10 ) {
			buffer[x + y * window_w] = 0xFF505050;
		}
	}
}

void buffer_draw_rect(int x, int y, int w, int h, Uint32 c) {
	for ( int _x = x; _x < x + w; _x++ ) {
		for ( int _y = y; _y < y + h; _y++ ) {
			if ( _x < 0 || _x >= window_w ) continue;
			if ( _y < 0 || _y >= window_h ) continue;
			buffer[_x + _y * window_w] = c;
		}
	}
}

void setup(void) {
	quit = sdl_init(window_w, window_h);
	keys = SDL_GetKeyboardState(NULL);
	buffer_init();
}

void check_input(void) {
	quit = sdl_do_events();
	if ( keys[SDL_SCANCODE_ESCAPE] ) quit = 1;
}

void update(void) {

}

void draw(void) {
	buffer_clear(0xFF000000);
	buffer_draw_grid();
	buffer_draw_rect(20,20,80,80,0xFFFFFF00);
	sdl_render(buffer);
}

void cleanup(void) {
	buffer_free();
	sdl_quit();
}

int main(void) {
	setup();	
	while ( !quit ) {
		check_input();
		update();
		draw();
	}
	cleanup();	
	return 0;
}
