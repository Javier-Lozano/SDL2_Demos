#ifndef BOX_COLLISION
#define BOX_COLLISION

#include "../common/demo.h"

/* Macros */

#define NAME "SDL Box Collision [C]"
#define WIDTH 640
#define HEIGHT 480
#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_FLAGS SDL_WINDOW_SHOWN
#define RENDER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

#define BOX_WIDTH 64
#define BOX_HEIGHT 64

#define SPEED 5

/* Estructuras */

typedef struct CollisionBox {
	SDL_Rect rect;
	SDL_Color color;
} CollisionBox;

/**/

void RenderCollisionBox(Demo* demo, CollisionBox box);

#endif // BOX_COLLISION
