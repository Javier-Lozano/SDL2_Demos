#include "star.h"

// Contruye una 'estrella'
void StarConstruct(Star* star, float area_width, float area_height)
{
	// Obten la Velocidad aleatorea entre STAR_SPEED_MIN y STAR_SPEED_MAX
	star->speed = FRand((float)STAR_SPEED_MIN, (float)STAR_SPEED_MAX);
	
	// Inicializamos la posicion de la estrella y su origen
	star->position.x = FRand(-area_width  * 0.5, area_width  * 0.5);
	star->position.y = FRand(-area_height * 0.5, area_height * 0.5);
	star->position.z = FRand(0, Z_MAX);
}

// Actualiza a la 'estrella'
void StarUpdate(Star* star, SDL_Color* color)
{
    // Calcula el procentaje de la posicion en Z sobre Z_MAX
	//float ratio = 1 - (star->position.z / Z_MAX);

	// Mueve la estrella en direccion al origen
	star->position.z += star->speed;

	// Si la estrella llegó al origen
	if (star->position.z > Z_MAX)
	{
		star->position.z = 0;
	}
}

void StarRender(SDL_Renderer* renderer, Texture* texture, Star* star, Vector3* origin, SDL_Color* color)
{
    // Renderiza una estela de estrellas fugacez
	for (int i = 0; i <= TAIL; i++)
	{
        // Calcula las posiciones para la estrella y sus puntos anteriores
        float p = star->position.z - (i * star->speed);

		// Si el posicion es menor a 0 iguala a Z_MAX
        if (p < 0) p = Z_MAX;
    
        // Calcula el porcentaje entre la posicion actual y Z_MAX
        float ratio = RATIO(p);

        // Multiplica el vector de posicion dicho porcentaje
        Vector3 v = Vector3Mult(star->position, ratio);

        // Mueve el vector reultante al origen
        v = Vector3Add(v, *origin);

        // Multiplica el porcentaje por PI porque gradualmente el angulo transiciona de 0 a 180°
        float angulo = PI * ratio;
        // Se requiere calcular Seno Absoluto para hacer un efecto de: Aparicion y Desaparicion
        float sin = SDL_fabsf(SDL_sin(angulo));

        // Modifica el canal alpha
        color->a = 255 * sin;
        //printf("Ratio: %f -> T %f\n", ratio, sin);

        // Escala la textura deacuerdo al porcentaje
        TextureSetScale(texture, ratio, ratio);

        // Renderiza Textura en posicion
        TextureRender(renderer, texture, v.x, v.y, 1, color);
    
	}
}