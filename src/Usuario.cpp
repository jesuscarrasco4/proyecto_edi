#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Constructor por defecto
Usuario::Usuario() {
    idUsuario = "";
    apellidosNombre = "";
    email = "";
    contrasena = "";
    fechaNac = new Fecha();
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

// Constructor parametrizado
Usuario::Usuario(string id, string nombre, string email, string contrasena, int dia, int mes, int anio) {
    this->idUsuario = id;
    this->apellidosNombre = nombre;
    this->email = email;
    this->contrasena = contrasena;
    this->fechaNac = new Fecha(dia, mes, anio);
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

// Constructor por copia
Usuario::Usuario(const Usuario &otroUsuario) {
    idUsuario = otroUsuario.idUsuario;
    apellidosNombre = otroUsuario.apellidosNombre;
    email = otroUsuario.email;
    contrasena = otroUsuario.contrasena;

    if (otroUsuario.fechaNac != nullptr) {
        this->fechaNac = new Fecha(*(otroUsuario.fechaNac));
    } else {
        this->fechaNac = nullptr;
    }

    this->lPlayLists = new ListaDPI<PlayList*>();
    otroUsuario.lPlayLists->moverPrimero();
    while (!otroUsuario.lPlayLists->alFinal()) {
        PlayList *copiaPL = new PlayList(*(otroUsuario.lPlayLists->consultar()));
        lPlayLists->insertar(copiaPL);
        otroUsuario.lPlayLists->avanzar();
    }

    this->lArtistasFavoritos = new ListaDPI<Artista*>();
    otroUsuario.lArtistasFavoritos->moverPrimero();
    while (!otroUsuario.lArtistasFavoritos->alFinal()) {
        lArtistasFavoritos->insertar(otroUsuario.lArtistasFavoritos->consultar());
        otroUsuario.lArtistasFavoritos->avanzar();
    }
}

// Setter
void Usuario::setIdUsuario(string idUsuario) { this->idUsuario = idUsuario; }

// Setter
void Usuario::setApellidosNombre(string apellidosNombre) { this->apellidosNombre = apellidosNombre; }

// Setter
void Usuario::setEmail(string email) { this->email = email; }

// Setter
void Usuario::setContrasena(string contrasena) { this->contrasena = contrasena; }

// Getter
string Usuario::getApellidosNombre() const { return this->apellidosNombre; }

// Getter
string Usuario::getIdUsuario() const { return this->idUsuario; }

// Getter
string Usuario::getEmail() const { return this->email; }

// Getter
string Usuario::getContrasena() const { return this->contrasena; }

// Getter
Fecha* Usuario::getFechaNac() const { return this->fechaNac; }

// Mostrar
void Usuario::mostrar() const {
    cout << "ID: " << this->idUsuario << endl;
    cout << "Nombre: " << this->apellidosNombre << endl;
    cout << "Email: " << this->email << endl;
    if (fechaNac) {
        cout << "Fecha Nacimiento: " << fechaNac->pasarCadena() << endl;
    }
}

// Pasar a cadena
string Usuario::pasarACadena() const {
    string cad = this->idUsuario + " " + this->apellidosNombre + " " +
                 this->email + " " + this->contrasena;
    if (fechaNac) cad += " " + fechaNac->pasarCadena();
    return cad;
}

// Destructor
Usuario::~Usuario() {
    delete fechaNac;

    lPlayLists->moverPrimero();
    while (!lPlayLists->estaVacia()) {
        delete lPlayLists->consultar();
        lPlayLists->eliminar();
    }
    delete lPlayLists;

    delete lArtistasFavoritos;
}

// Crear PlayList
void Usuario::crearPlayList(string nombre){
    bool existe = false;
    lPlayLists->moverPrimero();

    while(!lPlayLists->alFinal() && !existe){
        if (lPlayLists->consultar()->getNombre() == nombre) {
            existe = true;
        }else{
            lPlayLists->avanzar();
        }
    }

    if(!existe){
        PlayList *nueva = new PlayList(nombre);
        lPlayLists->insertar(nueva);
    }
}

// Eliminar PlayList
bool Usuario::eliminarPlayList(string nombre) {
    bool eliminada = false;
    lPlayLists->moverPrimero();

    while (!lPlayLists->alFinal() && !eliminada) {
        if (lPlayLists->consultar()->getNombre() == nombre) {
            PlayList *pl = lPlayLists->consultar();
            delete pl;
            lPlayLists->eliminar();
            eliminada = true;
        } else {
            lPlayLists->avanzar();
        }
    }

    return eliminada;
}

// Añadir cancion a Playlist
void Usuario::anadirCancionAPlayList(string nombrePL, Cancion *c) {
    bool encontrada = false;
    lPlayLists->moverPrimero();

    while (!lPlayLists->alFinal() && !encontrada) {
        if (lPlayLists->consultar()->getNombre() == nombrePL) {
            encontrada = true;
            lPlayLists->consultar()->agregarCancion(c);
        } else {
            lPlayLists->avanzar();
        }
    }
}

// Reproducir PlayLists
void Usuario::reproducirPlayLists() {
    cout << "Reproduciendo todas las PlayLists de: " << apellidosNombre << endl;

    if (lPlayLists->estaVacia()) {
        cout << "  (No hay PlayLists para reproducir)" << endl;
    } else {
        lPlayLists->moverPrimero();
        while (!lPlayLists->alFinal()) {
            lPlayLists->consultar()->reproducirTodo();
            lPlayLists->avanzar();
        }
    }
}

// Compartir PlayList
PlayList* Usuario::compartirPlayList(string nombrePL) {
    PlayList *copia = nullptr;
    bool encontrada = false;
    lPlayLists->moverPrimero();

    while (!lPlayLists->alFinal() && !encontrada) {
        if (lPlayLists->consultar()->getNombre() == nombrePL) {
            encontrada = true;
            copia = new PlayList(*(lPlayLists->consultar()));
        } else {
            lPlayLists->avanzar();
        }
    }
    return copia;
}

// Añadir PlayList compartida
void Usuario::anadirPlayListCompartida(PlayList *pl) {
    if (pl != nullptr) {
        lPlayLists->insertar(pl);
    }
}

// Mostrar favoritos
void Usuario::mostrarFavoritos() const {
    cout << "Favoritos de " << apellidosNombre << ":" << endl;
    if (lArtistasFavoritos->estaVacia()) {
        cout << "  (Lista vacia)" << endl;
    } else {
        lArtistasFavoritos->moverPrimero();
        while (!lArtistasFavoritos->alFinal()) {
            cout << "  - " << lArtistasFavoritos->consultar()->getNombre() << endl;
            lArtistasFavoritos->avanzar();
        }
    }
}

// Eliminar artista favorito
void Usuario::eliminarArtistaFavorito(string nombreA) {
    bool encontrado = false;
    lArtistasFavoritos->moverPrimero();

    while (!lArtistasFavoritos->alFinal() && !encontrado) {
        if (lArtistasFavoritos->consultar()->getNombre() == nombreA) {
            encontrado = true;
            lArtistasFavoritos->consultar()->decrementarSeguidores();
            lArtistasFavoritos->eliminar();
        } else {
            lArtistasFavoritos->avanzar();
        }
    }
}

// Insertar artista favorito
void Usuario::insertarArtistaFavorito(Artista * a){
    if(a !=nullptr){
        bool existe = false;
        lArtistasFavoritos->moverPrimero();
        while(!lArtistasFavoritos->alFinal() && !existe){
            if(lArtistasFavoritos->consultar()->getNombre() == a->getNombre()){
                existe = true;
            }else{
                lArtistasFavoritos->avanzar();
            }
        }
        if(!existe){
            lArtistasFavoritos->insertar(a);
            a->incrementarSeguidores();
        }
    }
}

// Cargar usuarios
void cargarUsuarios(Usuario* usuariosArchivo[], int &numUsuarios) {
    numUsuarios = 0;

    ifstream archivo("../usuarios.csv");
    if (!archivo.is_open()) {
        cerr << "ERROR: No encuentro el archivo usuarios.csv en la ruta actual." << endl;
    }

    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea);

        while (getline(archivo, linea) && numUsuarios < MAX) {
            stringstream extractorDeDatos(linea);
            string id, nombre, email, pass, sDia, sMes, sAnio;

            getline(extractorDeDatos, id, ';');
            getline(extractorDeDatos, nombre, ';');
            getline(extractorDeDatos, email, ';');
            getline(extractorDeDatos, pass, ';');

            getline(extractorDeDatos, sDia, '/');
            getline(extractorDeDatos, sMes, '/');
            getline(extractorDeDatos, sAnio, ';');

            if (!id.empty()) {
                usuariosArchivo[numUsuarios] = new Usuario(id, nombre, email, pass,
                                               stoi(sDia), stoi(sMes), stoi(sAnio));
                numUsuarios++;
            }
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el fichero usuarios.csv" << endl;
    }
}

// Mostrar usuarios
void mostrarUsuarios(TVector usuarios, int numUsuarios) {
    cout << "--- Listado de Usuarios Cargados (" << numUsuarios << ") ---" << endl;
    for (int i = 0; i < numUsuarios; i++) {
        cout << "[" << i + 1 << "] ";
        usuarios[i]->mostrar();
        cout << "-----------------------" << endl;
    }
}

// Destruir usuarios
void destruirUsuarios(TVector usuarios, int &numUsuarios) {
    for (int i = 0; i < numUsuarios; i++) {
        delete usuarios[i];
        usuarios[i] = nullptr;
    }
    numUsuarios = 0;
    cout << "Memoria liberada correctamente." << endl;
}

// Guardar usuarios por año
void guardarUsuariosPorAnio(TVector usuarios, int numUsuarios, int anioFiltro) {
    ofstream fSal;
    fSal.open("usuarios_out.csv");

    if (fSal.is_open()) {
        fSal << "idUsuario;apellidos y nombre;email;contraseña;dia/mes/año" << endl;

        for (int i = 0; i < numUsuarios; i++) {
            if (usuarios[i]->getFechaNac() != nullptr && usuarios[i]->getFechaNac()->getYear() == anioFiltro) {
                fSal << usuarios[i]->pasarACadena() << endl;
            }
        }
        fSal.close();
        cout << "Fichero 'usuarios_out.csv' generado para el año " << anioFiltro << endl;
    } else {
        cerr << "Error al crear el fichero de salida." << endl;
    }
}
