/*
 * Usuario.h
 *
 *  Created on: 9 feb 2026
 *      Author: estudiante
 */

#ifndef USUARIO_H_
#define USUARIO_H_

#include <iostream>
#include <string> // Importante para usar string
#include "Fecha.h"
using namespace std;

// 1. Definimos la constante primero
const int MAX = 100;

// 2. Definimos la clase Usuario
class Usuario {
private:
	string idUsuario;
	string apellidosNombre;
	string email;
	string contrasena;
	Fecha *fechaNac;

public:
	string getIdUsuario() const;
	string getApellidosNombre() const;
	string getEmail() const;
	string getContrasena() const;
	Fecha* getFechaNac() const;

	Usuario();
	Usuario(string idUsuario, string apellidosNombre, string email, string contrasena, int dia, int mes, int anio);
	Usuario(const Usuario &otroUsuario);

	void setIdUsuario(string idUsuario);
	void setApellidosNombre(string apellidosNombre);
	void setEmail(string email);
	void setContrasena(string contrasena);
	void mostrar() const;

	~Usuario();

	string pasarACadena() const;
};

// 3. AHORA definimos el tipo TVector (ya que la clase Usuario existe)
typedef Usuario* TVector[MAX];

// 4. Declaramos las funciones globales (fuera de la clase)
void cargarUsuarios(TVector usuariosArchivo, int &numUsuarios);
void mostrarUsuarios(TVector usuarios, int numUsuarios);
void destruirUsuarios(TVector usuarios, int &numUsuarios);
void guardarUsuariosPorAnio(TVector usuarios, int numUsuarios, int anioFiltro);

#endif /* USUARIO_H_ */
