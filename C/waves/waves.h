#if !defined(WAVES_H)
#define WAVES_H

#include <SDL2/SDL.h>

#include "../common/vector.h"
#include "../common/texture.h"

// MACROS

#define NAME "SDL2 Dot.Waves [C]"
#define WIDTH	640
#define HEIGHT	480

#define DOTS	10
#define ROWS 	10
#define PI	3.1416

// Estructuras

typedef struct Demo {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} Demo;

// Declaracion de Funciones

int StartSDL(Demo* demo);
void CloseSDL(Demo* demo);

#endif // WAVES_H
