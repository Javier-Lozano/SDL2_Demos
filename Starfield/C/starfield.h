#if !defined(STARFIELD_H)
#define STARFIELD_H

#include <SDL2/SDL.h>
#include <time.h>

#include "texture.h"
#include "vector.h"
#include "star.h"

// MACROS 

#define NAME "C Starfield - SDL2"
#define WIDTH	640
#define HEIGHT	480
#define STARS   300

#define COLOR_RATE 0.75

// Estructuras

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} Demo;

// Prototipos

void ChangeColor(float numerator, SDL_Color* color);
//float RandFloat(float min, float max);


#endif // STARFIELD_H
