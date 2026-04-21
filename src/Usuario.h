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
#include "ListaDPI.h"  // Necesario para las listas
#include "Artista.h"
#include "PlayList.h"

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

	ListaDPI<PlayList*> *lPlayLists;
	ListaDPI<Artista*> *lArtistasFavoritos;

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

	// --- MÉTODOS A IMPLEMENTAR/MODIFICAR ---
	void crearPlayList(string nombre); // [cite: 74]
	void anadirCancionAPlayList(string nombrePL, Cancion *c); // [cite: 76]
	void reproducirPlayLists(); // Reproduce todas [cite: 77]

	// Para compartir música
	PlayList* compartirPlayList(string nombrePL); // Devuelve copia [cite: 78, 79]
	void anadirPlayListCompartida(PlayList *pl); // Inserta la copia [cite: 80]

	// Gestión de favoritos
	void insertarArtistaFavorito(Artista *a); // [cite: 81]
	void eliminarArtistaFavorito(string nombreA); // [cite: 83]
	void mostrarFavoritos() const; // [cite: 84]

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
