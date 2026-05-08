#ifndef USUARIO_H_
#define USUARIO_H_

#include <iostream>
#include <string>
#include "Fecha.h"
#include "ListaDPI.h"
#include "Artista.h"
#include "PlayList.h"

using namespace std;

const int MAX = 100;

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
	Usuario();
	Usuario(string idUsuario, string apellidosNombre, string email, string contrasena, int dia, int mes, int anio);
	Usuario(const Usuario &otroUsuario);
	~Usuario();

	// Getter
	string getIdUsuario() const;
	string getApellidosNombre() const;
	string getEmail() const;
	string getContrasena() const;
	Fecha* getFechaNac() const;

	// Setter
	void setIdUsuario(string idUsuario);
	void setApellidosNombre(string apellidosNombre);
	void setEmail(string email);
	void setContrasena(string contrasena);

	void mostrar() const;
	void crearPlayList(string nombre);
	bool eliminarPlayList(string nombre);
	void anadirCancionAPlayList(string nombrePL, Cancion *c);
	void reproducirPlayLists();
	PlayList* compartirPlayList(string nombrePL);
	void anadirPlayListCompartida(PlayList *pl);
	void insertarArtistaFavorito(Artista *a);
	void eliminarArtistaFavorito(string nombreA);
	void mostrarFavoritos() const;
	string pasarACadena() const;
};

typedef Usuario* TVector[MAX];

void cargarUsuarios(TVector usuariosArchivo, int &numUsuarios);
void mostrarUsuarios(TVector usuarios, int numUsuarios);
void destruirUsuarios(TVector usuarios, int &numUsuarios);
void guardarUsuariosPorAnio(TVector usuarios, int numUsuarios, int anioFiltro);

#endif /* USUARIO_H_ */
