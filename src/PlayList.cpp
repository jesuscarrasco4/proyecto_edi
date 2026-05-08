/*
 * PlayList.cpp
 *
 *  Created on: 8 mar 2026
 *      Author: estudiante
 */

#include "PlayList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Constructor por Defecto
PlayList::PlayList() {
    this->nombre = "";
    this->numeroCanciones = 0;
    this->totalDuracion = 0;
    this->colaReproduccion = new Cola<Cancion*>();     //Inicializamos la Cola
}

// Constructor Parametrizado
PlayList::PlayList(string nombre){
    this->nombre = nombre;
    this->numeroCanciones = 0;
    this->totalDuracion = 0;
    this->colaReproduccion = new Cola<Cancion*>();    //Inicializamos la Cola
}

// Constructor por Copia
PlayList::PlayList(const PlayList &otraPlayList){
	this->nombre = otraPlayList.nombre;
	this->numeroCanciones = otraPlayList.numeroCanciones;
	this->totalDuracion = otraPlayList.totalDuracion;
	this->colaReproduccion = new Cola<Cancion*>();    //Inicializamos la Cola

	Cola<Cancion*> aux;
	Cancion* c;
	Cola<Cancion*> *origen = const_cast<Cola<Cancion*> *>(otraPlayList.colaReproduccion);

	// Recorremos la cola origen restaurandola al final para mantener su estado.
	while (!origen->estaVacia()) {
        c = origen->getPrimero();
	    this->colaReproduccion->encolar(c);
	    aux.encolar(c);
        origen->desencolar();
	}
	while(!aux.estaVacia()){
		origen->encolar(aux.getPrimero());
		aux.desencolar();
	}
}

// Destructor
PlayList::~PlayList() {
	delete colaReproduccion;
}

// Agregar Cancion
void PlayList::agregarCancion(Cancion *c){
	if (c != nullptr){
		colaReproduccion->encolar(c);
		numeroCanciones++;	// Sumamos 1 unidad por la cancion añadida
		totalDuracion += c->getDuracion();	// Acumulamos la duracion de la cancion
	}
}

// Eliminar Cancion
void PlayList::eliminarCancion() {
    if (!colaReproduccion->estaVacia()) {
        Cancion* primero = colaReproduccion->getPrimero();
        totalDuracion -= primero->getDuracion(); // Restamos duración
        numeroCanciones--;

        colaReproduccion->desencolar();
    }
}

void PlayList::reproducirTodo() {
    if (colaReproduccion->estaVacia()) {
        cout << "La PlayList " << nombre << " esta vacia." << endl;
    } else {
        cout << "--- Reproduciendo PlayList: " << nombre << " ---" << endl;
        Cola<Cancion*> aux;
        while (!colaReproduccion->estaVacia()) {
            Cancion *actual = colaReproduccion->getPrimero();
            actual->mostrar();
            aux.encolar(actual);
            colaReproduccion->desencolar();
        }
        while (!aux.estaVacia()) {
            colaReproduccion->encolar(aux.getPrimero());
            aux.desencolar();
        }
    }
}

void PlayList::reproducirAPartir(int posicion) {
    if (colaReproduccion->estaVacia()) {
        cout << "La PlayList " << nombre << " esta vacia." << endl;
        return;
    }
    if (posicion <= 0 || posicion > numeroCanciones) {
        cout << "Posicion de inicio invalida para la PlayList " << nombre << "." << endl;
        return;
    }

    Cola<Cancion*> aux;
    int indice = 1;

    // Rotamos la cola hasta situar en primer lugar la posicion deseada.
    while (!colaReproduccion->estaVacia()) {
        Cancion *actual = colaReproduccion->getPrimero();
        colaReproduccion->desencolar();
        if (indice < posicion) {
            colaReproduccion->encolar(actual);
        } else {
            aux.encolar(actual);
        }
        indice++;
    }
    while (!aux.estaVacia()) {
        colaReproduccion->encolar(aux.getPrimero());
        aux.desencolar();
    }

    cout << "--- Reproduciendo PlayList desde posicion " << posicion << ": " << nombre << " ---" << endl;
    reproducirTodo();
}

void PlayList::setNombre(string nombre) {
    this->nombre = nombre;
}

void PlayList::mostrar() const {
    cout << "PlayList: " << nombre << endl;
    cout << "Numero de canciones: " << numeroCanciones << endl;
    cout << "Duracion total: " << totalDuracion << " segundos" << endl;
}

//Getters
string PlayList::getNombre() const {
	return nombre;
}
int PlayList::getNumCanciones() const {
    return this->numeroCanciones;
}
int PlayList::getDuracion() const {
    return this->totalDuracion;
}

