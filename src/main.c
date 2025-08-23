#include "sdl.h"
#include "buffer.h"

const int window_w = 960;
const int window_h = 640;
int quit = 0;

const bool* keys = NULL;

void setup(void) {
	quit = sdl_init(window_w, window_h);
	keys = SDL_GetKeyboardState(NULL);
	buffer_init(window_w, window_h);
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
	sdl_render(buffer_get());
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
