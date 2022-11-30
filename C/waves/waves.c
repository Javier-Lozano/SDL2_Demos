/**
 * Programa: Waves
 * Autor: Javier Lozano
 */

#include "waves.h"

int main(int argc, char* args[])
{
    // Variables
    Demo demo;
    int run;
    int loop = 1;

    Texture texture;
    SDL_Color textureColor = { 0x11, 0x65, 0xD1, 0xFF };

    float deg = 0;
    float frequency = 31;
    float amplitude = 15;

    // Inicia SDL
    run = StartSDL(&demo, NAME, WIDTH, HEIGHT, SDL_FLAGS, WINDOW_FLAGS, RENDER_FLAGS);
    if (run)
    {
        // Inicializa la textura
        TextureLoad(demo.renderer, "resources/Sphere.bmp", &texture);

        // Bucle Principal
        while (loop)
        {
            // Eventos
            while (SDL_PollEvent(&demo.event))
            {
                if (demo.event.type == SDL_QUIT) loop = 0;
                if (demo.event.type == SDL_KEYDOWN)
                {
                    SDL_Keycode key = demo.event.key.keysym.sym;
                    if (key == SDLK_UP) frequency += FREQUENCY_RATE;
                    if (key == SDLK_DOWN) frequency -= FREQUENCY_RATE;
                    if (key == SDLK_RIGHT) amplitude += AMPLITUDE_RATE;
                    if (key == SDLK_LEFT) amplitude -= AMPLITUDE_RATE;
                }
            }

            // Aumenta los grados
            deg += DEGREE_RATE;

            // Limpia Pantalla
            SDL_SetRenderDrawColor(demo.renderer, 0, 0, 0, 0xFF);
            SDL_RenderClear(demo.renderer);

            // Calcula los Puntos
            for (int i = 0; i < ROWS * COLUMNS; i++)
            {
                // Obten el angulo en Radianes
                float radians = deg + (i * DEGREE_RATE);
                // Calcula el seno del angulo
                float sin = SDL_sinf(radians * frequency) * amplitude;

                // Posiciona
                int col = i % COLUMNS;
                int row = i / COLUMNS;
                int section_x = (WIDTH / COLUMNS);
                int section_y = (HEIGHT / ROWS);
                Vector2 position = {
                    (col * section_x) + (section_x / 2),
                    (row * section_y) + (section_y / 2) + sin
                };

                TextureRender(demo.renderer, &texture, position.x, position.y, 1, &textureColor);
            }
            

            // Renderiza
            SDL_RenderPresent(demo.renderer);
            
        }

        // Destruye Textura
        TextureDestroy(&texture);
    }

    // Termina SDL
    CloseSDL(&demo);

    return 0;
}