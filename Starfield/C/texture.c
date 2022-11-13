#include "texture.h"

// Carga una superficie desde una imagen.
void TextureLoad(SDL_Renderer* renderer, const char* path, Texture* texture )
{
    // Crea una superficie apartir de una imagen
    SDL_Surface* surface = SDL_LoadBMP(path);
    
    // Si no se encontró la imagen crea un superficie
    if (!surface)
    {
        // Imprime el error
        printf("SDL Error: %s\n", SDL_GetError());

        // Crea una superficie en blanco.
        surface = SDL_CreateRGBSurfaceWithFormat(0, 32, 32, 32, SDL_PIXELFORMAT_RGBA32);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0xFF, 0xFF, 0xFF, 0xFF));
    }

    // Crea una textura a partir de la superficie
    texture->texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Almacena sus Dimensiones
    texture->rect.x = 0;
    texture->rect.w = 0;
    texture->rect.w = surface->w;
    texture->rect.h = surface->h;

    // Inicializa Scaling en 1
    texture->scaling.x = 1;
    texture->scaling.y = 1;

    // Activa Modulacion Alpha
    SDL_SetTextureBlendMode(texture->texture, SDL_BLENDMODE_BLEND);

    // Libera recursos
    SDL_FreeSurface(surface);
}

// Ajusta la escala de la textura a un porcentaje en el Eje X y Y
void TextureSetScale(Texture* texture, float x, float y)
{
    texture->scaling.x = x;
    texture->scaling.y = y;
}

// Rederiza la Textura en un determinado punto, con determinado colo y transparencia
void TextureRender(SDL_Renderer* renderer, Texture* texture, int x, int y, int center, SDL_Color* color)
{
    // Prepara dimensiones y aplica el escalado
    SDL_Rect r = {x, y, texture->rect.w * texture->scaling.x, texture->rect.h * texture->scaling.y};

    // Centra la textura
    if (center)
    {
        r.x -= (r.w / 2);
        r.y -= (r.h / 2);
    }

    // Aplica Modulacion de Color
    SDL_SetTextureColorMod(texture->texture, color->r, color->g, color->b);
    // Aplica Modulacion de Canal Alpha
    SDL_SetTextureAlphaMod(texture->texture, color->a);

    // Renderiza la Textura
    SDL_RenderCopy(renderer, texture->texture, NULL, &r);
}

// Destroye la Textura SDL
void TextureDestroy(Texture* texture)
{
    SDL_DestroyTexture(texture->texture);
}
