#include "sdl.h"

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Texture* buffer_texture = NULL;
static float frametime = 0.0f;

/* Initialize SDL Window and Renderer. Returns if should quit */
bool sdl_init(int w, int h) {
	if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ) {
		SDL_Log("%s", SDL_GetError());
		return true;
	}
	
	if ( !SDL_CreateWindowAndRenderer(NULL,  w, h, 0, &window, &renderer) ) {
		SDL_Log("%s", SDL_GetError());
		return true;
	}

	if ( !SDL_SetRenderVSync(renderer, 1) ) {
		SDL_Log("%s", SDL_GetError());
		return true;
	}
	
	return false;
}

bool sdl_init_buffer_texture(int w, int h) {
	buffer_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		w,
		h);
	if ( buffer_texture == NULL ) return true;
	return false;
}

/* Check events. Returns if should quit */
bool sdl_do_events(void) {
	SDL_Event event;
	bool quit = 0;
	while ( SDL_PollEvent(&event) ) {
		switch ( event.type ) {
			case SDL_EVENT_QUIT: quit = true; break;
		}
	}

	return quit;
}

void sdl_render(void* buffer) {
	/* Clear Renderer */
	SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
	
	/* Update color texture with new values and render */
	SDL_UpdateTexture(buffer_texture, NULL, buffer, sizeof(Uint32) * buffer_texture->w);
	SDL_RenderTexture(renderer, buffer_texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	
	/* Update frametime */
	static Uint64 prev = 0;
	const Uint64 now = SDL_GetTicks();
	frametime = (now - prev) / 1000.0f;
	prev = now;
}

void sdl_quit(void) {
	SDL_DestroyTexture(buffer_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
