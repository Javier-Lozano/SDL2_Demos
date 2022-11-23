#ifndef DEMO_H
#define DEMO_H

#include <SDL2/SDL.h>

/* Estructuras */

/**
 * \brief Contexto para la ejecucion de un Demo.
 * 
 * Todos los Demos que utilizan SDL requieren una Ventana, un Renderer y
 * una estructura (Union) para manejar Eventos.
 */
typedef struct Demo {
	SDL_Window* window;		/* Ventana */
	SDL_Renderer* renderer;	/* Renderer */
	SDL_Event event;		/* Eventos*/
} Demo;

/* Declaracion de funciones */

/**
 * Inicializa SDL.
 * 
 * \param demo Contexto del Demo.
 * \param name Nombre del Demo.
 * \param width Ancho de la ventana.
 * \param height Altura de la ventana.
 * \param sdl_flags 'Flags' para la inicializacion de SDL.
 * \param window_flags 'Flags' para la inicializacion de la ventana.
 * \param render_flags 'Flags' para la inicializacion del 'renderer'.
 * 
 * \return Devuelve 1 si la operacion fue exitosa. Devuelve 0 en caso de error.
 */
int StartSDL(Demo* demo, const char* name, int width, int height, Uint32 sdl_flags, Uint32 window_flags, Uint32 renderer_flags);

/**
 * Termina SDL.
 * 
 * \param demo Contexto del Demo.
 */
void CloseSDL(Demo* demo);

#endif // DEMO_H
