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
    fechaNac = new Fecha(); // Reserva dinámica obligatoria
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

// Constructor parametrizado (Actualizado para Sesión 3)
Usuario::Usuario(string id, string nombre, string email, string contrasena, int dia, int mes, int anio) {
    this->idUsuario = id;
    this->apellidosNombre = nombre;
    this->email = email;
    this->contrasena = contrasena;
    // Reserva de memoria para el objeto Fecha
    this->fechaNac = new Fecha(dia, mes, anio);
    //Reservamos memoria para las nuevas listas
    lPlayLists = new ListaDPI<PlayList*>();
    lArtistasFavoritos = new ListaDPI<Artista*>();
}

// Constructor de copia
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

    // 1. Copia de PlayLists (Composición -> Copia profunda)
    this->lPlayLists = new ListaDPI<PlayList*>();
    otroUsuario.lPlayLists->moverPrimero();
    while (!otroUsuario.lPlayLists->alFinal()) {
        // Usamos el constructor de copia de PlayList
        PlayList *copiaPL = new PlayList(*(otroUsuario.lPlayLists->consultar()));
        lPlayLists->insertar(copiaPL);
        otroUsuario.lPlayLists->avanzar();
    }

    // 2. Copia de Favoritos (Agregación -> Copia de punteros)
    this->lArtistasFavoritos = new ListaDPI<Artista*>();
    otroUsuario.lArtistasFavoritos->moverPrimero();
    while (!otroUsuario.lArtistasFavoritos->alFinal()) {
        // Solo copiamos el puntero, no creamos un nuevo Artista
        lArtistasFavoritos->insertar(otroUsuario.lArtistasFavoritos->consultar());
        otroUsuario.lArtistasFavoritos->avanzar();
    }
}

// Setters
void Usuario::setIdUsuario(string idUsuario) { this->idUsuario = idUsuario; }
void Usuario::setApellidosNombre(string apellidosNombre) { this->apellidosNombre = apellidosNombre; }
void Usuario::setEmail(string email) { this->email = email; }
void Usuario::setContrasena(string contrasena) { this->contrasena = contrasena; }

// Getters
string Usuario::getApellidosNombre() const { return this->apellidosNombre; }
string Usuario::getIdUsuario() const { return this->idUsuario; }
string Usuario::getEmail() const { return this->email; }
string Usuario::getContrasena() const { return this->contrasena; }
Fecha* Usuario::getFechaNac() const { return this->fechaNac; }


void Usuario::mostrar() const {
    cout << "ID: " << this->idUsuario << endl;
    cout << "Nombre: " << this->apellidosNombre << endl;
    cout << "Email: " << this->email << endl;
    if (fechaNac) {
        cout << "Fecha Nacimiento: " << fechaNac->pasarCadena() << endl;
    }
}

string Usuario::pasarACadena() const {
    string cad = this->idUsuario + " " + this->apellidosNombre + " " +
                 this->email + " " + this->contrasena;
    if (fechaNac) cad += " " + fechaNac->pasarCadena();
    return cad;
}

