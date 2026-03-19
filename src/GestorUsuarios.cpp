/*
 * GestorUsuarios.cpp
 *
 *  Created on: 13 mar 2026
 *      Author: estudiante
 */

#include "GestorUsuarios.h"

GestorUsuarios::GestorUsuarios() {
    lUsuarios = new ListaDPI<Usuario *>(); // Crea lista vacía
}

GestorUsuarios::GestorUsuarios(const GestorUsuarios &otroGestorUsuarios) {
	lUsuarios = new ListaDPI<Usuario *>();
	otroGestorUsuarios.lUsuarios->moverPrimero();
	while(!otroGestorUsuarios.lUsuarios->alFinal()){
		Usuario *original = otroGestorUsuarios.lUsuarios->consultar();
		Usuario *copia = new Usuario(*original);
		lUsuarios->insertar(copia);
		otroGestorUsuarios.lUsuarios->avanzar();
	}
}

GestorUsuarios::~GestorUsuarios() {
    if (lUsuarios != nullptr) {
        lUsuarios->moverPrimero();
        while (!lUsuarios->alFinal()) {
            Usuario *aux = lUsuarios->consultar();
            delete aux;              // Borramos el objeto Usuario (Composición)
            lUsuarios->eliminar();   // Borramos el nodo de la lista
        }
        delete lUsuarios;            // Borramos la estructura de la lista
    }
}


// Metodo Insertar
void GestorUsuarios::insertar(string id, string nombre, string email, string pass, int d, int m, int a){
	bool encontrado = false;
	lUsuarios->moverPrimero();
	while(!lUsuarios->alFinal() && !encontrado){
		Usuario *aux = lUsuarios->consultar();
		if(aux->getApellidosNombre() >= nombre){
			encontrado = true;
		}else{
			lUsuarios->avanzar();
		}
	}
	if (encontrado){
		Usuario *aux = lUsuarios->consultar();
		if (aux->getApellidosNombre() == nombre){
			return;
		}
	}
	Usuario *nuevo = new Usuario(id, nombre, email, pass, d, m, a);
	lUsuarios->insertar(nuevo);
}

// Metodo Mostrar
void GestorUsuarios::mostrar() const {
    if (lUsuarios->estaVacia()) {
    	cout << "No hay usuarios registrados en el sistema." << endl;
    } else {
        lUsuarios->moverPrimero();
        while (!lUsuarios->alFinal()) {
            // Consultamos el puntero y llamamos a su método mostrar [cite: 131]
            lUsuarios->consultar()->mostrar();
            lUsuarios->avanzar();
        }
    }
}

// Metodo numElementos
int GestorUsuarios::numElementos() const {
    int contador = 0;
    lUsuarios->moverPrimero();
    while (!lUsuarios->alFinal()) {
        contador++;
        lUsuarios->avanzar();
    }
    return contador;
}

//Metodo Buscar
Usuario* GestorUsuarios::buscar(string apellidosNombre) {
    Usuario *encontrado = nullptr;
    lUsuarios->moverPrimero(); // Empezamos desde el inicio [cite: 120]

    // Recorremos mientras no estemos al final y no hayamos encontrado nada [cite: 129]
    while (!lUsuarios->alFinal() && encontrado == nullptr) {
        Usuario *aux = lUsuarios->consultar(); // Miramos el usuario actual [cite: 131]

        if (aux->getApellidosNombre() == apellidosNombre) {
            encontrado = aux; // ¡Lo tenemos!
        } else {
            lUsuarios->avanzar(); // Seguimos buscando [cite: 116]
        }
    }

    return encontrado;
}












