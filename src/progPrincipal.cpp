#include <iostream>
#include <limits>
#include "Sistema.h"
#include "Pruebas.h"

void pruebasGestorUsuarios();

using namespace std;

void mostrarMenu() {
    cout << "\n=============   MENU   =============" << endl;
    cout << "1. Mostrar todos los Usuarios" << endl;
    cout << "2. Mostrar todos los Artistas y Canciones" << endl;
    cout << "3. Buscar Usuario" << endl;
    cout << "4. Compartir PlayList entre Usuarios" << endl;
    cout << "5. Buscar Artista por nombre" << endl;
    cout << "6. Eliminar PlayList" << endl;
    cout << "7. Añadir Artista a Favoritos" << endl;
    cout << "8. Eliminar Artista de Favoritos" << endl;
    cout << "9. Mostrar Artista con mas Seguidores" << endl;
    cout << "10. Ejecutar Bateria de Pruebas" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Sistema *miSistema = new Sistema("Sistema EDI");
    int opcion;
    string nombreU, nombreDest, nombrePL, nombreArtista;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer tras leer un entero

        switch (opcion) {
            case 1:
                miSistema->mostrarUsuarios();
                break;
            case 2:
                miSistema->mostrarArtistas();
                break;
            case 3:
                cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
                getline(cin, nombreU);
                miSistema->buscarUsuario(nombreU);
                break;
            case 4:
                cout << "Usuario Origen: "; getline(cin, nombreU);
                cout << "Nombre de la PlayList: "; getline(cin, nombrePL);
                cout << "Usuario Destino: "; getline(cin, nombreDest);
                miSistema->compartirPlayList(nombreU, nombrePL, nombreDest);
                break;
            case 5:
                cout << "Introduce el nombre del artista: ";
                getline(cin, nombreArtista);
                miSistema->buscarArtista(nombreArtista);
                break;
            case 6:
                cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
                getline(cin, nombreU);
                cout << "Nombre de la PlayList: ";
                getline(cin, nombrePL);
                miSistema->eliminarPlayList(nombreU, nombrePL);
                break;
            case 7:
                cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
                getline(cin, nombreU);
                cout << "Introduce el nombre del artista: ";
                getline(cin, nombreArtista);
                miSistema->anadirArtistaFavorito(nombreU, nombreArtista);
                break;
            case 8:
                cout << "Introduce el nombre del usuario (Apellido, Nombre): ";
                getline(cin, nombreU);
                cout << "Introduce el nombre del artista: ";
                getline(cin, nombreArtista);
                miSistema->eliminarArtistaFavorito(nombreU, nombreArtista);
                break;
            case 9:
                miSistema->mostrarArtistaConMasSeguidores();
                break;
            case 10:
            	cout << "\n[SISTEMA] Iniciando bateria de pruebas..." << endl;
            	ejecutarPruebas();
            	break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);

    delete miSistema;
    return 0;
}
