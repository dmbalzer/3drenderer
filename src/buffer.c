#include "buffer.h"

static int buffer_w = 0;
static int buffer_h = 0;
static Uint32* buffer = NULL;

void buffer_init(int w, int h) {
	buffer = (Uint32*)SDL_malloc(sizeof(Uint32) * w * h);
	buffer_w = w;
	buffer_h = h;
}

void buffer_free(void) {
	SDL_free(buffer);
}

Uint32* buffer_get(void) {
    return buffer;
}

void buffer_clear(Uint32 c) {
	for ( int i = 0; i < buffer_w * buffer_h; i++ ) {
		buffer[i] = c;
	}
}

void buffer_draw_pixel(int x, int y, Uint32 c) {
    if ( x < 0 || x >= buffer_w ) return;
    if ( y < 0 || y >= buffer_h ) return;
    buffer[x + y * buffer_w] = c;
}

void buffer_draw_grid(void) {
	for ( int x = 0; x < buffer_w; x += 10 ) {
		for ( int y = 0; y < buffer_h; y += 10 ) {
			buffer_draw_pixel(x, y, 0xFF505050);
		}
	}
}

void buffer_draw_rect(int x, int y, int w, int h, Uint32 c) {
	for ( int _x = x; _x < x + w; _x++ ) {
		for ( int _y = y; _y < y + h; _y++ ) {
			buffer_draw_pixel(_x, _y, c);
		}
	}
}