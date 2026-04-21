#include <iostream>
#include "Sistema.h"

void pruebasGestorUsuarios();

using namespace std;

void mostrarMenu() {
    cout << "\n=============   MENU   =============" << endl;
    cout << "1. Mostrar todos los Usuarios" << endl;
    cout << "2. Mostrar todos los Artistas y Canciones" << endl;
    cout << "3. Buscar Usuario (Info completa)" << endl;
    cout << "4. Compartir PlayList entre Usuarios" << endl;
    cout << "5. Ejecutar Bateria de Pruebas" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    Sistema *miSistema = new Sistema("Sistema EDI");
    int opcion;
    string nombreU, nombreDest, nombrePL;

    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer tras leer un entero

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
            	cout << "\n[SISTEMA] Iniciando bateria de pruebas..." << endl;
            	pruebasGestorUsuarios(); // <--- Aquí es donde se "despierta" el código
            	break;
            case 6:
            	cout << "Saliendo del sistema" << endl;
            	break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 6);

    delete miSistema;
    return 0;
}
