#include "GestorArtista.h"
#include <iostream>

using namespace std;

#if defined (LISTA_ARTISTAS)
    // Constructor con Lista
	GestorArtistas::GestorArtistas() {
		lArtista = new ListaDPI<Artista *>();
	}

    // Constructor de copia con Lista
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
    GestorArtistas::GestorArtistas() {
        aArtistas = new BSTree<KeyValue<string, Artista*>>();
    }

    GestorArtistas::~GestorArtistas() {
        delete aArtistas;
    }

    void GestorArtistas::insertar(string nombre, string pais) {
        Artista *nuevo = new Artista(nombre, pais, 0);
        KeyValue<string, Artista*> par(nombre, nuevo);
        aArtistas->insertar(par);
    }

    Artista* GestorArtistas::buscar(string nombre) {
        KeyValue<string, Artista*> molde(nombre);
        if (aArtistas->existe(molde)) {
            return buscarRecursivo(aArtistas, molde);
        }
        return nullptr;
    }

    // Método auxiliar para buscar el puntero real dentro del árbol
    Artista* GestorArtistas::buscarRecursivo(BSTree<KeyValue<string, Artista*>> *arbol, const KeyValue<string, Artista*> &buscado) {
        if (arbol->estaVacio()) return nullptr;
        if (arbol->getDato() == buscado) return arbol->getDato().getValue();
        if (buscado < arbol->getDato()) return buscarRecursivo(arbol->getIzq(), buscado);
        return buscarRecursivo(arbol->getDer(), buscado);
    }

    void GestorArtistas::mostrar() const {
        if (aArtistas->estaVacio()) {
            cout << "Estructura vacia." << endl;
        } else {
            mostrarInorden(aArtistas);
            cout << "Total elementos: " << numElementos() << endl;
            cout << "Niveles del arbol: " << calcularAltura(aArtistas) << endl; // <--- Requisito PDF
        }
    }

    // Recorrido Inorden para mostrar ordenado [cite: 222]
    void GestorArtistas::mostrarInorden(BSTree<KeyValue<string, Artista*>> *a) const {
        if (!a->estaVacio()) {
            mostrarInorden(a->getIzq());
            a->getDato().getValue()->mostrar();
            cout << "---------------------------------" << endl;
            mostrarInorden(a->getDer());
        }
    }

    int GestorArtistas::numElementos() const {
        return contarNodos(aArtistas);
    }

    int GestorArtistas::contarNodos(BSTree<KeyValue<string, Artista*>> *a) const {
        if (a->estaVacio()) return 0;
        return 1 + contarNodos(a->getIzq()) + contarNodos(a->getDer());
    }

    int GestorArtistas::calcularAltura(BSTree<KeyValue<string, Artista*>> *a) const {
        if (a->estaVacio()) return 0;

        int altIzq = calcularAltura(a->getIzq());
        int altDer = calcularAltura(a->getDer());

        return 1 + (altIzq > altDer ? altIzq : altDer);
    }

#endif
