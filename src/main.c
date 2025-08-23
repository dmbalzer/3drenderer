#include <SDL3/SDL.h>

const int window_w = 960;
const int window_h = 640;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
float frametime = 0.0f;
bool quit = false;
const bool* keys = NULL;

Uint32* color_buffer = NULL;
SDL_Texture* color_texture = NULL;

/* Initialize SDL Window and Renderer. Returns if should quit */
bool sdl_init(void) {
	if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ) {
		SDL_Log("%s", SDL_GetError());
		return true;
	}
	
	if ( !SDL_CreateWindowAndRenderer(NULL,  window_w, window_h, 0, &window, &renderer) ) {
		SDL_Log("%s", SDL_GetError());
		return true;
	}

	if ( !SDL_SetRenderVSync(renderer, 1) ) {
		SDL_Log("%s", SDL_GetError());
		return true;;
	}

	keys = SDL_GetKeyboardState(NULL);
	if ( !keys ) {
		SDL_Log("%s", SDL_GetError());
		return true;;
	}

	return false;
}

/* Check events. Returns if should quit */
bool sdl_do_events(void) {
	bool result = false;

	SDL_Event event;
	while ( SDL_PollEvent(&event) ) {
		switch ( event.type ) {
			case SDL_EVENT_QUIT: result = true; break;
			case SDL_EVENT_KEY_DOWN: if ( event.key.key == SDLK_ESCAPE ) result = true; break;
		}
	}

	return result;
}

void sdl_render(void) {
	/* Clear Renderer */
	SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
	/* Update color texture with new values and render */
	SDL_UpdateTexture(color_texture, NULL, color_buffer, 4 * window_w);
	SDL_RenderTexture(renderer, color_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	/* Update frametime */
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = (now - prev) / 1000.0f;
	prev = now;
}

void sdl_quit(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void clear_buffer(void) {
	SDL_memset(color_buffer, 0x00, sizeof(Uint32) * window_w * window_h);
}

void setup(void) {
	quit = sdl_init();
	color_buffer = (Uint32*)SDL_malloc(sizeof(Uint32) * window_w * window_h);
	color_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, window_w, window_h);
}

void check_input(void) {
	quit = sdl_do_events();
}

void update(void) {

}

void draw_grid(void) {
	for ( int x = 0; x < window_w; x += 10 ) {
		for ( int y = 0; y < window_h; y += 10 ) {
			color_buffer[x + y * window_w] = 0x505050FF;
		}
	}
}

void draw_rect(int x, int y, int w, int h, Uint32 c) {
	for ( int _x = x; _x < x + w; _x++ ) {
		for ( int _y = y; _y < y + h; _y++ ) {
			if ( _x < 0 || _x >= window_w ) continue;
			if ( _y < 0 || _y >= window_h ) continue;
			color_buffer[_x + _y * window_w] = c;
		}
	}
}

void draw(void) {
	clear_buffer();
	draw_grid();
	draw_rect(-20,-20,40,40,0xFFFF00FF);
	sdl_render();
}

void cleanup(void) {
	SDL_free(color_buffer);
	SDL_DestroyTexture(color_texture);
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
