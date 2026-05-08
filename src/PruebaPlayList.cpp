#include "PruebaPlayList.h"
#include <iostream>

using namespace std;

void pruebasPlayList() {
    cout << "--- Inicio de Pruebas: PlayList ---" << endl;

    Cancion *c1 = new Cancion("One", "Rock", 240);
    Cancion *c2 = new Cancion("Two", "Pop", 180);
    Cancion *c3 = new Cancion("Three", "Indie", 210);

    PlayList *pl = new PlayList("Mix");
    pl->agregarCancion(c1);
    pl->agregarCancion(c2);
    pl->agregarCancion(c3);

    cout << "Num canciones (esperado 3): " << pl->getNumCanciones() << endl;
    cout << "Duracion total (esperado 630): " << pl->getDuracion() << endl;

    cout << "[1] Reproduccion completa:" << endl;
    pl->reproducirTodo();

    cout << "[2] Reproduccion desde posicion 2:" << endl;
    pl->reproducirAPartir(2);

    cout << "[3] Probando copia por agregacion..." << endl;
    PlayList *copia = new PlayList(*pl);
    cout << "Copia num canciones (esperado 3): " << copia->getNumCanciones() << endl;

    pl->eliminarCancion();
    cout << "Original tras eliminar una (esperado 2): " << pl->getNumCanciones() << endl;
    cout << "Copia se mantiene en 3: " << copia->getNumCanciones() << endl;

    delete pl;
    delete copia;
    delete c1;
    delete c2;
    delete c3;

    cout << "--- Fin de Pruebas: PlayList ---" << endl;
}
