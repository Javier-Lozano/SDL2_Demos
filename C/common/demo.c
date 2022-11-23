#include "demo.h"

int StartSDL(Demo* demo, const char* name, int width, int height, Uint32 sdl_flags, Uint32 window_flags, Uint32 renderer_flags)
{
	// Variables
	int	success = 1;

	// Inicializa SDL
	if (SDL_Init(sdl_flags) < 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		success = 0;
	}

	// Inicializa ventana
	demo->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
	if (demo->window == NULL)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		success = 0;
	}

	// Inicializa renderer
	demo->renderer = SDL_CreateRenderer(demo->window, -1, renderer_flags);
	if (demo->renderer == NULL)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		success = 0;
	}

	// Retorna bandera
	return success;
}

void CloseSDL(Demo* demo)
{
	// Destruye Ventana
	SDL_DestroyWindow(demo->window);
	// Destruye Renderer
	SDL_DestroyRenderer(demo->renderer);
	// Termina SDL
	SDL_Quit();
}
