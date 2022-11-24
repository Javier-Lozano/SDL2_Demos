#if !defined(COMMON_MATH_H)
#define COMMON_MATH_H

#include <stdlib.h>

/* Macros */

#define PI 3.1416
#define SIGN(n) n >= 0 ? 1 : -1;

/* Declaracion de Funciones */

/**
 * Obten un numero aleatoreo de punto flotante entre a (inclusivo) y b (inclusivo)
 * \param a Rango Minimo
 * \param b Rango Maximo
 *
 * \return Numero aleatoreo de punto flotante
 */
float FloatRNG(float a, float b);

#endif // COMMON_MATH_H
