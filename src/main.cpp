#include "Pruebas.h"
#include "Usuario.h"
#include <iostream>
#include "Artista.h"
#include "PruebasArtista.h"
#include "Cancion.h"
#include "PruebasCancion.h"
#include "PruebaGestorUsuarios.h"
#include "PruebaGestorArtistas.h"
#include "PruebaPlayList.h"

using namespace std;

// Ejecutar pruebas
void ejecutarPruebas() {
    cout << "--- EJECUTANDO BATERÍA DE PRUEBAS DEL SISTEMA ---" << endl;

    pruebasUsuario();
    pruebasArtista();
    pruebasCancion();
    pruebasPlayList();
    pruebasGestorUsuarios();
    pruebasGestorArtistas();
    pruebasUsuarioSesion78();

    cout << "--- PRUEBAS FINALIZADAS CON ÉXITO ---" << endl;
}
