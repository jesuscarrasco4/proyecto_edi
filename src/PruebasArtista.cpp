/*
 * PruebasArtista.cpp
 *
 *  Created on: 2 mar 2026
 *      Author: estudiante
 */

#include "PruebasArtista.h"
#include <iostream>

using namespace std;

void pruebasArtista() {
    cout << "--- Inicio de Pruebas Dinámicas: Artista ---" << endl;

    // Crear un artista dinámicamente
    Artista *a1 = new Artista("Rosalia", "España", 20000000);

    // Mostrar sus datos
    a1->mostrar();

    // Crear otro artista para comparar
    Artista *a2 = new Artista("Bad Bunny", "Puerto Rico", 50000000);

    // Probar el operador < (alfabético)
    if (*a1 < *a2) {
        cout << a1->getNombre() << " va antes que " << a2->getNombre() << endl;
    } else {
        cout << a2->getNombre() << " va antes que " << a1->getNombre() << endl;
    }

    // ¡MUY IMPORTANTE! Liberar la memoria
    delete a1;
    delete a2;

    cout << "--- Fin de Pruebas ---" << endl;
}
