/**
 * Programa: Waves
 * Autor: Javier Lozano
 * 
 * Descripcion:
 * Animacion de unos puntos moviendose formando una especie de 'Onda'
 * 
 * 
 */

#include "waves.h"

int main(int argc, char* args[])
{
    // Asigna 'Demo' 
	Demo* demo = malloc(sizeof(Demo));

    // Inicia SDL
    int run = StartSDL(demo);
    if (run)
    {
        // Carga Textura de esfera
        Texture texSphere;
        TextureLoad(demo->renderer, "Sphere.bmp", &texSphere);

        // Inicializa 'Puntos'
        Vector2* dots = malloc(sizeof(Vector2) * DOTS * ROWS);

        // Espaciado entre olas
        float y_spacing = 20;

        // Angulo
        float angle = 0;

        // Radio
        float radio = 30;

        // Origen
        Vector2 origin = { WIDTH / DOTS * 0.5, HEIGHT / ROWS};

        // Bucle principal
        int loop = 1;
        while (loop)
        {
            while (SDL_PollEvent(&demo->event)) if (demo->event.type == SDL_QUIT) loop = 0;

            // Limpia pantalla
            SDL_SetRenderDrawColor(demo->renderer, 0, 0x10, 0x43, 0xFF);
            SDL_RenderClear(demo->renderer);

            // Actualiza posicion de los 'Puntos'
            angle += 0.1;
            SDL_Color c = { 0x11, 0x65, 0xD1, 0xFF };

            for (int i = 0; i < DOTS * ROWS; i++)
            {
                int col = i % DOTS;
                // Posiciona en Eje X
                dots[i].x = col * (WIDTH / DOTS);

                int row = i / DOTS;
                float shift = (PI / 8) * row;
                // Posiciona en Eje Y
                float fract = (2 * PI) / DOTS;
                int p = i / DOTS;
                dots[i].y = (SDL_sinf(angle + shift + (i * fract)) * radio) + (p * 40);

                // Mueve el 'Punto' al origen
                Vector2 v = Vector2Add(dots[i], origin);

                // Escala dependiendo la 'Fila';
                float s = (float)row / ROWS;

                // Renderiza
                TextureRender(demo->renderer, &texSphere, v.x, v.y, 1, &c);
            }
            
            // Renderiza
            SDL_RenderPresent(demo->renderer);
        }
        

        // Libera 'Puntos'
        free(dots);

        // Destruye Textura de esfera
        TextureDestroy(&texSphere);

    }

    // Termina SDL
    CloseSDL(demo);

    // Libera 'Demo'
    free(demo);

    return 0;
}

int StartSDL(Demo* demo)
{
    int success = 1;

    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        success = 0;
    }

    // Crea ventana y revisa si no es NULL
	demo->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (demo->window == NULL)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        success = 0;
    }

    // Crea renderer y revisa si no es NULL
	demo->renderer = SDL_CreateRenderer(demo->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (demo->renderer == NULL)
    {
        printf("SDL_Error: %s\n", SDL_GetError());
        success = 0;
    }

    return success;

}

void CloseSDL(Demo* demo)
{
    // Termina SDL
    SDL_DestroyWindow(demo->window);
    SDL_DestroyRenderer(demo->renderer);
    SDL_Quit();
}