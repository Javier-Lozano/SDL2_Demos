#if !defined(VECTOR3_H)
#define VECTOR3_H

#include <SDL2/SDL_rect.h>

typedef SDL_FPoint Vector2;

typedef struct {
	float x;
	float y;
	float z;
} Vector3;

Vector3 Vector3Add(Vector3 v1, Vector3 v2);
Vector3 Vector3Mult(Vector3 v1, float n);

//Vector2 ToVector2(Vector3 v);

#endif // VECTOR3_H
