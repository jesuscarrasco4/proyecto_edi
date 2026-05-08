/*
 * Artista.h
 *
 *  Created on: 2 mar 2026
 *      Author: estudiante
 */

#ifndef ARTISTA_H_
#define ARTISTA_H_

#include <string>
#include <iostream>
using namespace std;
#include "ListaDPI.h"
#include "Cancion.h"

class Artista {
private:
    std::string nombre;
    std::string pais;
    int numeroSeguidores;
    ListaDPI<Cancion*> *lCanciones;

public:

    string getNombre() const;
    string getPais() const;
    int getNumeroSeguidores() const;
    int numCanciones() const;

    Artista();
    Artista(string nombre, string pais, int numeroSeguidores);
    Artista(const Artista &otroArtista);

	void setNombre(string nombre);
	void setPais(string pais);
	void setNumeroSeguidores(int numeroSeguidores);

	void mostrar() const;

    virtual ~Artista();

    bool operator==(const Artista &otro) const; // Por nombre
    bool operator<(const Artista &otro) const;  // Orden alfabético

    void insertarCancion(string titulo, string genero, int duracion);
    bool buscarCancion(string titulo, Cancion &c);
    Cancion* buscarCancionPtr(const string &titulo) const;
    void incrementarSeguidores();
    void decrementarSeguidores();
};

#endif /* ARTISTA_H_ */
