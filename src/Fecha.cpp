#include "Fecha.h"

// Constructor por defecto
Fecha::Fecha(){
	dia = 1;
	mes= 1;
	year = 1;
}

// Constructor parametrizado
Fecha::Fecha(int dia, int mes, int year){
	this->dia = dia;
	this->mes = mes;
	this->year = year;
}

// Setter
void Fecha::setDia(int dia){
	this->dia = dia;
}

// Setter
void Fecha::setMes(int mes){
	this->mes = mes;
}

// Setter
void Fecha::setYear(int year){
	this->year = year;
}

// Constructor por copia
Fecha::Fecha(Fecha &otraFecha){
	dia = otraFecha.dia;
	mes= otraFecha.mes;
	year = otraFecha.year;
}

// Getter
int Fecha::getDia() const {
	return this->dia;
}

// Getter
int Fecha::getMes() const {
	return this->mes;
}

// Getter
int Fecha::getYear() const {
	return this->year;
}

// Mostrar fecha
void Fecha::mostrarF () const{
	cout <<"Día: " << this->dia <<endl
		 <<"Mes: " << this->mes <<endl
		 <<"Año: " << this->year <<endl;
}

// Calcular días del mes
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

// Comprobar año bisiesto
bool Fecha::anioBisiesto() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);		    // (Es divisible por 4 Y NO por 100) O (Es divisible por 400)
}

// Destructor
Fecha::~Fecha(){
}

// Convertir a cadena
string Fecha::pasarCadena() const {
    return to_string(dia) + "/" + to_string(mes) + "/" + to_string(year);
}
