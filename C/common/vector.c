#include "vector.h"

// Vector2

Vector2 Vector2Add(Vector2 a, Vector2 b)
{
    Vector2 v = { a.x + b.x, a.y + b.y };
    return v;
}

Vector2 Vector2Mult(Vector2 a, float n)
{
    Vector2 v = { a.x * n, a.y * n };
    return v;
}

Vector2 Vec3ToVec2(Vector3 v3)
{
    Vector2 v2 = { v3.x, v3.y };
    return v2;
}

// Vector3

Vector3 Vector3Add(Vector3 a, Vector3 b)
{
    Vector3 v = { a.x + b.x, a.y + b.y, a.z + b.z };
    return v;
}

Vector3 Vector3Mult(Vector3 a, float n)
{
    Vector3 v = {a.x * n, a.y * n, a.z * n};
    return v;
}

Vector3 Vec2ToVec3(Vector2 v2)
{
    Vector3 v3 = { v2.x, v2.y, 0 };
    return v3;
}