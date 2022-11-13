#include "vector.h"

Vector3 Vector3Add(Vector3 v1, Vector3 v2)
{
    Vector3 v = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
    return v;
}

Vector3 Vector3Mult(Vector3 v1, float n)
{
    Vector3 v = {v1.x * n, v1.y * n, v1.z * n};
    return v;
}