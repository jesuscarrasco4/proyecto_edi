//============================================================================
// Name        : progPrincipal.cpp
// Author      : Profesores de la asignatura EDI
// Version     : Curso 25/26
// Copyright   :
// Description : Programa principal proyecto EDI
//============================================================================

#include <iostream>
#include <string>
#include <limits>
#include "Sistema.h"

using namespace std;

// Menú
int menu(string nombreSistema) {
    int opcion;
    do {
        cout << endl << endl;
        cout << " -------- " << nombreSistema << " --------" << endl << endl;
        cout << " 1. Mostrar todos los usuarios             " << endl;
        cout << " 2. Buscar y mostrar un usuario            " << endl;
        cout << " 3. Mostrar artistas y sus canciones       " << endl;
        cout << " 4. Buscar y mostrar un artista            " << endl;
        cout << " 5. Reproducir una playlist de un usuario  " << endl;
        cout << " 6. Compartir playlist entre dos usuarios  " << endl;
        cout << " 7. Eliminar playlist de un usuario        " << endl;
        cout << " 8. Añadir artista a favoritos de un usuario" << endl;
        cout << " 9. Eliminar artista de favoritos de un usuario" << endl;
        cout << " 10. Artista con mas seguidores          " << endl;

        cout << " 0. Finalizar. " << endl;
        cout << " Opción: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

    } while ((opcion < 0) || (opcion > 10));
    return opcion;
}

// Función principal
int main() {
    Sistema *miSistema = new Sistema("Sistema EDI");

    bool salir = false;
    int opcion;

    string nombreU, nombreDest, nombrePL, nombreArtista;

    while (!salir) {
        opcion = menu("Simulador Spotify");

        switch (opcion) {
        case 1:
            miSistema->mostrarUsuarios();
            break;

        case 2:
            cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
            getline(cin, nombreU);
            miSistema->buscarUsuario(nombreU);
            break;

        case 3:
            miSistema->mostrarArtistas();
            break;

        case 4:
            cout << "Introduce el nombre del artista: ";
            getline(cin, nombreArtista);
            miSistema->buscarArtista(nombreArtista);
            break;

        case 5:
            cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
            getline(cin, nombreU);
            cout << "Nombre de la PlayList: ";
            getline(cin, nombrePL);
            cout << "[Aviso] Asegúrate de tener el método implementado en Sistema." << endl;
            break;

        case 6:
            cout << "Usuario Origen: "; getline(cin, nombreU);
            cout << "Nombre de la PlayList: "; getline(cin, nombrePL);
            cout << "Usuario Destino: "; getline(cin, nombreDest);
            miSistema->compartirPlayList(nombreU, nombrePL, nombreDest);
            break;

        case 7:
            cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
            getline(cin, nombreU);
            cout << "Nombre de la PlayList: ";
            getline(cin, nombrePL);
            miSistema->eliminarPlayList(nombreU, nombrePL);
            break;

        case 8:
            cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
            getline(cin, nombreU);
            cout << "Introduce el nombre del artista: ";
            getline(cin, nombreArtista);
            miSistema->anadirArtistaFavorito(nombreU, nombreArtista);
            break;

        case 9:
            cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
            getline(cin, nombreU);
            cout << "Introduce el nombre del artista: ";
            getline(cin, nombreArtista);
            miSistema->eliminarArtistaFavorito(nombreU, nombreArtista);
            break;

        case 10:
            miSistema->mostrarArtistaConMasSeguidores();
            break;

        case 0:
            salir = true;
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            break;
        }
    }

    delete miSistema;

    return 0;
}
