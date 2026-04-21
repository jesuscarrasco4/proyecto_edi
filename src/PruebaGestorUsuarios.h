#ifndef PRUEBAGESTORUSUARIOS_H_
#define PRUEBAGESTORUSUARIOS_H_

#include "GestorUsuarios.h"

/**
 * Casos de prueba para GestorUsuarios:
 * 1. Inserción en lista vacía. [cite: 183]
 * 2. Inserción al principio (orden alfabético). [cite: 184]
 * 3. Inserción al final. [cite: 185]
 * 4. Inserción en posición intermedia. [cite: 186]
 * 5. Intento de insertar un duplicado (no debe insertarse). [cite: 163]
 * 6. Búsqueda de usuario existente y no existente. [cite: 187, 188]
 * 7. Verificación de la copia profunda (Constructor de copia). [cite: 160]
 */
void pruebasGestorUsuarios();
void pruebasUsuarioSesion78();
void pruebasGestorUsuariosABB();

#endif
