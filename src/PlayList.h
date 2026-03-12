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
	PlayList();
	PlayList(string nombre);
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
    void reproducirAPartir(int posicion);

};

#endif /* PLAYLIST_H_ */
