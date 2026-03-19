/*
 * Artista.cpp
 *
 *  Created on: 2 mar 2026
 *      Author: estudiante
 */

#include "Artista.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Constructor por defecto
Artista::Artista() {
    nombre = "";
    pais = "";
    numeroSeguidores = 0;
}

// Constructor parametrizado
Artista::Artista(string nombre, string pais, int numeroSeguidores) {
    this->nombre = nombre;
    this->pais = pais;
    this->numeroSeguidores = numeroSeguidores;
}

// Constructor de copia
Artista::Artista(const Artista &otro) {
    this->nombre = otro.nombre;
    this->pais = otro.pais;
    this->numeroSeguidores = otro.numeroSeguidores;
    this->lCanciones = new ListaDPI<Cancion*>();

    otro.lCanciones->moverPrimero();
    while (!otro.lCanciones->alFinal()) {
        // Clonamos cada canción del artista original
        Cancion *copiaC = new Cancion(*(otro.lCanciones->consultar()));
        this->lCanciones->insertar(copiaC);
        otro.lCanciones->avanzar();
    }
}

// Destructor
Artista::~Artista() {
	lCanciones->moverPrimero();
	while(!lCanciones->estaVacia()){
		Cancion *aux = lCanciones->consultar();
		delete aux;
		lCanciones->eliminar();
	}
	delete lCanciones;
}

// Setters
void Artista::setNombre(string nombre) { this->nombre = nombre; }
void Artista::setPais(string pais) { this->pais = pais; }
void Artista::setNumeroSeguidores(int numeroSeguidores) { this->numeroSeguidores = numeroSeguidores; }

// Getters
string Artista::getNombre() const { return this->nombre; }
string Artista::getPais() const { return this->pais; }
int Artista::getNumeroSeguidores() const { return this->numeroSeguidores; }


// - Mostrar - //
void Artista::mostrar() const {
    cout << "Nombre: " << this->nombre << endl;
    cout << "Pais: " << this->pais << endl;
    cout << "Numero de Seguidores: " << this->numeroSeguidores << endl;
}

// - Sobrecargar con el operador '==' - //
bool Artista::operator==(const Artista &otro) const {
	return this->nombre == otro.nombre;
}

// - Sobrecarga con el operador '<' - //
bool Artista::operator<(const Artista &otro) const {
	return this->nombre < otro.nombre;
}

void Artista::insertarCancion(string titulo, string genero, int duracion) {
    lCanciones->moverPrimero();
    bool encontrado = false;

    // Buscar posición u homónimo
    while (!lCanciones->alFinal() && !encontrado) {
        if (lCanciones->consultar()->getTitulo() >= titulo) {
            encontrado = true;
        } else {
            lCanciones->avanzar();
        }
    }

    // Si no es duplicado, insertamos [cite: 219]
    if (!encontrado || lCanciones->consultar()->getTitulo() != titulo) {
        Cancion *nueva = new Cancion(titulo, genero, duracion);
        lCanciones->insertar(nueva);
    }
}

bool Artista::buscarCancion(string titulo, Cancion &c) {
    bool encontrada = false;
    lCanciones->moverPrimero(); // Siempre empezamos desde el principio de la lista

    // Recorremos la lista con el Punto de Interés (DPI)
    while (!lCanciones->alFinal() && !encontrada) {
        // Consultamos la canción actual
        Cancion *aux = lCanciones->consultar();

        if (aux->getTitulo() == titulo) {
            encontrada = true;
            c = *aux; // Copiamos los datos del objeto encontrado en el parámetro de salida
        } else {
            lCanciones->avanzar(); // Movemos el DPI al siguiente nodo
        }
    }

    return encontrada;
}


