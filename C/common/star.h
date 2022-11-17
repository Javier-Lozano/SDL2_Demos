#if !defined(STAR_H)
#define STAR_H

#include "../common/math.h"
#include "../common/vector.h"
#include "../common/texture.h"

// Structs

typedef struct Star {
	Vector3 position;
	float speed;
	float maxZ;
	//int tail;
} Star;

// Declaracion de Funciones

void StarConstruct(Star* star, float area_width, float area_height, float max_z, int tail_length, float max_speed, float min_speed);
void StarUpdate(Star* star, SDL_Color* color);
void StarRender(SDL_Renderer* renderer, Texture* texture, Star* star, Vector3* origin, SDL_Color* color);

#endif // STAR_H
