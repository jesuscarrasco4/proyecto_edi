/*
 * Cancion.h
 *
 *  Created on: 2 mar 2026
 *      Author: estudiante
 */

#ifndef CANCION_H_
#define CANCION_H_

#include <string>
#include <iostream>
using namespace std;

class Cancion {
private:
    std::string titulo;
    std::string genero;
    int duracion;

public:
    string getTitulo() const;
    string getGenero() const;
    int getDuracion() const;

    Cancion();
    Cancion(string titulo, string genero, int duracion);
    Cancion(const Cancion &otroCancion);

	void setTitulo(string titulo);
	void setGenero(string genero);
	void setDuracion(int duracion);

	void mostrar() const;

    virtual ~Cancion();

    bool operator==(const Cancion &otro) const; // Por nombre
    bool operator<(const Cancion &otro) const;  // Orden alfabético
};

#endif /* CANCION_H_ */
