/*
 * GestorUsuarios.h
 *
 *  Created on: 13 mar 2026
 *      Author: estudiante
 */

#ifndef GESTORUSUARIOS_H_
#define GESTORUSUARIOS_H_

#include <iostream>
#include <string>
#include "Usuario.h"
#include "ListaDPI.h"
using namespace std;
#include "KeyValue.h"
#include "BSTree.h"

// #define LISTA_USUARIOS

#if defined(LISTA_USUARIOS)
	class GestorUsuarios {
	private:
		ListaDPI <Usuario *> *lUsuarios;
	public:
		GestorUsuarios();                                      // Constructor por defecto
		GestorUsuarios(const GestorUsuarios &otro);            // Constructor de copia (composición)
		~GestorUsuarios();                                     // Destructor

		// Métodos solicitados
		void insertar(string id, string nombre, string email, string pass, int d, int m, int a);
		int numElementos() const;                              // Número de usuarios
		void mostrar() const;                                  // Muestra todos los usuarios
		Usuario* buscar(string apellidosNombre);               // Devuelve la info si lo encuentra

	};

#else
	class GestorUsuarios{
	private:
		BSTree<KeyValue<string, Usuario*>> *aUsuarios;

		// Métodos privados auxiliares necesarios para el árbol
        void copiarArbol(BSTree<KeyValue<string, Usuario*>> *arbol);
        void mostrarRecursivo(BSTree<KeyValue<string, Usuario*>> *a) const;
        Usuario* buscarRecursivo(BSTree<KeyValue<string, Usuario*>> *arbol, const KeyValue<string, Usuario*> &buscado);
        int contarNodos(BSTree<KeyValue<string, Usuario*>> *arbol) const;
        int calcularAltura(BSTree<KeyValue<string, Usuario*>> *arbol) const;
        void liberarUsuarios(BSTree<KeyValue<string, Usuario*>> *arbol);

	public:
        GestorUsuarios();
        GestorUsuarios(const GestorUsuarios &otro);
        ~GestorUsuarios();

        // Métodos solicitados
   		void insertar(string id, string nombre, string email, string pass, int d, int m, int a);
   		int numElementos() const;                              // Número de usuarios
       	void mostrar() const;                                  // Muestra todos los usuarios
        Usuario* buscar(string apellidosNombre);               // Devuelve la info si lo encuentra

	};
#endif

#endif /* GESTORUSUARIOS_H_ */
