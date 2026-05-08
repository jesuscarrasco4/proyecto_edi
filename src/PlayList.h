#ifndef PLAYLIST_H_
#define PLAYLIST_H_

#include <iostream>
#include <string>
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

	// Getter
	string getNombre() const;
	int getNumCanciones() const;
	int getDuracion() const;

	// Setter
	void setNombre(string nombre);

	void agregarCancion(Cancion *c);
	void eliminarCancion();
	void mostrar() const;
	void reproducirTodo();
	void reproducirAPartir(int posicion);
};

#endif /* PLAYLIST_H_ */
