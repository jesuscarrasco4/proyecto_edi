#include "GestorArtista.h"
#include <iostream>

using namespace std;

#if defined (LISTA_ARTISTAS)

	// Constructor por defecto
	GestorArtistas::GestorArtistas() {
		lArtista = new ListaDPI<Artista *>();
	}

	// Constructor por copia
	GestorArtistas::GestorArtistas(const GestorArtistas &otro) {
		lArtista = new ListaDPI<Artista *>();
		otro.lArtista->moverPrimero();
		while(!otro.lArtista->alFinal()){
			Artista *original = otro.lArtista->consultar();
			Artista * copia = new Artista(*original);
			lArtista->insertar(copia);
			otro.lArtista->avanzar();
		}
	}

	// Destructor
	GestorArtistas::~GestorArtistas() {
		if(lArtista != nullptr){
			lArtista->moverPrimero();
			while (!lArtista->estaVacia()){
				Artista *aux = lArtista->consultar();
				delete aux;
				lArtista->eliminar();
			}
			delete lArtista;
		}
	}

	// Insertar
	void GestorArtistas::insertar(string nombre, string pais){
		bool encontrado = false;
		lArtista->moverPrimero();
		while(!lArtista->alFinal() && !encontrado){
			if (lArtista->consultar()->getNombre() >= nombre) {
				encontrado = true;
			}else{
				lArtista->avanzar();
			}
		}
		if(encontrado && lArtista->consultar()->getNombre() == nombre){
			return;
		}
		Artista *nuevo = new Artista(nombre, pais, 0);
		lArtista->insertar(nuevo);
	}

	// Buscar
	Artista* GestorArtistas::buscar(string nombre){
		Artista *encontrado = nullptr;
		lArtista->moverPrimero();
		while(!lArtista->alFinal() && encontrado==nullptr){
			if(lArtista->consultar()->getNombre() == nombre){
				encontrado = lArtista->consultar();
			}else{
				lArtista->avanzar();
			}
		}
		return encontrado;
	}

	// Artista con más seguidores
    Artista* GestorArtistas::artistaConMasSeguidores() const {
        Artista *mejor = nullptr;
        lArtista->moverPrimero();

        while (!lArtista->alFinal()) {
            Artista *actual = lArtista->consultar();
            if (mejor == nullptr ||
                actual->getNumeroSeguidores() > mejor->getNumeroSeguidores()) {
                mejor = actual;
            }
            lArtista->avanzar();
        }

        return mejor;
    }

	// Mostrar
	void GestorArtistas::mostrar() const{
		if(lArtista->estaVacia()){
			cout << "El gestor de artista esta vacio" << endl;
		}else{
			cout << "Lista de Artistas en el Sistema" << endl;
			lArtista->moverPrimero();
			while(!lArtista->alFinal()){
				Artista *aux = lArtista->consultar();
				aux->mostrar();
				cout << "---------------------------------" << endl;
				lArtista->avanzar();
			}
		}
	}

	// Número de elementos
    int GestorArtistas::numElementos() const {
        int cont = 0;
        lArtista->moverPrimero();
        while(!lArtista->alFinal()){
            cont++;
            lArtista->avanzar();
        }
        return cont;
    }

