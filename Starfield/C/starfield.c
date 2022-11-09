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
#define STAR_SPEED_MIN 1
#define STAR_SPEED_MAX 7
#define TRAIL 5

#define ALPHA_MIN 0
#define ALPHA_RATE 5

#define PI 3.1416

// Structs

typedef struct {
	float x;
	float y;
} Vector2;

typedef struct {
	Vector2 position;
	Vector2 trail[TRAIL];
	Vector2 angle;
	float speed;
	SDL_Color color;
} Star;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} Demo;

// Prototipos

void ConstructStar(Star*);
void UpdateStar(Star*, SDL_Renderer*, Vector2* origin);

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

	// Activa el Alpha Blending
	SDL_SetRenderDrawBlendMode(demo->renderer, SDL_BLENDMODE_BLEND);

	// Semilla aleatorea en base a la "Tiempo" actual 
	srand(time(NULL));

	// Inicializa 'Starfield' 
	Star* starfield = malloc(sizeof(Star) * STARS);
	for (int i = 0; i < STARS; i++)
	{
		//printf("Min Vel: %d Max Vel: %d Actual: %f\n", STAR_SPEED_MIN, STAR_SPEED_MAX, velocidad);
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
		for (int i = 0; i < STARS; i++)
		{
			UpdateStar(&starfield[i], demo->renderer, &origen);
		}

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

void ConstructStar(Star* star)
{
	// Obten un Angulo aleatoreo entre 0 y 2PI randianes 
	float angulo = RandFloat(0, PI * 2);

	// Calcula Seno y Coseno 
 	star->angle.x = SDL_cosf(angulo);
	star->angle.y = SDL_sinf(angulo);

	// Obten la Velocidad aleatorea entre STAR_SPEED_MIN y STAR_SPEED_MAX
	star->speed = RandFloat((float)STAR_SPEED_MIN, (float)STAR_SPEED_MAX);
	
	// Inicializamos la posicion de la estrella 
	star->position.x = 0;
	star->position.y = 0;

	// Inicializamos la cola (trail)
	for (int i = 0; i < TRAIL; i++)
	{
		star->trail[i] = star->position;
	}
	
	// Color 
	star->color.a = 0xFF;
	//printf("Color: 0x%d\n", star->color);
}

void UpdateStar(Star* star, SDL_Renderer* renderer, Vector2* origen)
{
	Vector2 p = { star->position.x + origen->x, star->position.y + origen->y };
	// Revisa si la estrella estan dentro de la ventana 
	if (p.x < 0 || p.x > WIDTH || p.y < 0 || p.y > HEIGHT)
	{
		star->position.x = 0;
		star->position.y = 0;
		star->color.a = ALPHA_MIN;
	}

	//
	for (int i = TRAIL - 1; i > 0 ; i--)
	{
		star->trail[i] = star->trail[i - 1];
	}
	star->trail[0] = star->position;

	// Mueve las Estrellas 
	star->position.x += star->speed * star->angle.x;
	star->position.y += star->speed * star->angle.y;

	// Color 
	int alpha = star->color.a + ALPHA_RATE;
	if (alpha > 0xFF)
	{
		star->color.a = 0xFF;
	}
	else
	{
		star->color.a = alpha;
	}

	// Manda a Dibujar las Estrellas 
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, star->color.a);
	SDL_RenderDrawPoint(renderer, p.x, p.y);
	for (int i  = 0; i < TRAIL; i++)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, star->color.a / (i+1));
		SDL_RenderDrawPoint(renderer, star->trail[i].x + origen->x, star->trail[i].y + origen->y);
	}
}

float RandFloat(float min, float max)
{
	float ratio = (float)rand() / (float)RAND_MAX;
	return (ratio * (max - min)) + min;
}
