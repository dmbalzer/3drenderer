#include <SDL3/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
float frametime = 0.0f;
bool quit = false;
const bool* keys = NULL;

bool sdl_init(void) {
	if ( !SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) ) {
		SDL_Log("%s", SDL_GetError());
		return true;
	}

	if ( !SDL_CreateWindowAndRenderer("3D Renderer", 960, 640, 0, &window, &renderer) ) {
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

void sdl_begin_draw(void) {
	SDL_SetRenderDrawColor(renderer, 0x00,0x00,0x00,0xFF);
	SDL_RenderClear(renderer);
}

void sdl_end_draw(void) {
	SDL_RenderPresent(renderer);
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

int main(void) {
	
	quit = sdl_init();
	
	while ( !quit ) {
		quit = sdl_do_events();
		sdl_begin_draw();
		sdl_end_draw();
	}
	
	sdl_quit();
	return 0;
}
