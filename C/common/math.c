#include "math.h"

float FloatRNG(float a, float b)
{
    float ratio = (float)rand() / (float)RAND_MAX;
    return (ratio * (b - a)) + a;
}