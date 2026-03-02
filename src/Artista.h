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

class Artista {
private:
    std::string nombre;
    std::string pais;
    int numeroSeguidores;

public:
    string getNombre() const;
    string getPais() const;
    int getNumeroSeguidores() const;

    Artista();
    Artista(string nombre, string pais, int numeroSeguidores);
    Artista(const Artista &otroArtista);

	void setNombre(string nombre);
	void setPais(string pais);
	void setNumeroSeguidores(int numeroSeguidores);

	void mostrar() const;

    virtual ~Artista();

    // Sobrecarga de operadores
    bool operator==(const Artista &otro) const; // Por nombre
    bool operator<(const Artista &otro) const;  // Orden alfabético
};

#endif /* ARTISTA_H_ */
