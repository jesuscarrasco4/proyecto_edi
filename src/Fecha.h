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
	Fecha (int dia, int mes, int year);
	Fecha (Fecha &otraFecha);
	~Fecha ();

	// Getter
	int getDia () const;
	int getMes () const;
	int getYear () const;

	// Setter
	void setDia (int dia);
	void setMes (int mes);
	void setYear (int year);

	int diasDelMes() const;
	bool anioBisiesto() const;
	void mostrarF () const;
	string pasarCadena() const;
};

#endif /* FECHA_H_ */
