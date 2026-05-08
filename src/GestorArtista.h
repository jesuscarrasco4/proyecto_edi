#ifndef GESTORARTISTA_H_
#define GESTORARTISTA_H_

#include "Artista.h"
#include "ListaDPI.h"
#include <string>
#include "BSTree.h"
#include "KeyValue.h"

// #define LISTA_ARTISTAS

#if defined(LISTA_ARTISTAS)

class GestorArtistas {
private:
	ListaDPI<Artista *> *lArtista;

public:
	GestorArtistas();
	GestorArtistas(const GestorArtistas &otro);
	virtual ~GestorArtistas();

	void insertar(string nombre, string pais);
	Artista* buscar(string nombre);
	Artista* artistaConMasSeguidores() const;
	void mostrar() const;
	int numElementos() const;
};

#else

class GestorArtistas {
private:
	BSTree<KeyValue<string, Artista*>> *aArtistas;

	void copiarArbol(BSTree<KeyValue<string, Artista*>> *otro);
	void mostrarInorden(BSTree<KeyValue<string, Artista*>> *a) const;
	int contarNodos(BSTree<KeyValue<string, Artista*>> *a) const;
	Artista* artistaConMasSeguidores(BSTree<KeyValue<string, Artista*>> *a, Artista *mejor) const;
	Artista* buscarRecursivo(BSTree<KeyValue<string, Artista*>> *arbol, const KeyValue<string, Artista*> &buscado);
	int calcularAltura(BSTree<KeyValue<string, Artista*>> *a) const;
	void liberarArtistas(BSTree<KeyValue<string, Artista*>> *a);

public:
	GestorArtistas();
	GestorArtistas(const GestorArtistas &otro);
	~GestorArtistas();

	void insertar(string nombre, string pais);
	Artista* buscar(string nombre);
	Artista* artistaConMasSeguidores() const;
	void mostrar() const;
	int numElementos() const;
};

#endif
#endif
