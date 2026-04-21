#include "PruebaGestorArtistas.h"
#include <iostream>

using namespace std;

void pruebasGestorArtistas() {
    cout << "--- Inicio de Pruebas: GestorArtistas (ABB) ---" << endl;

    // CORRECCIÓN 1: Nombre de la clase en plural 'GestorArtistas'
    GestorArtistas *ga = new GestorArtistas();

    // 1. Probar búsqueda en estructura vacía
    cout << "[1] Buscando en estructura vacia..." << endl;
    if (ga->buscar("Cualquiera") == nullptr) {
        cout << "[OK] Busqueda en vacio correcta." << endl;
    }

    // 2. Probar inserciones (El Árbol las ordenará automáticamente)
    cout << "\n[2] Realizando inserciones en el Arbol..." << endl;

    // CORRECCIÓN 2: Eliminadas etiquetas para evitar errores de compilación
    ga->insertar("Muse", "UK");
    ga->insertar("AC/DC", "Australia");
    ga->insertar("ZZ Top", "USA");
    ga->insertar("Queen", "UK");

    // 3. Mostrar y verificar orden (Saldrán por Inorden alfabético)
    cout << "\nLista de artistas (deben salir: AC/DC, Muse, Queen, ZZ Top):" << endl;
    ga->mostrar();

    // 4. Probar búsqueda de existente
    cout << "\n[3] Buscando artista 'Queen'..." << endl;
    Artista *encontrado = ga->buscar("Queen");
    if (encontrado != nullptr) {
        cout << "[OK] Encontrado: " << encontrado->getNombre() << " de " << encontrado->getPais() << endl;
    } else {
        cout << "[ERROR] No se encontro a Queen." << endl;
    }

    // 5. Probar búsqueda de NO existente
    cout << "\n[4] Buscando artista inexistente ('Estopa')..." << endl;
    if (ga->buscar("Estopa") == nullptr) {
        cout << "[OK] El sistema detecta correctamente que no existe." << endl;
    }

    // 6. Limpieza de memoria
    delete ga;
    cout << "\n--- Fin de Pruebas GestorArtistas: Memoria Liberada ---" << endl;
}
