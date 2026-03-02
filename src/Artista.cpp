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
Artista::Artista(const Artista &otroArtista) {
    nombre = otroArtista.nombre;
    pais = otroArtista.pais;
    numeroSeguidores = otroArtista.numeroSeguidores;
}

// Setters
void Artista::setNombre(string nombre) { this->nombre = nombre; }
void Artista::setPais(string pais) { this->pais = pais; }
void Artista::setNumeroSeguidores(int numeroSeguidores) { this->numeroSeguidores = numeroSeguidores; }

// Getters
string Artista::getNombre() const { return this->nombre; }
string Artista::getPais() const { return this->pais; }
int Artista::getNumeroSeguidores() const { return this->numeroSeguidores; }


Artista::~Artista() {
	// TODO Auto-generated destructor stub
}

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






