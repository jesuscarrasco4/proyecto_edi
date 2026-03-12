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
    this->nombre = "";
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

	//PAsamos de 'otra' PlayList a la 'aux'
	while (!otraPlayList.colaReproduccion->estaVacia()) {
        c = otraPlayList.colaReproduccion->getPrimero();
	    this->colaReproduccion->encolar(c);
	    aux.encolar(c);
        otraPlayList.colaReproduccion->desencolar();
	}
	while(!aux.estaVacia()){
		otraPlayList.colaReproduccion->encolar(aux.getPrimero());
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


