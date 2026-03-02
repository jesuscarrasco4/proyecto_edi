/*
 * Fecha.cpp
 *
 *  Created on: 16 feb 2026
 *      Author: estudiante
 */

#include "Fecha.h"

Fecha::Fecha(){
	dia = 1;
	mes= 1;
	year = 1;
}

Fecha::Fecha(int dia, int mes, int year){
	this->dia = dia;
	this->mes = mes;
	this->year = year;
}

void Fecha::setDia(int dia){
	this->dia = dia;
}

void Fecha::setMes(int mes){
	this->mes = mes;
}

void Fecha::setYear(int year){
	this->year = year;
}

Fecha::Fecha(Fecha &otraFecha){
	dia = otraFecha.dia;
	mes= otraFecha.mes;
	year = otraFecha.year;
}
int Fecha::getDia() const {
	return this->dia;
}

int Fecha::getMes() const {
	return this->mes;
}

int Fecha::getYear() const {
	return this->year;
}

void Fecha::mostrarF () const{
	cout <<"Día: " << this->dia <<endl
		 <<"Mes: " << this->mes <<endl
		 <<"Año: " << this->year <<endl;
}

//-- Dia del Mes --//
int Fecha::diasDelMes()const{
	int limite = 0;

	switch(mes){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 12:
		limite = 31;
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		limite = 30;
		break;

	case 2:
		if (anioBisiesto()) {
		        limite = 29;
		    } else {
		    	limite = 28;
		    }
		    break;

	default:
		limite = 0;
		break;
	}
	return limite;
}

//-- Año Bisiesto --//
bool Fecha::anioBisiesto() const {
    // Un año es bisiesto si:
    // (Es divisible por 4 Y NO por 100) O (Es divisible por 400)
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


Fecha::~Fecha(){
}

string Fecha::pasarCadena() const {
    // Convertimos los enteros a string y los concatenamos
    return to_string(dia) + "/" + to_string(mes) + "/" + to_string(year);
}