// Destructor: Libera la memoria de la fecha
Usuario::~Usuario() {
    delete fechaNac;

    // 1. Borrar PlayLists (Composición: somos dueños)
    lPlayLists->moverPrimero();
    while (!lPlayLists->estaVacia()) {
        delete lPlayLists->consultar();
        lPlayLists->eliminar();
    }
    delete lPlayLists;

    // 2. Borrar Favoritos (Agregación: NO somos dueños de los artistas)
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

// Añadir Cancion a Playlist
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

// Reproducir PlayList
void Usuario::reproducirPlayLists() {
    cout << "Reproduciendo todas las PlayLists de: " << apellidosNombre << endl;

    if (lPlayLists->estaVacia()) {
        cout << "  (No hay PlayLists para reproducir)" << endl;
    } else {
        lPlayLists->moverPrimero();
        while (!lPlayLists->alFinal()) {
            // Cada PlayList se encarga de su propia reproduccion
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
            // Usamos el constructor de copia de PlayList para no compartir punteros [cite: 79, 138, 139]
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

// Eliminar Artista Favorito
void Usuario::eliminarArtistaFavorito(string nombreA) {
    bool encontrado = false;
    lArtistasFavoritos->moverPrimero();

    while (!lArtistasFavoritos->alFinal() && !encontrado) {
        if (lArtistasFavoritos->consultar()->getNombre() == nombreA) {
            encontrado = true;
            lArtistasFavoritos->consultar()->decrementarSeguidores();
            // Solo eliminamos el nodo de la lista (el puntero)
            lArtistasFavoritos->eliminar();
        } else {
            lArtistasFavoritos->avanzar();
        }
    }
}

//Insertar Artista Favorito
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



// Funciones Globales //

void cargarUsuarios(Usuario* usuariosArchivo[], int &numUsuarios) {
    numUsuarios = 0;

    ifstream archivo("../usuarios.csv");
    if (!archivo.is_open()) {
        // Esto te dirá si el programa no encuentra el archivo
        cerr << "ERROR: No encuentro el archivo usuarios.csv en la ruta actual." << endl;
    }

    string linea;

    if (archivo.is_open()) {
        getline(archivo, linea); // Ignorar cabecera

        while (getline(archivo, linea) && numUsuarios < MAX) {
            stringstream extractorDeDatos(linea);
            string id, nombre, email, pass, sDia, sMes, sAnio;

            // Extracción por delimitadores
            getline(extractorDeDatos, id, ';');
            getline(extractorDeDatos, nombre, ';');
            getline(extractorDeDatos, email, ';');
            getline(extractorDeDatos, pass, ';');

            // La fecha viene como dia/mes/anio
            getline(extractorDeDatos, sDia, '/');
            getline(extractorDeDatos, sMes, '/');
            getline(extractorDeDatos, sAnio, ';');

            // Convertir y crear objeto con 'new'
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

void mostrarUsuarios(TVector usuarios, int numUsuarios) {
    cout << "--- Listado de Usuarios Cargados (" << numUsuarios << ") ---" << endl;
    for (int i = 0; i < numUsuarios; i++) {
        cout << "[" << i + 1 << "] ";
        usuarios[i]->mostrar(); // Llamamos al mostrar de cada objeto Usuario
        cout << "-----------------------" << endl;
    }
}

void destruirUsuarios(TVector usuarios, int &numUsuarios) {
    for (int i = 0; i < numUsuarios; i++) {
        delete usuarios[i];    // Esto llama al destructor de Usuario y luego al de Fecha
        usuarios[i] = nullptr; // Buena práctica para evitar punteros "colgantes"
    }
    numUsuarios = 0; // Reiniciamos el contador
    cout << "Memoria liberada correctamente." << endl;
}

void guardarUsuariosPorAnio(TVector usuarios, int numUsuarios, int anioFiltro) {
    ofstream fSal;
    fSal.open("usuarios_out.csv");

    if (fSal.is_open()) {
        fSal << "idUsuario;apellidos y nombre;email;contraseña;dia/mes/año" << endl; // Cabecera

        for (int i = 0; i < numUsuarios; i++) {
            // Suponiendo que has añadido un getter en Usuario para obtener el año
            // o que puedes acceder a la fecha
        	if (usuarios[i]->getFechaNac() != nullptr && usuarios[i]->getFechaNac()->getYear() == anioFiltro) {
        	    fSal << usuarios[i]->pasarACadena() << endl;
        	}
        }
        fSal.close(); // [cite: 21]
        cout << "Fichero 'usuarios_out.csv' generado para el año " << anioFiltro << endl;
    } else {
        cerr << "Error al crear el fichero de salida." << endl;
    }
}

// --- --- --- --- --- --- --- --- --- --- --- --- //
