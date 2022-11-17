#if !defined(VECTOR3_H)
#define VECTOR3_H

// Estructuras

typedef struct Vector2 {
	float x;
	float y;
} Vector2;

typedef struct Vector3 {
	float x;
	float y;
	float z;
} Vector3;

// Declaracion de Funciones

// Vector2

Vector2 Vector2Add(Vector2 a, Vector2 b);
Vector2 Vector2Mult(Vector2 a, float n);
Vector2 Vec3ToVec2(Vector3 v3);

// Vector3

Vector3 Vector3Add(Vector3 a, Vector3 b);
Vector3 Vector3Mult(Vector3 a, float n);
Vector3 Vec2ToVec3(Vector2 v2);


#endif // VECTOR3_H
