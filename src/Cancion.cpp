/*
 * Cancion.cpp
 *
 *  Created on: 2 mar 2026
 *      Author: estudiante
 */

#include "Cancion.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Constructor por defecto
Cancion::Cancion() {
    titulo = "";
    genero = "";
    duracion = 0;
}

// Constructor parametrizado
Cancion::Cancion(string nombre, string pais, int numeroSeguidores) {
    this->titulo = nombre;
    this->genero = pais;
    this->duracion = numeroSeguidores;
}

// Constructor de copia
Cancion::Cancion(const Cancion &otroCancion) {
    titulo = otroCancion.titulo;
    genero = otroCancion.genero;
    duracion = otroCancion.duracion;
}

// Setters
void Cancion::setTitulo(string titulo) { this->titulo = titulo; }
void Cancion::setGenero(string genero) { this->genero = genero; }
void Cancion::setDuracion(int duracion) { this->duracion = duracion; }

// Destructor
Cancion::~Cancion() {
	// TODO Auto-generated destructor stub
}

// Getters
string Cancion::getTitulo() const { return this->titulo; }
string Cancion::getGenero() const { return this->genero; }
int Cancion::getDuracion() const { return this->duracion; }

// Mostrar
void Cancion::mostrar() const {
    cout << "Titulo: " << this->titulo << endl;
    cout << "Genero: " << this->genero << endl;
    cout << "Duracion: " << this->duracion << endl;
}

// Sobrecargar con el operador '=='
bool Cancion::operator==(const Cancion &otro) const {
	return this->titulo == otro.titulo;
}

// Sobrecarga con el operador '<'
bool Cancion::operator<(const Cancion &otro) const {
	return this->titulo < otro.titulo;
}






