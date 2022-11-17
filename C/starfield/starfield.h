#if !defined(STARFIELD_H)
#define STARFIELD_H

#include <SDL2/SDL.h>
#include <time.h>

#include "../common/vector.h"
#include "../common/texture.h"
#include "../common/star.h"

// MACROS 

#define NAME "SDL2 Starfield [C]"
#define WIDTH	640
#define HEIGHT	480

#define STARS   300
#define COLOR_RATE 0.75

#define STAR_SPEED_MIN	10
#define STAR_SPEED_MAX	20
#define TAIL	5
#define Z_MAX	1500

// Estructuras

typedef struct Demo {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} Demo;

// Declaracion de Funciones

void ChangeColor(float numerator, SDL_Color* color);

#endif // STARFIELD_H
