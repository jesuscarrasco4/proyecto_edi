#include "PruebasArtista.h"
#include <iostream>

using namespace std;

// Pruebas Artista
void pruebasArtista() {
    cout << "--- Inicio de Pruebas: Artista con Lista de Canciones ---" << endl;

    Artista *a1 = new Artista("Coldplay", "UK", 50000000);

    cout << "\n[1] Insertando canciones..." << endl;
    a1->insertarCancion("Yellow", "Alternative", 269);
    a1->insertarCancion("Clocks", "Rock", 307);
    a1->insertarCancion("Zzz", "Relax", 120);

    cout << "[2] Intentando insertar duplicado ('Yellow')..." << endl;
    a1->insertarCancion("Yellow", "Pop", 100);

    cout << "\nEstado del artista:" << endl;
    a1->mostrar();
    cout << "Total canciones: " << a1->numCanciones() << " (esperado: 3)" << endl;

    cout << "\n[3] Probando busqueda..." << endl;
    Cancion datosEncontrados;
    if (a1->buscarCancion("Yellow", datosEncontrados)) {
        cout << "[OK] Cancion encontrada: " << datosEncontrados.getTitulo()
             << " [" << datosEncontrados.getGenero() << "]" << endl;
    } else {
        cout << "[ERROR] No se encontro 'Yellow'" << endl;
    }

    cout << "\n[4] Probando copia profunda (Constructor de copia)..." << endl;
    Artista *a2 = new Artista(*a1);

    cout << "Copia creada. Modificando original (borramos canciones en el original indirectamente)..." << endl;

    delete a1;

    cout << "Datos del artista clonado tras borrar el original:" << endl;
    a2->mostrar();

    delete a2;

    cout << "\n--- Fin de Pruebas Artista: Memoria OK ---" << endl;
}
