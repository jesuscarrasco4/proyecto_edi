#ifndef GESTORARTISTA_H_
#define GESTORARTISTA_H_

#include "Artista.h"
#include "ListaDPI.h"
#include <string>
#include "BSTree.h"
#include "KeyValue.h"

// 1. Asegúrate de que esta macro es la que compruebas abajo [cite: 126, 137]
// #define LISTA_ARTISTAS

#if defined(LISTA_ARTISTAS)

    class GestorArtistas { // Unificado a plural
    private:
        ListaDPI<Artista *> *lArtista;
    public:
        GestorArtistas();
        GestorArtistas(const GestorArtistas &otro);
        virtual ~GestorArtistas();

        void insertar(string nombre, string pais);
        Artista* buscar(string nombre);
        void mostrar() const;
        int numElementos() const; // Nombre unificado
    };

#else

    class GestorArtistas {
    private:
        BSTree<KeyValue<string, Artista*>> *aArtistas;

        // Métodos privados para el árbol [cite: 206, 207]
        void copiarArbol(BSTree<KeyValue<string, Artista*>> *otro);
        void mostrarInorden(BSTree<KeyValue<string, Artista*>> *a) const;
        int contarNodos(BSTree<KeyValue<string, Artista*>> *a) const;
        // Método necesario para extraer el valor del árbol [cite: 220]
        Artista* buscarRecursivo(BSTree<KeyValue<string, Artista*>> *arbol, const KeyValue<string, Artista*> &buscado);
        int calcularAltura(BSTree<KeyValue<string, Artista*>> *a) const;

    public:
        GestorArtistas(); // [cite: 209]
        GestorArtistas(const GestorArtistas &otro); // [cite: 210]
        ~GestorArtistas(); // [cite: 212]

        // Interfaz pública idéntica [cite: 214]
        void insertar(string nombre, string pais); // [cite: 217]
        Artista* buscar(string nombre); // [cite: 220]
        void mostrar() const; // [cite: 222]
        int numElementos() const;
    };
#endif
#endif /* GESTORARTISTA_H_ */
