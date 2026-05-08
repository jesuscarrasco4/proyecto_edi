/*
 * PlayList.h
 *
 *  Created on: 8 mar 2026
 *      Author: estudiante
 */

#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <iostream>
#include <string> // Importante para usar string
using namespace std;
#include "Cola.h"
#include "Cancion.h"

class PlayList {
private:
	string nombre;
	int numeroCanciones;
	int totalDuracion;
	Cola <Cancion *> *colaReproduccion;

public:
	// PRE: ---
	// DESC: Construye una playlist vacia.
	// COMPLEJIDAD: O(1)
	PlayList();
	// PRE: nombre puede ser cualquier cadena.
	// DESC: Construye una playlist vacia con el nombre indicado.
	// COMPLEJIDAD: O(1)
	PlayList(string nombre);
	// PRE: ---
	// DESC: Crea una copia de la cola de canciones (agregacion: copia punteros, no canciones).
	// COMPLEJIDAD: O(n), siendo n el numero de canciones.
	PlayList(const PlayList &otraPlayList);
	virtual ~PlayList();

   // --  GETTERS / SETTERS  -- //
	string getNombre() const;
	void setNombre(string nombre);
	int getNumCanciones() const;
    int getDuracion() const;

    // --  METODOS DE COLA  -- //
    void agregarCancion(Cancion *c);
    void eliminarCancion();

    // --  MOSTRAR  -- //
    void mostrar() const;
    void reproducirTodo();
    // PRE: posicion > 0
    // DESC: Reproduce de forma circular a partir de la posicion indicada sin perder datos.
    // COMPLEJIDAD: O(n), siendo n el numero de canciones.
    void reproducirAPartir(int posicion);

};

#endif /* PLAYLIST_H_ */
