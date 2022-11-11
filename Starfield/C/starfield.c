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

#define WIDTH	640
#define HEIGHT	480

#define STARS			500
#define STAR_SPEED_MIN	1
#define STAR_SPEED_MAX	5
#define TRAIL	10

#define ALPHA_MAX	255
#define ALPHA_MIN	0
#define ALPHA_RATE	10

#define PI	3.1416

// Structs

typedef struct {
	float x;
	float y;
} Vector2;

typedef struct {
	Vector2 origin;
	Vector2 position;
	Vector2 trail[TRAIL];
	Vector2 angle;
	float speed;
	int alpha;
} Star;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
} Demo;

// Prototipos

void ConstructStar(Star* star);
void UpdateStar(Star* star, SDL_Renderer* renderer, Vector2* origin, SDL_Color* color);
void ChangeColor(float numerator, SDL_Color* color);
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

	//SDL_RenderSetLogicalSize(demo->renderer, WIDTH / 2, HEIGHT / 2);

	// Semilla aleatorea en base a la "Tiempo" actual 
	srand(time(NULL));

	// Inicializa Origen 
	Vector2 origen = { WIDTH * 0.5, HEIGHT * 0.5 };

	// Inicializa 'Starfield' 
	Star* starfield = malloc(sizeof(Star) * STARS);
	for (int i = 0; i < STARS; i++)
	{
		ConstructStar(&starfield[i]);
	}

	// Color
	SDL_Color color;

	// Pivote que indica
	int num = 0;

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
		num += 1;
		// Cambia el color
		ChangeColor(num, &color);

		// Actualiza Estrellas 
		for (int i = 0; i < STARS; i++)
		{
			UpdateStar(&starfield[i], demo->renderer, &origen, &color);
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
	
	// Distancia del origen
	float distance = RandFloat(10, 100);
	
	// Inicializamos la posicion de la estrella y su origen
	star->origin.x = distance * star->angle.x;
	star->origin.y = distance * star->angle.y;
	star->position.x = star->origin.x;
	star->position.y = star->origin.y;


	// Inicializamos la cola (trail)
	for (int i = 0; i < TRAIL; i++)
	{
		star->trail[i] = star->position;
	}
}

void UpdateStar(Star* star, SDL_Renderer* renderer, Vector2* origen, SDL_Color* color)
{
	// 
	Vector2 p = { star->position.x + origen->x, star->position.y + origen->y };
	// Revisa si la estrella estan dentro de la ventana 
	if (p.x < 0 || p.x > WIDTH || p.y < 0 || p.y > HEIGHT)
	{
		star->position.x = star->origin.x;
		star->position.y = star->origin.y;
		star->alpha = ALPHA_MIN;
	}

	// Mueve de posiciones que componene el "Barrido"
	for (int i = TRAIL - 1; i > 0 ; i--)
	{
		star->trail[i] = star->trail[i - 1];
	}

	// Almacena la posicion actual
	star->trail[0] = star->position;

	// Mueve la estrella de posicion
	star->position.x += star->speed * star->angle.x;
	star->position.y += star->speed * star->angle.y;

	// Cambiar Alpha
	star->alpha += ALPHA_RATE;
	if (star->alpha > ALPHA_MAX)
	{
		star->alpha = ALPHA_MAX;
	}

	// Manda a dibujar la estrella 
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, star->alpha);
	SDL_RenderDrawPoint(renderer, p.x, p.y);

	// Dibuja el "Barrido"
	for (int i = 0; i < TRAIL; i++)
	{
		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, star->alpha / (i+2));
		SDL_RenderDrawPoint(renderer, star->trail[i].x + origen->x, star->trail[i].y + origen->y);
	}
}

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
	else if (section < 200)
	{
		color->r = 0;
		color->g = 255 - (255 * n) / 100;
		color->b = (255 * n) / 100;
	}
	else if (section < 300)
	{
		color->r = (255 * n) / 100;
		color->g = 0;
		color->b = 255 - (255 * n) / 100;
	}


//	int num = (255 * n) / 100;
//	int num2 = 255 - num;
//	color->r = num;
//	color->g = num2;

//	printf("R: %d G: %d B: %d | Numerator: %f Fraction: %f | Color 1: %d Color 2: %d\n", color->r, color->g, color->b, numerator, section, num, num2);
}

float RandFloat(float min, float max)
{
	float ratio = (float)rand() / (float)RAND_MAX;
	return (ratio * (max - min)) + min;
}
