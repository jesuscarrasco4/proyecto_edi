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
    GestorArtistas *artistas; // [CORREGIDO] Añadida la 's' para coincidir con la clase

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
    void compartirPlayList(string nombreOrigen, string nombrePL, string nombreDestino);
};

#endif
