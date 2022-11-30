#if !defined(WAVES_H)
#define WAVES_H

#include "../common/demo.h"
#include "../common/math.h"
#include "../common/vector.h"
#include "../common/texture.h"

/* Macros */

#define NAME "SDL2 Waves [C]"
#define WIDTH 800
#define HEIGHT 600
#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_FLAGS SDL_WINDOW_SHOWN
#define RENDER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

#define COLUMNS 20
#define ROWS 15

#define DEGREE_RATE 0.01
#define FREQUENCY_RATE 0.25
#define AMPLITUDE_RATE 0.25

/* Declaracion de Funciones */

//float SineWave(float angle, float frequency, float amplitude);
//float Sawtooth(float angle, float frequency, float amplitude, int iterations);
//float MusicWave();

#endif // WAVES_H
