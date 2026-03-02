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
}

// Constructor parametrizado (Actualizado para Sesión 3)
Usuario::Usuario(string id, string nombre, string email, string contrasena, int dia, int mes, int anio) {
    this->idUsuario = id;
    this->apellidosNombre = nombre;
    this->email = email;
    this->contrasena = contrasena;
    // Reserva de memoria para el objeto Fecha
    this->fechaNac = new Fecha(dia, mes, anio);
}

// Constructor de copia: Copia profunda
Usuario::Usuario(const Usuario &otroUsuario) {
    idUsuario = otroUsuario.idUsuario;
    apellidosNombre = otroUsuario.apellidosNombre;
    email = otroUsuario.email;
    contrasena = otroUsuario.contrasena;

    if (otroUsuario.fechaNac != nullptr) {
        // Creamos una nueva instancia de Fecha basada en la original
        this->fechaNac = new Fecha(*(otroUsuario.fechaNac));
    } else {
        this->fechaNac = nullptr;
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
}

// --- Gestión de Ficheros ---

void cargarUsuarios(Usuario* usuariosArchivo[], int &numUsuarios) {
    numUsuarios = 0;

    ifstream archivo("usuarios.csv");
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
