/*
 * Fecha.h
 *
 *  Created on: 16 feb 2026
 *      Author: estudiante
 */

#ifndef FECHA_H_
#define FECHA_H_

#include <iostream>
#include <string>
using namespace std;

class Fecha {
private:
	int dia;
	int mes;
	int year;

public:
	Fecha();
	void setDia (int dia);
	void setMes (int mes);
	void setYear (int year);

	//-- Dia del Mes --//
	int diasDelMes() const;

	//-- Año Bisiesto 'Si o No' --//
	bool anioBisiesto() const;


	Fecha (int dia, int mes, int year);
	Fecha (Fecha &otraFecha);
	int getDia () const;
	int getMes () const;
	int getYear () const;


	~Fecha ();

	void mostrarF () const;
	string pasarCadena() const;
};


#endif /* FECHA_H_ */
