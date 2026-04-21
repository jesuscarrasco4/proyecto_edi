/*
 * GestorUsuarios.cpp
 *
 *  Created on: 13 mar 2026
 *      Author: estudiante
 */

#include "GestorUsuarios.h"

#if defined(LISTA_USUARIOS)
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

#else

	GestorUsuarios::GestorUsuarios() {
		aUsuarios = new BSTree<KeyValue<string, Usuario*>>();
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
		delete aUsuarios;
	}

	// Metodo Insertar
	void GestorUsuarios::insertar(string id, string nombre, string email, string pass, int d, int m, int a){
		Usuario *nuevoUsuario = new Usuario(id, nombre, email, pass, d, m, a);

		KeyValue<string, Usuario*> par(nombre, nuevoUsuario);

		if(!aUsuarios->insertar(par);
	}

	// Metodo Mostrar
	void GestorUsuarios::mostrar() const {
	    cout << "--- Listado de Usuarios (Orden Alfabético) ---" << endl;

	    if (aUsuarios->estaVacio()) {
	        cout << "El gestor está vacío." << endl;
	    } else {
	        // 1. Llamada al método recursivo para mostrar los datos
	        mostrarRecursivo(aUsuarios);

	        // 2. Información estadística requerida por el PDF
	        cout << "\nTotal de usuarios: " << numElementos() << endl;
	    }
	}

	// Método privado auxiliar para el recorrido Inorden
	void GestorUsuarios::mostrarRecursivo(BSTree<KeyValue<string, Usuario*>> *arbol) const {
	    if (!arbol->estaVacio()) {
	        // 1. Visitar subárbol izquierdo (menores)
	        mostrarRecursivo(arbol->getIzq());

	        // 2. Procesar raíz (dato actual)
	        // Obtenemos el par [clave-valor] y mostramos el Usuario
	        arbol->getDato().getValue()->mostrar();

	        // 3. Visitar subárbol derecho (mayores)
	        mostrarRecursivo(arbol->getDer());
	    }
	}

	//Metodo Buscar
	Usuario* GestorUsuarios::buscarRecursivo(BSTree<KeyValue<string, Usuario*>> *arbol, const KeyValue<string, Usuario*> &buscado) {
	    if (arbol->estaVacio()) {
	        return nullptr;
	    }

	    // Obtenemos el par KeyValue de la raíz actual
	    KeyValue<string, Usuario*> actual = arbol->getDato();

	    if (actual == buscado) {
	        return actual.getValue(); // ¡Encontrado! Devolvemos el puntero al Usuario [cite: 77, 120]
	    }
	    else if (buscado < actual) {
	        return buscarRecursivo(arbol->getIzq(), buscado); // Buscar en el subárbol izquierdo [cite: 84]
	    }
	    else {
	        return buscarRecursivo(arbol->getDer(), buscado); // Buscar en el subárbol derecho [cite: 84]
	    }
	}

	int GestorUsuarios::numElementos() const {
	    return contarNodos(aUsuarios); // Llama al método privado que cuenta nodos
	}

	// Auxiliar privado
	int GestorUsuarios::contarNodos(BSTree<KeyValue<string, Usuario*>> *arbol) const {
	    if (arbol->estaVacio()) {
	        return 0;
	    }
	    // Suma 1 (raíz) + hijos izquierda + hijos derecha [cite: 5, 9]
	    return 1 + contarNodos(arbol->getIzq()) + contarNodos(arbol->getDer());
	}

#endif









