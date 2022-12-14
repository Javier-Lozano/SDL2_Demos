#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <SDL2/SDL_render.h>
#include "vector.h"

// Macros

#define TEXTURE_WIDTH 8
#define TEXTURE_HEIGHT 8

// Estructuras

typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    Vector2 scaling;
} Texture;

// Declaracion de Funciones

void TextureLoad(SDL_Renderer* renderer, const char* path, Texture* texture );
void TextureSetScale(Texture* texture, float x, float y);
void TextureRender(SDL_Renderer* renderer, Texture* texture, int x, int y, int center, SDL_Color* color);
void TextureDestroy(Texture* Texture);

#endif // TEXTURE_H
