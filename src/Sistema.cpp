#include "Sistema.h"
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

    // Convertir a entero de forma segura
    bool convertirEnteroSeguro(const string &texto, int &valor) {
        try {
            size_t idx = 0;
            valor = stoi(texto, &idx);
            return idx == texto.size();
        } catch (...) {
            return false;
        }
    }

    // Abrir archivo CSV
    bool abrirCSV(ifstream &archivo, const string &nombre) {
        archivo.open("../" + nombre);
        if (!archivo.is_open()) {
            archivo.clear();
            archivo.open(nombre);
        }
        return archivo.is_open();
    }

    // Limpiar espacios en los extremos
    string limpiarExtremos(const string &texto) {
        size_t inicio = 0;
        size_t fin = texto.size();

        while (inicio < fin && isspace(static_cast<unsigned char>(texto[inicio]))) {
            inicio++;
        }
        while (fin > inicio && isspace(static_cast<unsigned char>(texto[fin - 1]))) {
            fin--;
        }

        return texto.substr(inicio, fin - inicio);
    }
}

// Constructor parametrizado
Sistema::Sistema(string nombreSistema) {
    this->nombreSistema = nombreSistema;
    this->usuarios = new GestorUsuarios();
    this->artistas = new GestorArtistas();

    this->cargarUsuarios();
    this->cargarArtistas();
    this->cargarCanciones();
    this->cargarPlayList();
}

// Constructor por defecto
Sistema::Sistema() {
    this->nombreSistema = "Mi Sistema de Musica";
    this->usuarios = new GestorUsuarios();
    this->artistas = new GestorArtistas();

    this->cargarUsuarios();
    this->cargarArtistas();
    this->cargarCanciones();
    this->cargarPlayList();
}

// Constructor por copia
Sistema::Sistema(const Sistema &otro) {
    this->nombreSistema = otro.nombreSistema;
    this->usuarios = new GestorUsuarios(*(otro.usuarios));
    this->artistas = new GestorArtistas(*(otro.artistas));
}

// Destructor
Sistema::~Sistema() {
    delete usuarios;
    delete artistas;
}

// Cargar usuarios
void Sistema::cargarUsuarios() {
    ifstream archivo;
    string linea;

    if (abrirCSV(archivo, "usuarios.csv")) {
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, nombre, email, pass, fecha;

            getline(ss, id, ';');
            getline(ss, nombre, ';');
            getline(ss, email, ';');
            getline(ss, pass, ';');
            getline(ss, fecha, ';');

            if (!id.empty()) {
                stringstream ssFecha(fecha);
                string sDia, sMes, sAnio;
                getline(ssFecha, sDia, '/');
                getline(ssFecha, sMes, '/');
                getline(ssFecha, sAnio, '/');

                int dia = 0, mes = 0, anio = 0;
                if (convertirEnteroSeguro(sDia, dia) &&
                    convertirEnteroSeguro(sMes, mes) &&
                    convertirEnteroSeguro(sAnio, anio)) {
                    usuarios->insertar(id, nombre, email, pass, dia, mes, anio);
                } else {
                    cout << "[WARN] Usuario ignorado por fecha invalida: " << linea << endl;
                }
            }
        }
        archivo.close();
    }
}

// Cargar artistas
void Sistema::cargarArtistas() {
    ifstream archivo;
    string linea;

    if (!abrirCSV(archivo, "artistas.csv")) {
        cout << "[ERROR] No se pudo abrir artistas.csv" << endl;
        return;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, pais;

        getline(ss, nombre, ';');
        getline(ss, pais, ';');

        if (!nombre.empty()) {
            artistas->insertar(nombre, pais);
        }
    }
    archivo.close();
}

// Cargar canciones
void Sistema::cargarCanciones() {
    ifstream archivo;
    string linea;

    if (abrirCSV(archivo, "canciones.csv")) {
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombreArtista, titulo, genero, sDuracion;

            getline(ss, nombreArtista, ';');
            getline(ss, titulo, ';');
            getline(ss, genero, ';');
            getline(ss, sDuracion, ';');

            if (!nombreArtista.empty()) {
                Artista *a = artistas->buscar(nombreArtista);
                if (a != nullptr) {
                    int duracion = 0;
                    if (convertirEnteroSeguro(sDuracion, duracion)) {
                        a->insertarCancion(titulo, genero, duracion);
                    } else {
                        cout << "[WARN] Cancion ignorada por duracion invalida: " << linea << endl;
                    }
                }
            }
        }
        archivo.close();
    }
}

// Cargar playlist
void Sistema::cargarPlayList() {
    ifstream archivo;
    string linea;

    if (abrirCSV(archivo, "playList.csv")) {
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string nombreUsuario, nombrePL, nombreArtista, nombreCancion;

            getline(ss, nombreUsuario, ';');
            getline(ss, nombrePL, ';');
            getline(ss, nombreArtista, ';');
            getline(ss, nombreCancion, ';');

            if (!nombreUsuario.empty()) {
                Usuario *u = usuarios->buscar(nombreUsuario);
                if (u != nullptr) {
                    Artista *a = artistas->buscar(nombreArtista);
                    if (a != nullptr) {
                        Cancion *c = a->buscarCancionPtr(nombreCancion);
                        if (c != nullptr) {
                            u->crearPlayList(nombrePL);
                            u->anadirCancionAPlayList(nombrePL, c);
                        }
                    }
                }
            }
        }
        archivo.close();
    }
}

