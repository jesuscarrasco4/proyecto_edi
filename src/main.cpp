#include "Pruebas.h"
#include "Usuario.h"
#include <iostream>
#include "Artista.h"
#include "PruebasArtista.h"
#include "Cancion.h"
#include "PruebasCancion.h"
#include "PruebaGestorUsuarios.h"
#include "PruebaGestorArtistas.h"

using namespace std;

// Cambiamos el nombre para que no choque con el main de progPrincipal.cpp
void ejecutarPruebas() {
    cout << "--- EJECUTANDO BATERÍA DE PRUEBAS DEL SISTEMA ---" << endl;

    pruebasArtista();
    pruebasCancion();
    pruebasGestorUsuarios();
    pruebasGestorArtistas();
    pruebasUsuarioSesion78();

    cout << "--- PRUEBAS FINALIZADAS CON ÉXITO ---" << endl;
}
