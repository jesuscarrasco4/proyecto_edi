#include "PruebaGestorArtistas.h"
#include <iostream>

using namespace std;

// Pruebas Gestor Artistas
void pruebasGestorArtistas() {
    cout << "--- Inicio de Pruebas: GestorArtistas (ABB) ---" << endl;

    GestorArtistas *ga = new GestorArtistas();

    cout << "[1] Buscando en estructura vacia..." << endl;
    if (ga->buscar("Cualquiera") == nullptr) {
        cout << "[OK] Busqueda en vacio correcta." << endl;
    }

    cout << "\n[2] Realizando inserciones en el Arbol..." << endl;

    ga->insertar("Muse", "UK");
    ga->insertar("AC/DC", "Australia");
    ga->insertar("ZZ Top", "USA");
    ga->insertar("Queen", "UK");

    cout << "\nLista de artistas (deben salir: AC/DC, Muse, Queen, ZZ Top):" << endl;
    ga->mostrar();

    cout << "\n[3] Buscando artista 'Queen'..." << endl;
    Artista *encontrado = ga->buscar("Queen");
    if (encontrado != nullptr) {
        cout << "[OK] Encontrado: " << encontrado->getNombre() << " de " << encontrado->getPais() << endl;
    } else {
        cout << "[ERROR] No se encontro a Queen." << endl;
    }

    cout << "\n[4] Buscando artista inexistente ('Estopa')..." << endl;
    if (ga->buscar("Estopa") == nullptr) {
        cout << "[OK] El sistema detecta correctamente que no existe." << endl;
    }

    delete ga;
    cout << "\n--- Fin de Pruebas GestorArtistas: Memoria Liberada ---" << endl;
}
