#ifndef SISTEMA_H_
#define SISTEMA_H_

#include <iostream>
#include <string>
#include "GestorUsuarios.h"
#include "GestorArtista.h"

using namespace std;

class Sistema {
private:
    string nombreSistema;
    GestorUsuarios *usuarios;
    GestorArtistas *artistas;

    void cargarUsuarios();
    void cargarArtistas();
    void cargarCanciones();
    void cargarPlayList();

public:
    Sistema();
    Sistema(string nombreSistema);
    Sistema(const Sistema &otro);
    ~Sistema();

    void mostrarUsuarios() const;
    void mostrarArtistas() const;

    void buscarUsuario(string nombre);
    void buscarArtista(string nombre);
    void eliminarPlayList(string nombreUsuario, string nombrePL);
    void anadirArtistaFavorito(string nombreUsuario, string nombreArtista);
    void eliminarArtistaFavorito(string nombreUsuario, string nombreArtista);
    void mostrarArtistaConMasSeguidores() const;
    void compartirPlayList(string nombreOrigen, string nombrePL, string nombreDestino);
};

#endif
