/*
 * Sistema.cpp
 *
 *  Created on: 17 abr 2026
 *      Author: estudiante
 */

#include "Sistema.h"
#include <fstream>
#include <sstream>

// Constructor Parametrizado
Sistema::Sistema(string nombreSistema) {
    this->nombreSistema = nombreSistema;
    this->usuarios = new GestorUsuarios();
    this->artistas = new GestorArtistas(); // [CORREGIDO] Añadida la 's'

    this->cargarUsuarios();
    this->cargarArtistas();
    this->cargarCanciones();
    this->cargarPlayList();
}

// Constructor por Defecto
Sistema::Sistema() {
    this->nombreSistema = "Mi Sistema de Musica";
    this->usuarios = new GestorUsuarios();
    this->artistas = new GestorArtistas(); // [CORREGIDO] Añadida la 's'

    this->cargarUsuarios();
    this->cargarArtistas();
    this->cargarCanciones();
    this->cargarPlayList();
}

// Destructor: Libera los gestores [cite: 144]
Sistema::~Sistema() {
    delete usuarios; // Llama al destructor de GestorUsuarios
    delete artistas; // Llama al destructor de GestorArtistas
}

void Sistema::cargarUsuarios() {
    ifstream archivo("usuarios.csv");
    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea); // Saltar cabecera [cite: 116]

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, nombre, email, pass, fecha;

            // Formato: idUsuario; Apellido(s), Nombre; correo; contraseña; dia/mes/año [cite: 117]
            getline(ss, id, ';');
            getline(ss, nombre, ';');
            getline(ss, email, ';');
            getline(ss, pass, ';');
            getline(ss, fecha, ';');

            if (!id.empty()) {
                // Extraer componentes de la fecha
                stringstream ssFecha(fecha);
                string sDia, sMes, sAnio;
                getline(ssFecha, sDia, '/');
                getline(ssFecha, sMes, '/');
                getline(ssFecha, sAnio, '/');

                // Insertar usando el gestor del sistema
                usuarios->insertar(id, nombre, email, pass, stoi(sDia), stoi(sMes), stoi(sAnio));
            }
        }
        archivo.close();
    }
}

void Sistema::cargarArtistas() {
    ifstream archivo("artistas.csv");
    string linea;

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir artistas.csv" << endl;
        return;
    }

    // Saltar cabecera si el archivo la tiene
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, pais;

        getline(ss, nombre, ';');
        getline(ss, pais, ';');

        if (!nombre.empty()) {
            artistas->insertar(nombre, pais);
            // cout << "Cargado artista: " << nombre << endl; // Descomenta para probar
        }
    }
    archivo.close();
}

void Sistema::cargarCanciones() {
    ifstream archivo("canciones.csv");
    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea); // Saltar cabecera

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombreArtista, titulo, genero, sDuracion;

            // Formato: Artista; Canción; Género; Duración (seg)
            getline(ss, nombreArtista, ';');
            getline(ss, titulo, ';');
            getline(ss, genero, ';');
            getline(ss, sDuracion, ';');

            if (!nombreArtista.empty()) {
                // 1. Localizamos al artista en nuestro gestor
                Artista *a = artistas->buscar(nombreArtista);
                if (a != nullptr) {
                    // 2. Si existe, le añadimos la canción
                    a->insertarCancion(titulo, genero, stoi(sDuracion));
                }
            }
        }
        archivo.close();
    }
}

void Sistema::cargarPlayList() {
    ifstream archivo("playList.csv");
    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea); // Saltar cabecera [cite: 128]

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombreUsuario, nombrePL, nombreArtista, nombreCancion;

            // Formato: Apellido(s), Nombre; nombrePlayList; Artista; canción [cite: 129]
            getline(ss, nombreUsuario, ';');
            getline(ss, nombrePL, ';');
            getline(ss, nombreArtista, ';');
            getline(ss, nombreCancion, ';');

            if (!nombreUsuario.empty()) {
                // 1. Localizar al usuario [cite: 127, 132]
                Usuario *u = usuarios->buscar(nombreUsuario);
                if (u != nullptr) {
                    // 2. Localizar al artista
                    Artista *a = artistas->buscar(nombreArtista);
                    if (a != nullptr) {
                        // 3. Buscar la canción dentro del artista
                        Cancion c;
                        if (a->buscarCancion(nombreCancion, c)) {
                            // 4. Crear la playlist en el usuario si no existe [cite: 74, 75, 127]
                            u->crearPlayList(nombrePL);
                            // 5. Añadir la canción encontrada a esa playlist [cite: 76, 127]
                            u->anadirCancionAPlayList(nombrePL, &c);
                        }
                    }
                }
            }
        }
        archivo.close();
    }
}

void Sistema::mostrarUsuarios() const {
    cout << "Usuarios registrados: " << usuarios->numElementos() << endl; // [cite: 130]
    usuarios->mostrar();
}

void Sistema::mostrarArtistas() const {
    // Aquí podrías añadir un método numArtistas() a tu GestorArtistas si quieres el total
    cout << "Listado de Artistas y sus canciones:" << endl; // [cite: 131]
    artistas->mostrar();
}

void Sistema::compartirPlayList(string nombreOrigen, string nombrePL, string nombreDestino) {
    // 1. Localizar al usuario que comparte [cite: 141]
    Usuario *emisor = usuarios->buscar(nombreOrigen);
    // 2. Localizar al usuario receptor [cite: 143]
    Usuario *receptor = usuarios->buscar(nombreDestino);

    if (emisor != nullptr && receptor != nullptr) {
        // 3. Obtener una copia física de la playlist del emisor [cite: 142]
        PlayList *copia = emisor->compartirPlayList(nombrePL);

        if (copia != nullptr) {
            // 4. Entregar la copia al receptor [cite: 143]
            receptor->anadirPlayListCompartida(copia);
            cout << "[SISTEMA] PlayList '" << nombrePL << "' compartida de "
                 << nombreOrigen << " a " << nombreDestino << endl;
        } else {
            cout << "[ERROR] La PlayList no existe en el origen." << endl;
        }
    } else {
        cout << "[ERROR] Uno de los usuarios no existe." << endl;
    }
}

void Sistema::buscarUsuario(string apellidosNombre) {
    Usuario *u = usuarios->buscar(apellidosNombre);
    if (u != nullptr) {
        cout << "\n--------------------------------------" << endl;
        u->mostrar();           // Muestra ID, Nombre, Email, etc.
        u->mostrarFavoritos();  // Muestra su lista de artistas favoritos
        u->reproducirPlayLists(); // Muestra sus playlists y canciones
        cout << "--------------------------------------" << endl;
    } else {
        cout << "[!] El usuario '" << apellidosNombre << "' no existe en el sistema." << endl;
    }
}
