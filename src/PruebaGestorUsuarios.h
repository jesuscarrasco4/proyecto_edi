#ifndef PRUEBAGESTORUSUARIOS_H_
#define PRUEBAGESTORUSUARIOS_H_

#include "GestorUsuarios.h"

/**
 * Casos de prueba para GestorUsuarios:
 * 1. Inserción en lista vacía.
 * 2. Inserción al principio (orden alfabético).
 * 3. Inserción al final.
 * 4. Inserción en posición intermedia.
 * 5. Intento de insertar un duplicado (no debe insertarse).
 * 6. Búsqueda de usuario existente y no existente.
 * 7. Verificación de la copia profunda (Constructor de copia).
 */
void pruebasGestorUsuarios();
void pruebasUsuarioSesion78();
void pruebasGestorUsuariosABB();

#endif