// Mostrar usuarios
void Sistema::mostrarUsuarios() const {
    cout << "Usuarios registrados: " << usuarios->numElementos() << endl;
    usuarios->mostrar();
}

// Mostrar artistas
void Sistema::mostrarArtistas() const {
    cout << "Listado de Artistas y sus canciones:" << endl;
    artistas->mostrar();
}

// Compartir playlist
void Sistema::compartirPlayList(string nombreOrigen, string nombrePL, string nombreDestino) {
    nombreOrigen = limpiarExtremos(nombreOrigen);
    nombrePL = limpiarExtremos(nombrePL);
    nombreDestino = limpiarExtremos(nombreDestino);

    Usuario *emisor = usuarios->buscar(nombreOrigen);
    Usuario *receptor = usuarios->buscar(nombreDestino);

    if (emisor != nullptr && receptor != nullptr) {
        PlayList *copia = emisor->compartirPlayList(nombrePL);

        if (copia != nullptr) {
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

// Buscar usuario
void Sistema::buscarUsuario(string apellidosNombre) {
    apellidosNombre = limpiarExtremos(apellidosNombre);

    Usuario *u = usuarios->buscar(apellidosNombre);
    if (u != nullptr) {
        cout << "\n--------------------------------------" << endl;
        u->mostrar();
        u->mostrarFavoritos();
        u->reproducirPlayLists();
        cout << "--------------------------------------" << endl;
    } else {
        cout << "[!] El usuario '" << apellidosNombre << "' no existe en el sistema." << endl;
    }
}

// Buscar artista
void Sistema::buscarArtista(string nombre) {
    nombre = limpiarExtremos(nombre);

    Artista *a = artistas->buscar(nombre);
    if (a != nullptr) {
        cout << "\n--------------------------------------" << endl;
        a->mostrar();
        cout << "--------------------------------------" << endl;
    } else {
        cout << "[!] El artista '" << nombre << "' no existe en el sistema." << endl;
    }
}

// Eliminar playlist
void Sistema::eliminarPlayList(string nombreUsuario, string nombrePL) {
    nombreUsuario = limpiarExtremos(nombreUsuario);
    nombrePL = limpiarExtremos(nombrePL);

    Usuario *u = usuarios->buscar(nombreUsuario);
    if (u == nullptr) {
        cout << "[ERROR] El usuario '" << nombreUsuario << "' no existe." << endl;
        return;
    }

    if (u->eliminarPlayList(nombrePL)) {
        cout << "[SISTEMA] PlayList '" << nombrePL << "' eliminada de "
             << nombreUsuario << endl;
    } else {
        cout << "[ERROR] La PlayList '" << nombrePL << "' no existe para ese usuario." << endl;
    }
}

// Añadir artista favorito
void Sistema::anadirArtistaFavorito(string nombreUsuario, string nombreArtista) {
    nombreUsuario = limpiarExtremos(nombreUsuario);
    nombreArtista = limpiarExtremos(nombreArtista);

    Usuario *u = usuarios->buscar(nombreUsuario);
    Artista *a = artistas->buscar(nombreArtista);

    if (u == nullptr) {
        cout << "[ERROR] El usuario '" << nombreUsuario << "' no existe." << endl;
        return;
    }
    if (a == nullptr) {
        cout << "[ERROR] El artista '" << nombreArtista << "' no existe." << endl;
        return;
    }

    u->insertarArtistaFavorito(a);
    cout << "[SISTEMA] Artista '" << nombreArtista << "' anadido a favoritos de "
         << nombreUsuario << endl;
}

// Eliminar artista favorito
void Sistema::eliminarArtistaFavorito(string nombreUsuario, string nombreArtista) {
    nombreUsuario = limpiarExtremos(nombreUsuario);
    nombreArtista = limpiarExtremos(nombreArtista);

    Usuario *u = usuarios->buscar(nombreUsuario);
    if (u == nullptr) {
        cout << "[ERROR] El usuario '" << nombreUsuario << "' no existe." << endl;
        return;
    }

    u->eliminarArtistaFavorito(nombreArtista);
    cout << "[SISTEMA] Si existia, el artista '" << nombreArtista
         << "' se ha eliminado de favoritos de " << nombreUsuario << endl;
}

// Mostrar artista con más seguidores
void Sistema::mostrarArtistaConMasSeguidores() const {
    Artista *a = artistas->artistaConMasSeguidores();
    if (a != nullptr) {
        cout << "\nArtista con mas seguidores:" << endl;
        a->mostrar();
    } else {
        cout << "[!] No hay artistas en el sistema." << endl;
    }
}
