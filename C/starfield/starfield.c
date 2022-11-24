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
 * Las teclas Arriba y Abajo aumentan y decrecen la velocidad de las estrellas
 *  respectivamente.
 * 
 * La tecla Enter/Return activa una Transicion en la cual las estrellas
 * cambiaran de direccion. Tambien es posible activar una transicion automatica
 * con la tecla TAB.
 */

#include "starfield.h"

int main(int argc, char* args[])
{
	// Variables
	Demo demo;
	int run;
	int loop;

	Texture starTexture;
	Vector3 starOrigin;
	Star stars[STARS];
	int starSpeed;

	Uint32 ticks;
	Uint32 timeDelta;
	Uint32 clock;

	int transitionState;
	int transitionAutomatic;
	int directionSign;
	float direction;

	printf("Up - Speeds Up\nDown - Speeds Down\nReturn - Manually activates Transition\nTab - Switch automatic Transition ON and OFF.\n");

	// Inicia SDL
	run = StartSDL(&demo, NAME, WIDTH, HEIGHT, SDL_FLAGS, WINDOW_FLAGS, RENDER_FLAGS);

	// Si SDL inicio correctamente continua con la ejecucion
	if (run)
	{
		// Inicializa rand() con el tiempo actual
		srand(time(NULL));

		// Activa el Alpha Blending
		SDL_SetRenderDrawBlendMode(demo.renderer, SDL_BLENDMODE_BLEND);

		// Carga la Textura.
		TextureLoad(demo.renderer, "resources/Star_Dot.bmp", &starTexture);

		// Posiciona el 'Origen' al centro de la ventana
		starOrigin.x = WIDTH * 0.5;
		starOrigin.y =  HEIGHT * 0.5;

		// Inicializa las estrellas
		for (int i = 0; i < STARS; i++)
		{
			StarConstruct(&stars[i], WIDTH, HEIGHT, Z_MAX);
		}

		// Inicializa la velocidad
		starSpeed = STAR_SPEED;

		// Inicializamos el reloj, contador y 'tiempo delta' en 0
		clock = 0;
		ticks = 0;
		timeDelta = 0;

		// Inicializa el estado de la Transicion
		transitionState = 0;
		transitionAutomatic = 0;

		// Inicializamos la direccion positiva
		direction = 1;
		directionSign = 1;

		// Bucle Principal
		loop = 1;
		while (loop)
		{
			// Obten el tiempo actual
			ticks = SDL_GetTicks();
			// Aumenta el tiempo al reloj
			clock += timeDelta;

			// Eventos
			while (SDL_PollEvent(&demo.event))
			{
				if (demo.event.type == SDL_QUIT)
				{
					loop = 0;
				}
				else if (demo.event.type == SDL_KEYDOWN)
				{
					// Obten la tecla que fue presionada
					SDL_Keycode key = demo.event.key.keysym.sym;

					// Modifica la velocidad
					if (key == SDLK_UP)
					{
						starSpeed += 5;
						printf("Speed UP!: %d\n", starSpeed);
					}
					else if (key == SDLK_DOWN)
					{
						starSpeed -= 5;
						printf("Speed DOWN!: %d\n", starSpeed);
					}

					// Activa Transicion manualmente
					if (key == SDLK_RETURN && !transitionState)
					{
						clock = 0;
						transitionState = 1;
						printf("Turning DIRECTION!\n");
					}

					// Activa o Desactiva Transicion Automatica
					if (key == SDLK_TAB)
					{
						transitionAutomatic = !transitionAutomatic;
						clock = 0;
						printf("Automatic Transition SWITCHED! %d\n", transitionAutomatic);
					}
				}
			}

			// Revisa los estados
			if (!transitionState && transitionAutomatic && clock >= STARFIELD_TIME_MS)
			{
				clock = 0;
				transitionState = 1;
				printf("Turning DIRECTION!\n");
			}
			else if (transitionState)
			{
				float ratio = (float)clock / TRANSITION_TIME_MS;
				direction = SDL_cosf(ratio * PI) * directionSign;
				if (clock >= TRANSITION_TIME_MS)
				{
					clock = 0;
					transitionState = 0;
					directionSign = SIGN(direction);
					direction = directionSign;
				}
				//printf("Ratio: %f Dir: %f\n", ratio, direction);
			}

			// Limpia Pantalla 
			SDL_SetRenderDrawColor(demo.renderer, 0, 0, 0, 0xFF);
			SDL_RenderClear(demo.renderer);

			// Actualiza Estrellas 
			for (int i = 0; i < STARS; i++)
			{
				StarUpdate(&stars[i], starSpeed * direction);
				StarRender(demo.renderer, &stars[i], &starTexture, &starOrigin);
			}

			// Renderiza
			SDL_RenderPresent(demo.renderer);

			// Calcula el 'tiempo delta'
			timeDelta = SDL_GetTicks() - ticks;
		}

		// Libera Recursos
		TextureDestroy(&starTexture);
	}

	// Terminar SDL
	CloseSDL(&demo);

	return 0;
}

/*
void CreateColors(SDL_Color* color, int color_num, int index)
{
	// Variables
	int red_section = color_num / 3;
	int green_section = (color_num * 2) / 3;
	int blue_section = color_num;

	// Colores
	int c1 = (255 * index) / color_num;
	int c2 = 255 - c1;
	int c3 = 0;
	
	if (index < red_section) // Transiciona de Rojo a Verde
	{
		color->r = c2;
		color->g = c1;
		color->b = c3;
	}
	else if (index < green_section) // Transiciona de Verde a Azul
	{
		color->r = c3;
		color->g = c2;
		color->b = c1;
	}
	else if (index < blue_section) // Transiciona de Azul a Rojo
	{
		color->r = c1;
		color->g = c3;
		color->b = c2;
	}
}
*/

/*
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
*/
