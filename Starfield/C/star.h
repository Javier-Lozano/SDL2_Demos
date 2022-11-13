#if !defined(STAR_H)
#define STAR_H

#include <SDL2/SDL.h>
#include "vector.h"
#include "texture.h"

// Macros

#define STAR_SPEED_MIN	10
#define STAR_SPEED_MAX	20
#define TAIL	5
#define Z_MAX	1500

#define PI 3.1416

#define FRand(a, b) (((float)rand() / (float)RAND_MAX) * (b - a)) + a

// Ratio es la razon entre la posicion en Z y el punto maximo del Eje Z.
// Basicamente el resultado es un porcentaje ente 0 y 1
#define RATIO(z) (z / Z_MAX);

// Structs

typedef struct Star {
	Vector3 position;
	float speed;
} Star;

// Declaracion de Funciones

void StarConstruct(Star* star, float area_width, float area_height);
void StarUpdate(Star* star, SDL_Color* color);
void StarRender(SDL_Renderer* renderer, Texture* texture, Star* star, Vector3* origin, SDL_Color* color);

#endif // STAR_H
