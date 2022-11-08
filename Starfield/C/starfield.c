/*
 * Programa: Starfield
 * Autor: Javier Lozano
 *
 * Descripcion: Inspirado en un programa clasico.
 *
 */

#include <SDL2/SDL.h>
#include <time.h>

// MACROS 

#define WIDTH 640
#define HEIGHT 480

#define STARS 500
#define SPAWN_RANGE WIDTH * 0.5

#define SPD_ACCEL 0.5
#define SPD_MAX 8
#define SPD_RANGE_MAX (SPD_MAX / SPD_ACCEL) - 1

#define BRIGHT_RATE 5

#define PI 3.1416

// Structs

typedef struct {
	float x;
	float y;
} Vector2;

typedef struct {
	Vector2 position;
	Vector2 speed;
	unsigned int color;
} Star;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} Demo;

// Prototipos

void ConstructStar(Star*);
void UpdateStars(Star*, SDL_Renderer*, Vector2* origin);

float RandFloat(float min, float max);

// Main

int main(int argc, char* args[])
{
	// Asigna Dinamicamente 'Demo' 
	Demo* demo = malloc(sizeof(Demo));
	
	// Inicio rapido de SDL 
	SDL_Init(SDL_INIT_VIDEO);
	demo->window = SDL_CreateWindow("SDL Starfield C", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	demo->renderer = SDL_CreateRenderer(demo->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Semilla aleatorea en base a la "Tiempo" actual 
	srand(time(NULL));

	// Inicializa 'Starfield' 
	Star* starfield = malloc(sizeof(Star) * STARS);
	for (int i = 0; i < STARS; i++)
	{
		ConstructStar(&starfield[i]);
	}

	// Inicializa Origen 
	Vector2 origen = { WIDTH * 0.5, HEIGHT * 0.5 };

	// Bucle Principal 
	int loop = 1;
	while (loop)
	{
		// Maneja el evento de salida 
		while (SDL_PollEvent(&demo->event)) if (demo->event.type == SDL_QUIT) loop = 0;

		// Limpia Pantalla 
		SDL_SetRenderDrawColor(demo->renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(demo->renderer);

		// Dibuja Centro 
		//SDL_SetRenderDrawColor(demo->renderer, 0xFF, 0, 0, 0xFF);
		//SDL_RenderDrawLine(demo->renderer, origen.x, 0, origen.x, HEIGHT);
		//SDL_RenderDrawLine(demo->renderer, 0, origen.y, WIDTH, origen.y);

		// Actualiza Estrellas 
		UpdateStars(starfield, demo->renderer, &origen);

		// Dibuja en Pantalla 
		SDL_RenderPresent(demo->renderer);
	}

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

void UpdateStars(Star* starfield, SDL_Renderer* renderer, Vector2* origen)
{
	for (int i = 0; i < STARS; i++)
	{
		Vector2 p = { starfield[i].position.x + origen->x, starfield[i].position.y + origen->y };
		// Revisa si la estrella estan dentro de la ventana 
		if (p.x < 0 || p.x > WIDTH || p.y < 0 || p.y > HEIGHT)
		{
			starfield[i].position.x = 0;
			starfield[i].position.y = 0;
			starfield[i].color = 0;
		}

		// Mueve las Estrellas 
		starfield[i].position.x += starfield[i].speed.x;
		starfield[i].position.y += starfield[i].speed.y;

		// Color 
		starfield[i].color += BRIGHT_RATE;
		if (starfield[i].color > 0xFF)
		{
			starfield[i].color = 0xFF;
		}

		// Manda a Dibujar las Estrellas 
		SDL_SetRenderDrawColor(renderer, starfield[i].color, starfield[i].color, starfield[i].color, 0xFF);
		SDL_RenderDrawPoint(renderer, p.x, p.y);
	}
}

void ConstructStar(Star* star)
{
	// Obten un Angulo aleatoreo entre 0 y 2PI randianes 
	float angulo = RandFloat(0, PI * 2);

	// Calcula Seno y Coseno 
	float cos = SDL_cosf(angulo);
	float sen = SDL_sinf(angulo);

	// Obten numero aleatoreo 
	float radio = rand() % SPAWN_RANGE;

	// Inicializamos la estrella  
	star->position.x = radio * cos;
	star->position.y = radio * sen;

	// Esta formula determina la velocidad en la que la estrella viaja:
	// velocidad = (random() * -inclinacion) + elevacion
	float random = RandFloat(0, SPD_RANGE_MAX);
	float velocidad = (random * -SPD_ACCEL) + SPD_MAX;
	
	star->speed.x = cos * velocidad;
	star->speed.y = sen * velocidad;

	// Color 
	star->color = 0x55;
	//printf("Color: 0x%d\n", star->color);
}

float RandFloat(float min, float max)
{
	float ratio = (float)rand() / (float)RAND_MAX;
	return (ratio * (max - min)) + min;
}
