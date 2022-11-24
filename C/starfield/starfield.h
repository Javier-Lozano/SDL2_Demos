#if !defined(STARFIELD_H)
#define STARFIELD_H

#include <time.h>

#include "../common/demo.h"
#include "../common/vector.h"
#include "../common/texture.h"
#include "../common/star.h"

/* Macros */

#define NAME "SDL2 Starfield [C]"
#define WIDTH	640
#define HEIGHT	480
#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_FLAGS SDL_WINDOW_SHOWN
#define RENDER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

#define STARS   300
#define STAR_SPEED	50
#define Z_MAX	4000

#define STARFIELD_TIME_MS 7000
#define TRANSITION_TIME_MS 2000

#endif // STARFIELD_H
