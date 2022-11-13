/*
 * Programa: Starfield
 * Autor: Javier Lozano
 *
 * Descripcion:
 * Las 'estrellas' son particulas representadas en un espacio 3D y su posicion
 * esta representada por coordenadas X, Y y Z (Vector3).
 *
 * Se delimita un rango en el Eje Z, entre 0, que es el origen, y Z_MAX.
 * Las particulas se muven unicamente en el Eje Z, 'adelante' o 'reversa', y
 * dependiendo de su posicion en el Eje afectara como se dibuja en el plano.
 * 
 * Si las particulas estan alejadas del origen estas apareceran mas cerca del
 * centro, en el caso contrario apareceran mas disperzas. 
 *
 * Ese efecto se logra Multiplicando las coordenadas X y Y por: 1 - (Z / Z_MAX)
 *
 * El canal Alpha es proporcional a la posicion en Eje Z, si esta mas alejado
 * del origen la particula tendra una mayor transparencia.
 *
 * Los colores se ciclan interpolandose Entre Rojo a Verde, de Verde a Azul y
 * de Azul a Rojo.
 */

#include "starfield.h"

// Main

int main(int argc, char* args[])
{
	// Asigna Dinamicamente 'Demo' 
	Demo* demo = malloc(sizeof(Demo));
	
	// Inicio rapido de SDL 
	SDL_Init(SDL_INIT_VIDEO);
	demo->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	demo->renderer = SDL_CreateRenderer(demo->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Activa el Alpha Blending
	SDL_SetRenderDrawBlendMode(demo->renderer, SDL_BLENDMODE_BLEND);

	// Textura: Debería haber 3 archivos .bmp adjuntos al codigo fuente. Puedes probar con cualquiera
	Texture t;
	TextureLoad(demo->renderer, "Star_Dot.bmp", &t);

	// Semilla aleatorea en base a la "Tiempo" actual 
	srand(time(NULL));

	// Inicializa Origen 
	Vector3 origen = { WIDTH * 0.5, HEIGHT * 0.5, 0 };

	// Inicializa 'Starfield' 
	Star* starfield = malloc(sizeof(Star) * STARS);
	for (int i = 0; i < STARS; i++)
	{
		StarConstruct(&starfield[i], WIDTH, HEIGHT);
	}

	// Color
	SDL_Color color;

	// Numerador que indica cuando debe cambiar el color
	float num = 0;

	// Bucle Principal 
	int loop = 1;
	while (loop)
	{
		// Maneja el evento de salida 
		while (SDL_PollEvent(&demo->event)) if (demo->event.type == SDL_QUIT) loop = 0;

		// Limpia Pantalla 
		SDL_SetRenderDrawColor(demo->renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(demo->renderer);

		// Aumenta numerador
		num += COLOR_RATE;
		// Cambia el color
		ChangeColor(num, &color);

		// Actualiza Estrellas 
		for (int i = 0; i < STARS; i++)
		{
			StarUpdate(&starfield[i], &color);
			StarRender(demo->renderer, &t, &starfield[i], &origen, &color);
		}

		// Dibuja en Pantalla 
		SDL_RenderPresent(demo->renderer);
	}

	TextureDestroy(&t);

	// Terminar SDL
	SDL_DestroyRenderer(demo->renderer);
	SDL_DestroyWindow(demo->window);
	SDL_Quit();

	// Libera 'Starfield' 
	free(starfield);

	// Liberar 'Demo' 
	free(demo);

	return 0;
}

// Definicion 

void ChangeColor(float numerator, SDL_Color* color)
{
	int n = (int)numerator % 100;
	int section = (int)numerator % 300;

	if (section < 100) // Transiciona de Rojo a Verde
	{
		color->r = 255 - (255 * n) / 100;
		color->g = (255 * n) / 100;
		color->b = 0;
	}
	else if (section < 200) // Transiciona de Verde a Azul
	{
		color->r = 0;
		color->g = 255 - (255 * n) / 100;
		color->b = (255 * n) / 100;
	}
	else if (section < 300) // Transiciona de Azul a Rojo
	{
		color->r = (255 * n) / 100;
		color->g = 0;
		color->b = 255 - (255 * n) / 100;
	}
}

/*
float RandFloat(float min, float max)
{
	float ratio = (float)rand() / (float)RAND_MAX;
	return (ratio * (max - min)) + min;
}
*/