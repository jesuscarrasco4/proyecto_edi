#include "PruebaGestorUsuarios.h"
#include <iostream>

using namespace std;

// Pruebas Gestor Usuarios
void pruebasGestorUsuarios() {
    cout << "--- Inicio de Pruebas: GestorUsuarios ---" << endl;

    GestorUsuarios *gestor = new GestorUsuarios();

    gestor->insertar("2", "Casillas, Iker", "iker@real.com", "123", 20, 5, 1981);
    gestor->insertar("1", "Arbeloa, Alvaro", "alvaro@real.com", "123", 17, 1, 1983);
    gestor->insertar("3", "Zidane, Zinedine", "zizou@real.com", "123", 23, 6, 1972);

    cout << "Usuarios tras inserciones (deben salir ordenados):" << endl;
    gestor->mostrar();

    cout << "\nIntentando insertar duplicado (Arbeloa)..." << endl;
    gestor->insertar("1", "Arbeloa, Alvaro", "copy@real.com", "999", 1, 1, 1990);
    cout << "Numero de elementos (debe ser 3): " << gestor->numElementos() << endl;

    cout << "\nBuscando a 'Casillas, Iker'..." << endl;
    Usuario *buscado = gestor->buscar("Casillas, Iker");
    if (buscado) {
        cout << "[OK] Encontrado: " << buscado->getEmail() << endl;
    } else {
        cout << "[ERROR] No encontrado" << endl;
    }

    cout << "\nProbando constructor de copia (Copia Profunda)..." << endl;
    GestorUsuarios *copiaGestor = new GestorUsuarios(*gestor);
    cout << "Copia del gestor creada. Elementos en copia: " << copiaGestor->numElementos() << endl;

    delete gestor;
    delete copiaGestor;

    cout << "\n--- Fin de Pruebas: Memoria Liberada ---" << endl;
}

// Pruebas Usuario Sesión 7 y 8
void pruebasUsuarioSesion78() {
    cout << "\n--- Inicio de Pruebas: Usuario (Nuevos Atributos) ---" << endl;

    Usuario *u1 = new Usuario("U1", "Zidane, Zinedine", "zizou@madrid.com", "123", 23, 6, 1972);
    Usuario *u2 = new Usuario("U2", "Raul, Gonzalez", "capitan@madrid.com", "777", 27, 6, 1977);

    Artista *a1 = new Artista("Coldplay", "UK", 1000);
    Cancion *c1 = new Cancion("Yellow", "Rock", 269);

    cout << "[1] Creando PlayList y añadiendo cancion..." << endl;
    u1->crearPlayList("Favoritos 2026");
    u1->crearPlayList("Favoritos 2026");
    u1->anadirCancionAPlayList("Favoritos 2026", c1);

    cout << "[2] Insertando Artista Favorito..." << endl;
    u1->insertarArtistaFavorito(a1);
    cout << "Seguidores tras insertar favorito (esperado 1001): "
         << a1->getNumeroSeguidores() << endl;
    u1->mostrarFavoritos();

    cout << "\n[3] Compartiendo PlayList de u1 a u2..." << endl;
    PlayList *copiaCompartida = u1->compartirPlayList("Favoritos 2026");
    if (copiaCompartida != nullptr) {
        u2->anadirPlayListCompartida(copiaCompartida);
        cout << "[OK] PlayList compartida e insertada en u2" << endl;
    }

    cout << "\n[4] Eliminando Artista Favorito..." << endl;
    u1->eliminarArtistaFavorito("Coldplay");
    cout << "Seguidores tras eliminar favorito (esperado 1000): "
         << a1->getNumeroSeguidores() << endl;
    u1->mostrarFavoritos();

    cout << "\n[5] Simulando reproduccion de PlayLists..." << endl;
    u2->reproducirPlayLists();

    delete u1;
    delete u2;
    delete a1;
    delete c1;

    cout << "--- Fin de Pruebas: Usuario (Sesion 7-8) OK ---" << endl;
}

// Pruebas Gestor Usuarios ABB
void pruebasGestorUsuariosABB() {
    cout << "--- Inicio de Pruebas: GestorUsuarios con ÁRBOL (ABB) ---" << endl;

    GestorUsuarios *gestor = new GestorUsuarios();

    cout << "[1] Insertando usuarios para formar el árbol..." << endl;
    gestor->insertar("2", "Casillas, Iker", "iker@real.com", "123", 20, 5, 1981);
    gestor->insertar("1", "Arbeloa, Alvaro", "alvaro@real.com", "123", 17, 1, 1983);
    gestor->insertar("3", "Zidane, Zinedine", "zizou@real.com", "123", 23, 6, 1972);
    gestor->insertar("4", "Bernabeu, Santiago", "presi@real.com", "123", 8, 6, 1895);

    cout << "\n[2] Usuarios en Inorden (deben salir: Arbeloa -> Bernabeu -> Casillas -> Zidane):" << endl;
    gestor->mostrar();

    cout << "\n[3] Buscando clave existente (Arbeloa, Alvaro)..." << endl;
    Usuario *u = gestor->buscar("Arbeloa, Alvaro");
    if (u) cout << "[OK] Encontrado: " << u->getApellidosNombre() << endl;
    else   cout << "[ERROR] No encontrado" << endl;

    cout << "\nBuscando clave inexistente (Ronaldo, Cristiano)..." << endl;
    if (!gestor->buscar("Ronaldo, Cristiano")) cout << "[OK] Detectado correctamente que no existe." << endl;

    cout << "\n[4] Intentando insertar duplicado (Zidane, Zinedine)..." << endl;
    gestor->insertar("3", "Zidane, Zinedine", "otro@real.com", "000", 1, 1, 2000);
    cout << "Número de elementos (debe seguir siendo 4): " << gestor->numElementos() << endl;

    cout << "\n[5] Probando copia del Gestor (Árbol completo)..." << endl;
    GestorUsuarios *copia = new GestorUsuarios(*gestor);
    cout << "Elementos en la copia: " << copia->numElementos() << endl;

    delete gestor;
    delete copia;

    cout << "\n--- Fin de Pruebas ABB: Memoria Liberada ---" << endl;
}
