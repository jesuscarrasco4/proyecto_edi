#include "PruebasCancion.h"
#include <iostream>

using namespace std;

void pruebasCancion() {
    cout << "\n--- Inicio de Pruebas Dinámicas: Canción ---" << endl;

    // 1. Creación dinámica (Constructor parametrizado) [cite: 42, 52]
    Cancion *c1 = new Cancion("Starman", "Rock", 255);
    Cancion *c2 = new Cancion("Bohemian Rhapsody", "Rock", 354);

    // 2. Mostrar datos [cite: 44]
    cout << "Cancion 1: ";
    c1->mostrar();
    cout << "Cancion 2: ";
    c2->mostrar();

    // 3. Probar Operador < (Orden alfabético) [cite: 46]
    // "Bohemian Rhapsody" debería ser menor que "Starman"
    if (*c2 < *c1) {
        cout << "[OK] '" << c2->getTitulo() << "' va antes que '" << c1->getTitulo() << "'" << endl;
    }

    // 4. Probar Operador == [cite: 45]
    Cancion *c3 = new Cancion("Starman", "Pop", 120); // Mismo título, distinto resto
    if (*c1 == *c3) {
        cout << "[OK] Las canciones son iguales por titulo: " << c1->getTitulo() << endl;
    }

    // 5. Liberar memoria (Destructor) [cite: 47, 54]
    delete c1;
    delete c2;
    delete c3;

    cout << "--- Fin de Pruebas Canción: Memoria Liberada ---" << endl;
}
