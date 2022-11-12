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

#include <SDL2/SDL.h>
#include <time.h>

// MACROS 

#define NAME "C Starfield - SDL2"
#define WIDTH	640
#define HEIGHT	480

#define STARS			500
#define STAR_SPEED_MIN	5
#define STAR_SPEED_MAX	10
#define TAIL	10

#define ALPHA_RATE	10
#define COLOR_RATE	0.5

#define Z_MAX 500

#define PI	3.1416

// Structs

typedef struct {
	float x;
	float y;
	float z;
} Vector3;

typedef struct {
	Vector3 position;
	float tail[TAIL];
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
void UpdateStar(Star* star, SDL_Renderer* renderer, Vector3* origin, SDL_Color* color);
void ChangeColor(float numerator, SDL_Color* color);
float RandFloat(float min, float max);

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

	//SDL_RenderSetLogicalSize(demo->renderer, WIDTH / 2, HEIGHT / 2);

	// Semilla aleatorea en base a la "Tiempo" actual 
	srand(time(NULL));

	// Inicializa Origen 
	Vector3 origen = { WIDTH * 0.5, HEIGHT * 0.5, 0 };

	// Inicializa 'Starfield' 
	Star* starfield = malloc(sizeof(Star) * STARS);
	for (int i = 0; i < STARS; i++)
	{
		ConstructStar(&starfield[i]);
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
	// Obten la Velocidad aleatorea entre STAR_SPEED_MIN y STAR_SPEED_MAX
	star->speed = RandFloat((float)STAR_SPEED_MIN, (float)STAR_SPEED_MAX);
	
	// Inicializamos la posicion de la estrella y su origen
	star->position.x = RandFloat(WIDTH * -0.5f, WIDTH * 0.5f);
	star->position.y = RandFloat(HEIGHT * -0.5f, HEIGHT * 0.5f);
	star->position.z = RandFloat(0, Z_MAX);

	// Inicializamos la cola
	for (int i = 0; i < TAIL; i++)
	{
		star->tail[i] = star->position.z;
	}
}

void UpdateStar(Star* star, SDL_Renderer* renderer, Vector3* origen, SDL_Color* color)
{
	// Calcula el procentaje de la posicion en Z sobre Z_MAX
	float ratio = 1 - (star->position.z / Z_MAX);

	// Origen + Posicion de la particula
	Vector3 p = {
		(star->position.x * ratio) + origen->x,
		(star->position.y * ratio) + origen->y,
		star->position.z };

	// Si la estrella llegó al origen
	if (p.z < 0)
	{
		star->position.z = Z_MAX;
		star->alpha = 0;
	}

	// Mueve de posiciones que componene el "Barrido"
	for (int i = TAIL - 1; i > 0 ; i--)
	{
		star->tail[i] = star->tail[i - 1];
	}

	// Almacena la posicion actual y el valor de Alpha
	star->tail[0] = star->position.z;

	// Mueve la estrella en direccion al origen
	star->position.z -= star->speed;

	// Cambiar Alpha
	star->alpha = 255 * ratio;
	//printf("Ratio: %f Alpha: %d\n", ratio, star->alpha);

	// Manda a dibujar la estrella 
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, star->alpha);
	SDL_RenderDrawPoint(renderer, p.x, p.y);

	// Dibuja el "Barrido"
	for (int i = 0; i < TAIL; i++)
	{
		// Calcula porcentaje para la posicion de la cola.
		float t_ratio = 1 - (star->tail[i] / Z_MAX);
		float t_alpha = 255 * t_ratio;
		//printf("\tT_Ratio: %f T_Alpha: %d\n", t_ratio, (int)t_alpha);

		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, (int)t_alpha / (i+1));
		SDL_RenderDrawPoint(renderer, (star->position.x * t_ratio) + origen->x, (star->position.y * t_ratio) + origen->y);
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
}

float RandFloat(float min, float max)
{
	float ratio = (float)rand() / (float)RAND_MAX;
	return (ratio * (max - min)) + min;
}
