#include "star.h"

void StarConstruct(Star* star, float area_width, float area_height, float max_z)
{
    // Asigna el limite en Eje Z
    star->maxZ = max_z;
	
	// Inicializamos la posicion de la estrella y su origen
	star->position.x = FloatRNG(-area_width  * 0.5, area_width  * 0.5);
	star->position.y = FloatRNG(-area_height * 0.5, area_height * 0.5);
	star->position.z = FloatRNG(0, max_z);

    // Inicializamos el color
    star->color.r = rand() % 255;
    star->color.g = rand() % 255;
    star->color.b = rand() % 255;
}

void StarUpdate(Star* star, float speed)
{
	// Mueve la estrella en direccion al origen
	star->position.z += speed;

	// Si la estrella llegó al origen
	if ( (speed > 0) && (star->position.z > star->maxZ) )
	{
		star->position.z = 0;
	}
    else if ( (speed < 0) && (star->position.z < 0) )
    {
        star->position.z = star->maxZ;
    }
}

void StarRender(SDL_Renderer* renderer, Star* star, Texture* texture, Vector3* origin)
{
    // Calcula el porcentaje entre la posicion actual y Z_MAX
    float ratio = star->position.z / star->maxZ;

    // Multiplica el vector de posicion por dicho porcentaje
    Vector3 v = Vector3Mult(star->position, ratio);
    // Mueve el vector resultante al origen
    v = Vector3Add(v, *origin);

    // Para dar un efecto Fade-In y Fade-Ouy utilizaremos la funcion Seno. Asi que calculamos un angulo
    float angulo = PI * ratio;
    // Despues calculamos el seno absoluto
    float sin_abs = SDL_fabsf(SDL_sin(angulo));
    // Y finalmente modificamos el canal alpha
    star->color.a = 255 * sin_abs;

    // Escala la textura deacuerdo al porcentaje
    TextureSetScale(texture, ratio, ratio);

    // Renderiza Textura
    TextureRender(renderer, texture, v.x, v.y, 1, &star->color);
}