#if !defined(STAR_H)
#define STAR_H

#include "../common/math.h"
#include "../common/vector.h"
#include "../common/texture.h"

/* Estructuras */

typedef struct Star {
	Vector3 position;
	SDL_Color color;
	float maxZ;
} Star;

/* Declaracion de Funciones */

/**
 * Construye una Estrella
 * 
 * \param star Estrella a inicializar
 * \param area_width Area horizontal para inicializar posicion
 * \param area_height Area vertical para inicializar posicion
 * \param max_z Maxima distancia en el Eje Z
 */
void StarConstruct(Star* star, float area_width, float area_height, float max_z);

/**
 * Actualiza la posicion de la estrella
 * 
 * \param star Estrella a actualizar
 * \param speed Velocidad de la estrella
 */
void StarUpdate(Star* star, float speed);

/**
 * Renderiza la estrella en pantalla con una Textura y Origen determinados
 * 
 * \param renderer Renderer que se utilizara
 * \param star Estrella a renderizar
 * \param texture Textura que se utilizara
 * \param origin Posicion de Origen para la estrella
 */
void StarRender(SDL_Renderer* renderer, Star* star, Texture* texture, Vector3* origin);

#endif // STAR_H