#else

	// Constructor por defecto
    GestorArtistas::GestorArtistas() {
        aArtistas = new BSTree<KeyValue<string, Artista*>>();
    }

	// Constructor por copia
    GestorArtistas::GestorArtistas(const GestorArtistas &otro) {
        aArtistas = new BSTree<KeyValue<string, Artista*>>();
        copiarArbol(otro.aArtistas);
    }

	// Destructor
    GestorArtistas::~GestorArtistas() {
        liberarArtistas(aArtistas);
        delete aArtistas;
    }

	// Insertar
    void GestorArtistas::insertar(string nombre, string pais) {
        if (buscar(nombre) != nullptr) {
            return;
        }
        Artista *nuevo = new Artista(nombre, pais, 0);
        KeyValue<string, Artista*> par(nombre, nuevo);
        aArtistas->insertar(par);
    }

	// Buscar
    Artista* GestorArtistas::buscar(string nombre) {
        KeyValue<string, Artista*> molde(nombre);
        if (aArtistas->existe(molde)) {
            return buscarRecursivo(aArtistas, molde);
        }
        return nullptr;
    }

	// Buscar recursivo
    Artista* GestorArtistas::buscarRecursivo(BSTree<KeyValue<string, Artista*>> *arbol, const KeyValue<string, Artista*> &buscado) {
        if (arbol->estaVacio()) return nullptr;
        if (arbol->getDato() == buscado) return arbol->getDato().getValue();
        if (buscado < arbol->getDato()) return buscarRecursivo(arbol->getIzq(), buscado);
        return buscarRecursivo(arbol->getDer(), buscado);
    }

	// Artista con más seguidores
    Artista* GestorArtistas::artistaConMasSeguidores() const {
        return artistaConMasSeguidores(aArtistas, nullptr);
    }

	// Artista con más seguidores recursivo
    Artista* GestorArtistas::artistaConMasSeguidores(BSTree<KeyValue<string, Artista*>> *a, Artista *mejor) const {
        if (a == nullptr || a->estaVacio()) {
            return mejor;
        }

        Artista *actual = a->getDato().getValue();
        if (mejor == nullptr ||
            actual->getNumeroSeguidores() > mejor->getNumeroSeguidores()) {
            mejor = actual;
        }

        mejor = artistaConMasSeguidores(a->getIzq(), mejor);
        return artistaConMasSeguidores(a->getDer(), mejor);
    }

	// Mostrar
    void GestorArtistas::mostrar() const {
        if (aArtistas->estaVacio()) {
            cout << "Estructura vacia." << endl;
        } else {
            mostrarInorden(aArtistas);
            cout << "Total elementos: " << numElementos() << endl;
            cout << "Niveles del arbol: " << calcularAltura(aArtistas) << endl;
        }
    }

	// Mostrar inorden
    void GestorArtistas::mostrarInorden(BSTree<KeyValue<string, Artista*>> *a) const {
        if (!a->estaVacio()) {
            mostrarInorden(a->getIzq());
            a->getDato().getValue()->mostrar();
            cout << "---------------------------------" << endl;
            mostrarInorden(a->getDer());
        }
    }

	// Número de elementos
    int GestorArtistas::numElementos() const {
        return contarNodos(aArtistas);
    }

	// Contar nodos
    int GestorArtistas::contarNodos(BSTree<KeyValue<string, Artista*>> *a) const {
        if (a->estaVacio()) return 0;
        return 1 + contarNodos(a->getIzq()) + contarNodos(a->getDer());
    }

	// Calcular altura
    int GestorArtistas::calcularAltura(BSTree<KeyValue<string, Artista*>> *a) const {
        if (a->estaVacio()) return 0;

        int altIzq = calcularAltura(a->getIzq());
        int altDer = calcularAltura(a->getDer());

        return 1 + (altIzq > altDer ? altIzq : altDer);
    }

	// Copiar árbol
    void GestorArtistas::copiarArbol(BSTree<KeyValue<string, Artista*>> *otro) {
        if (otro == nullptr || otro->estaVacio()) {
            return;
        }
        KeyValue<string, Artista*> dato = otro->getDato();
        Artista *copiaArtista = new Artista(*(dato.getValue()));
        aArtistas->insertar(KeyValue<string, Artista*>(dato.getKey(), copiaArtista));
        copiarArbol(otro->getIzq());
        copiarArbol(otro->getDer());
    }

	// Liberar artistas
    void GestorArtistas::liberarArtistas(BSTree<KeyValue<string, Artista*>> *a) {
        if (a == nullptr || a->estaVacio()) {
            return;
        }
        liberarArtistas(a->getIzq());
        liberarArtistas(a->getDer());
        delete a->getDato().getValue();
    }

#endif
