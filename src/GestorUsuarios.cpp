#include "GestorUsuarios.h"

#if defined(LISTA_USUARIOS)

	// Constructor por defecto
	GestorUsuarios::GestorUsuarios() {
		lUsuarios = new ListaDPI<Usuario *>();
	}

	// Constructor por copia
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

	// Destructor
	GestorUsuarios::~GestorUsuarios() {
		if (lUsuarios != nullptr) {
			lUsuarios->moverPrimero();
			while (!lUsuarios->alFinal()) {
				Usuario *aux = lUsuarios->consultar();
				delete aux;
				lUsuarios->eliminar();
			}
			delete lUsuarios;
		}
	}

	// Insertar
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

	// Mostrar
	void GestorUsuarios::mostrar() const {
		if (lUsuarios->estaVacia()) {
			cout << "No hay usuarios registrados en el sistema." << endl;
		} else {
			lUsuarios->moverPrimero();
			while (!lUsuarios->alFinal()) {
				lUsuarios->consultar()->mostrar();
				lUsuarios->avanzar();
			}
		}
	}

	// Número de elementos
	int GestorUsuarios::numElementos() const {
		int contador = 0;
		lUsuarios->moverPrimero();
		while (!lUsuarios->alFinal()) {
			contador++;
			lUsuarios->avanzar();
		}
		return contador;
	}

	// Buscar
	Usuario* GestorUsuarios::buscar(string apellidosNombre) {
		Usuario *encontrado = nullptr;
		lUsuarios->moverPrimero();

		while (!lUsuarios->alFinal() && encontrado == nullptr) {
			Usuario *aux = lUsuarios->consultar();

			if (aux->getApellidosNombre() == apellidosNombre) {
				encontrado = aux;
			} else {
				lUsuarios->avanzar();
			}
		}

		return encontrado;
	}

#else

	// Constructor por defecto
	GestorUsuarios::GestorUsuarios() {
		aUsuarios = new BSTree<KeyValue<string, Usuario*>>();
	}

	// Constructor por copia
	GestorUsuarios::GestorUsuarios(const GestorUsuarios &otroGestorUsuarios) {
        aUsuarios = new BSTree<KeyValue<string, Usuario*>>();
        copiarArbol(otroGestorUsuarios.aUsuarios);
	}

	// Destructor
	GestorUsuarios::~GestorUsuarios() {
        liberarUsuarios(aUsuarios);
		delete aUsuarios;
	}

	// Insertar
	void GestorUsuarios::insertar(string id, string nombre, string email, string pass, int d, int m, int a){
        if (buscar(nombre) != nullptr) {
            return;
        }
		Usuario *nuevoUsuario = new Usuario(id, nombre, email, pass, d, m, a);

		KeyValue<string, Usuario*> par(nombre, nuevoUsuario);
		aUsuarios->insertar(par);
	}

	// Mostrar
	void GestorUsuarios::mostrar() const {
	    cout << "--- Listado de Usuarios (Orden Alfabético) ---" << endl;

	    if (aUsuarios->estaVacio()) {
	        cout << "El gestor está vacío." << endl;
	    } else {
	        mostrarRecursivo(aUsuarios);
	        cout << "\nTotal de usuarios: " << numElementos() << endl;
            cout << "Niveles del arbol: " << calcularAltura(aUsuarios) << endl;
	    }
	}

	// Mostrar recursivo
	void GestorUsuarios::mostrarRecursivo(BSTree<KeyValue<string, Usuario*>> *arbol) const {
	    if (!arbol->estaVacio()) {
	        mostrarRecursivo(arbol->getIzq());
	        arbol->getDato().getValue()->mostrar();
	        mostrarRecursivo(arbol->getDer());
	    }
	}

	// Buscar
    Usuario* GestorUsuarios::buscar(string apellidosNombre) {
        KeyValue<string, Usuario*> buscado(apellidosNombre);
        return buscarRecursivo(aUsuarios, buscado);
    }

	// Buscar recursivo
	Usuario* GestorUsuarios::buscarRecursivo(BSTree<KeyValue<string, Usuario*>> *arbol, const KeyValue<string, Usuario*> &buscado) {
	    if (arbol->estaVacio()) {
	        return nullptr;
	    }

	    KeyValue<string, Usuario*> actual = arbol->getDato();

	    if (actual == buscado) {
	        return actual.getValue();
	    }
	    else if (buscado < actual) {
	        return buscarRecursivo(arbol->getIzq(), buscado);
	    }
	    else {
	        return buscarRecursivo(arbol->getDer(), buscado);
	    }
	}

	// Número de elementos
	int GestorUsuarios::numElementos() const {
	    return contarNodos(aUsuarios);
	}

	// Contar nodos
	int GestorUsuarios::contarNodos(BSTree<KeyValue<string, Usuario*>> *arbol) const {
	    if (arbol->estaVacio()) {
	        return 0;
	    }
	    return 1 + contarNodos(arbol->getIzq()) + contarNodos(arbol->getDer());
	}

	// Calcular altura
    int GestorUsuarios::calcularAltura(BSTree<KeyValue<string, Usuario*>> *arbol) const {
        if (arbol->estaVacio()) {
            return 0;
        }
        int altIzq = calcularAltura(arbol->getIzq());
        int altDer = calcularAltura(arbol->getDer());
        return 1 + (altIzq > altDer ? altIzq : altDer);
    }

	// Copiar árbol
    void GestorUsuarios::copiarArbol(BSTree<KeyValue<string, Usuario*>> *arbol) {
        if (arbol == nullptr || arbol->estaVacio()) {
            return;
        }
        KeyValue<string, Usuario*> dato = arbol->getDato();
        Usuario *copiaUsuario = new Usuario(*(dato.getValue()));
        aUsuarios->insertar(KeyValue<string, Usuario*>(dato.getKey(), copiaUsuario));
        copiarArbol(arbol->getIzq());
        copiarArbol(arbol->getDer());
    }

	// Liberar usuarios
    void GestorUsuarios::liberarUsuarios(BSTree<KeyValue<string, Usuario*>> *arbol) {
        if (arbol == nullptr || arbol->estaVacio()) {
            return;
        }
        liberarUsuarios(arbol->getIzq());
        liberarUsuarios(arbol->getDer());
        delete arbol->getDato().getValue();
    }

#endif
