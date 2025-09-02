#include "sdl.h"
#include "buffer.h"
#include "vector.h"

const int window_w = 960;
const int window_h = 640;
bool quit = 0;

const bool* keys = NULL;

Vector3_t cube[9 * 9 * 9] = { 0 };

void setup(void) {
	quit = sdl_init(window_w, window_h);
	quit = sdl_init_buffer_texture(window_w, window_h);
	buffer_init(window_w, window_h);
	keys = SDL_GetKeyboardState(NULL);

	for ( int x = 0; x < 9; x++ ) {
		for ( int y = 0; y < 9; y++ ) {
			for ( int z = 0; z < 9; z++ ) {

			}
		}
	}

}

void check_input(void) {
	quit = sdl_do_events();
	if ( keys[SDL_SCANCODE_ESCAPE] ) quit = true;
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
