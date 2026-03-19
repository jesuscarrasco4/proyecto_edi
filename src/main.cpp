#include "Pruebas.h"
#include "Usuario.h"
#include <iostream>
#include "Artista.h"
#include "PruebasArtista.h"
#include "Cancion.h"
#include "PruebasCancion.h"
#include "PruebaGestorUsuarios.h"

using namespace std;

// En main.cpp
int main() {

	/*// Practica 03
	TVector misUsuarios;
    int total = 0;

    // 1. Cargamos los 100 usuarios del fichero original
    cargarUsuarios(misUsuarios, total);

    // 2. Elegimos un año para filtrar (por ejemplo, 1995)
    int anioABuscar = 2001;

    // 3. Guardamos los que coincidan en el nuevo fichero
    guardarUsuariosPorAnio(misUsuarios, total, anioABuscar);

    // 4. Mostramos por pantalla para verificar
    mostrarUsuarios(misUsuarios, total);

    // 5. Liberamos la memoria
    destruirUsuarios(misUsuarios, total);
	 */

	// Practica 04
	pruebasArtista();
	pruebasCancion();
	pruebasGestorUsuarios();
	return 0;
}
