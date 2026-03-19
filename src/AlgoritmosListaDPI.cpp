//============================================================================
// Name        : PruebaTemplateListaDPI.cpp
// Author      : Profesores de EDI
// Version     : 1.0
// Description : Programa que crea una ListaDPI de enteros y trabaja con ella
//============================================================================

#include <iostream>
#include "ListaDPI.h"
using namespace std;

// -------------------------------------------------------------
// VERSIONES ITERATIVAS:
// -------------------------------------------------------------

// PRE: Lista l correctamente inicializada.
// DES: Devuelve el número de elementos de la lista l.
// 		Deja el PI de la lista l apuntando a nullptr (l->enUltimo () = true)
int contarElementos ( ListaDPI <int> *l ) {
	int contador;
	contador = 0;
	l->moverPrimero ( );
	while ( ! l->alFinal ( ) ) {
		contador++;
		l->avanzar ( );
	}
	return contador;
}

// PRE: Lista l correctamente inicializada.
// DES: Devuelve la suma de los elementos de la lista l.
// 		Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
int sumarElementos ( ListaDPI <int> *l ) {
	int suma;
	suma = 0;
	l->moverPrimero ( );
	while ( ! l->alFinal( ) ) {
		suma = suma + l->consultar();
		l->avanzar ( );
	}
	return suma;
}

// PRE: Lista l correctamente inicializada (puede estar vacía).
// DES: Muestra los elementos de la lista l por consola del primero al último.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true).
void mostrar ( ListaDPI <int> *l ){
	cout << "{ ";
	l->moverPrimero ( );
	while ( ! l->alFinal ( ) ) {
		cout << l->consultar ( ) << " ";
		l->avanzar ( );
	}
	cout << "}" << endl;
}

// PRE: Lista l correctamente inicializada (puede estar vacía).
// DES: Muestra los elementos de la l "l" por consola
//		del último al último. Deja el PI de "l" apuntando
//		a nullptr (l->enUltimo ( ) = true).
void mostrarInvertida ( ListaDPI <int> *l ){
	cout << "{ ";
	if ( !l->estaVacia ( ) ) {
		l->moverUltimo ( );
		while ( ! l->enPrimero( ) ) {
			cout << l->consultar() << " ";
			l->retroceder( );
		}
		cout << l->consultar() << " ";
	}
	cout << "}" << endl;
}

// PRE: Lista l correctamente inicializada.
// DES: Elimina de la lista l todos los elementos con valor impar.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true).
void eliminarImpares ( ListaDPI <int> *l ) {
	l->moverPrimero ( );
	while ( ! l->alFinal ( ) ) {
		if ( l->consultar ( ) % 2 == 1 ) {
			l->eliminar ( );
		}
		else {
			l->avanzar ( );
		}
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Inserta el valor n en todas las posiciones impares de l, duplicando su tamaño.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true).
void insertarNEnPosicionesImpares ( ListaDPI <int> *l, int n ){
	l->moverPrimero ( );
	while ( ! l->alFinal ( ) ) {
			l->insertar ( n );
			l->avanzar ( );
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Elimina de l todos los nodos que ocupan posiciones impares, dividiendo su tamaño a la mitad.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true)
void eliminarPosicionesImpares ( ListaDPI <int> *l ){
	l->moverPrimero ( );
	while ( ! l->alFinal ( ) ) {
		l->eliminar ( );
		if ( ! l->alFinal (  ) ) {
			l->avanzar ( );
		}
	}
}

// -------------------------------------------------------------
// VERSIONES RECURSIVAS (recursividad indirecta):
// -------------------------------------------------------------

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado al inicio (l->enPrimero () = true).
// DES: Devuelve el número de elementos de la lista l.
// 		Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
int contarElementosRec ( ListaDPI <int> *l ) {
	int contador;
	contador = 0;
	if ( ! l->alFinal( ) ) {
		l->avanzar ( );
		contador = 1 + contarElementosRec ( l );
	}
	return contador;
}

// PRE: Lista l correctamente inicializada.
// DES: Devuelve el número de elementos de la lista l.
// 		Deja el PI de la lista l apuntando a nullptr (l->enUltimo () = true)
int contarElementosR ( ListaDPI <int> *l ) {
	l->moverPrimero ( );		// Precondición de contarElementosRec
	return contarElementosRec ( l );
}

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado al inicio (l->enPrimero () = true).
// DES: Devuelve la suma de los elementos de la lista l.
// 		Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
int sumarRec ( ListaDPI <int> *l ) {
	int suma, valor;
	suma = 0;
	if ( !l->alFinal ( ) ) {
		valor = l->consultar ( );
		l->avanzar ( );
		suma = valor + sumarRec ( l );
	}
	return suma;
}

// PRE: Lista l correctamente inicializada.
// DES: Devuelve la suma de los elementos de la lista l.
// 		Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
int sumarElementosR ( ListaDPI <int> *l ) {
	l->moverPrimero ( );		// Precondición de sumarRec
	return sumarRec ( l );
}

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado al inicio (l->enPrimero () = true).
// DES: Muestra los elementos de la lista l por consola del primero al
// 		último. Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
void mostrarRec ( ListaDPI <int> *l  ) {
	if ( ! l->alFinal ( ) ) {
		cout << l->consultar() << " ";
		l->avanzar ( );
		mostrarRec ( l );
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Muestra los elementos de la lista l por consola del primero al último.
//		Deja el PI de l apuntando a nullptr (l->enUltimo ( ) = true).
void mostrarR ( ListaDPI <int> *l  ) {
	l->moverPrimero ( );		// Precondición de mostrarRec
	cout << "{ ";
	mostrarRec ( l );
	cout << "}" << endl;
}

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado en el último nodo (l->enUltimo () = true).
// DES: Muestra los elementos de la lista l por consola del último al primero.
//		Deja el PI de l apuntando al primer elemento (l->enPrimero( ) = true).
void mostInvertidaRec ( ListaDPI <int> *l ) {
	cout << l->consultar() << " ";
	if ( ! l->enPrimero ( ) ) {
		l->retroceder( );
		mostInvertidaRec ( l );
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Muestra los elementos de la lista l por consola del último al primero.
// 		Deja el PI de l apuntando al primer elemento (l->enPrimero ( ) = true).
void mostrarInvertidaR ( ListaDPI <int> *l ){
	cout << "{ ";
	if ( !l->estaVacia ( ) ) {
		l->moverUltimo ( );		// Precondición de mostInvertidaRec
		mostInvertidaRec ( l );
	}
	cout << "}" << endl;
}

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado al inicio (l->enPrimero () = true).
// DES: Elimina de la lista l todos los elementos con valor impar.
// 		Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
void eliminarImparesRec ( ListaDPI <int> *l ) {
	int valor;
	if ( ! l->alFinal ( ) ) {
		valor = l->consultar ( );
		if ( valor % 2 == 1 ) {
			l->eliminar ( );
		}
		else {
			l->avanzar ( );
		}
		eliminarImparesRec ( l );
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Elimina de la lista l todos los elementos con valor impar.
// 		Deja el PI de l apuntando a nullptr (l->enUltimo () = true).
void eliminarImparesR ( ListaDPI <int> *l ) {
	l->moverPrimero ( ); 	// precondicion de eliminarImparesRec
	eliminarImparesRec ( l );
}

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado al inicio (l->enPrimero () = true).
// DES: Inserta el valor n en todas las posiciones impares de l, duplicando su tamaño.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true).
void insertarNEnPosicionesImparesRec ( ListaDPI <int> *l, int n ){
	if ( !l->alFinal ( ) ) {
		l->insertar ( n );
		l->avanzar ( );
		insertarNEnPosicionesImparesRec ( l, n );
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Inserta el valor n en todas las posiciones impares de l, duplicando su tamaño.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true).
void insertarNEnPosicionesImparesR ( ListaDPI <int> *l, int n ){
	l->moverPrimero ( );		// Precondicion de insertarNEnPosicionesImparesRec
	insertarNEnPosicionesImparesRec ( l, n );
}

// PRE: Lista l correctamente inicializada. En la primera llamada, el PI
//		de l debe estar colocado al inicio (l->enPrimero () = true).
// DES: Elimina de l todos los nodos que ocupan posiciones impares,
// 		dividiendo su tamaño a la mitad.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true)
void eliminarPosicionesImparesRec ( ListaDPI <int> *l ){
	if ( !l->alFinal ( ) ) {
		l->eliminar ( );
		if ( !l->alFinal ( ) )
			l->avanzar ( );
		eliminarPosicionesImparesRec ( l );
	}
}

// PRE: Lista l correctamente inicializada.
// DES: Elimina de l todos los nodos que ocupan posiciones impares,
// 		dividiendo su tamaño a la mitad.
// 		Deja el PI de la l apuntando a nullptr (l->enUltimo () = true)
void eliminarPosicionesImparesR ( ListaDPI <int> *l ){
	l->moverPrimero ( );
	eliminarPosicionesImparesRec (l);
}

// ------------------------------------------------------------
// FUNCIÓN AUXILIAR QUE CREA UNA LISTA CON fin-ini ELEMENTOS
// ------------------------------------------------------------
ListaDPI <int> *crearLista (int ini, int fin) {
	int i;
	ListaDPI <int> *nueva = new ListaDPI<int> ();
	for (i = ini; i <= fin; i++) {
		nueva->insertar (i);
	}
	return nueva;
}

// ------------------------------------------------------------
// PROGRAMA PRINCIPAL: Invoca a las funciones anteriores para
//                     comprobar su correcto funcionamiento.
// ------------------------------------------------------------

/* int main() {

	ListaDPI <int> *l;
	int cuenta, cuentaR;
	int suma, sumaR;

	// Creación de una l vacía

	l = new ListaDPI <int> ();

	// Comprobaciones sobre una lista recién creada (vacía)

	if ( ! l->estaVacia ( ) ) {
		cerr << "Una lista recién creada debería estar vacía" << endl;
	}
	if ( ! l->enPrimero( ) ) {
		cerr << "En una lista recién creada el PI debería estar al inicio" << endl;
	}
	if ( ! l->enUltimo( ) ) {
		cerr << "En una lista recién creada el PI debería estar al final" << endl;
	}

	cuenta = contarElementos ( l );

	if ( cuenta != 0 ) {
		cerr << "Una lista recién recreada debe tener 0 elementos y tiene (método iterativo) " << cuenta << endl;
	}

	cuentaR = contarElementosR ( l );
	if ( cuentaR != 0 ) {
		cerr << "Una lista recién recreada debe tener 0 elementos y tiene (método recursivo) " << cuentaR << endl;
	}

	suma = sumarElementos ( l );
	if ( suma != 0 ) {
		cerr << "Los elementos de una lista recién recreada deben sumar 0 y suman (método iterativo) " << suma << endl;
	}

	sumaR = sumarElementosR ( l );
	if ( sumaR != 0 ) {
		cerr << "Los elementos de una l recién recreada deben sumar 0 y suman (método recursivoR) " << sumaR << endl;
	}

	cout << "mostrar (l) cuando l está vacía muestra: ";
	mostrar ( l );

	cout << "mostrarR (l) cuando l está vacía muestra: ";
	mostrarR ( l );

	cout << "mostrarInvertida (l) cuando l está vacía muestra: ";
	mostrarInvertida ( l );

	cout << "mostrarInvertidaR (l) cuando l está vacía muestra: ";
	mostrarInvertidaR ( l );

	// Insertamos un elemento en la lista => l = {1}

	l->insertar ( 1 );

	// Comprobaciones sobre una lista con 1 elemento

	if ( l-> estaVacia () ) {
		cerr << "Tras insertar 1 elemento la lista no puede estar vacía" << endl;
	}

	cuenta = contarElementos ( l );
	if ( cuenta != 1 ) {
		cerr << "Tras insertar un elemento la lista debe tener 1 elemento y tiene (método iterativo) " << cuenta << endl;
	}

	cuentaR = contarElementosR ( l );
	if ( cuentaR != 1 ) {
		cerr << "Tras insertar un elemento la lista debe tener 1 elemento y tiene (método recursivo) " << cuentaR << endl;
	}

	suma = sumarElementos ( l );
	if ( suma != 1 ) {
		cerr << "Los elementos de la lista {1} deben sumar 1 y suman (método iterativo) " << suma << endl;
	}

	sumaR = sumarElementosR ( l );
	if ( sumaR != 1 ) {
		cerr << "Los elementos de la lista {1} deben sumar 1 y suman (método recursivoR) " << sumaR << endl;
	}

	cout << "mostrar (l) cuando l = { 1 } muestra: ";
	mostrar ( l );

	cout << "mostrarR (l) cuando l = { 1 } muestra: ";
	mostrarR ( l );

	cout << "mostrarInvertida (l) cuando l = { 1 } muestra: ";
	mostrarInvertida ( l );

	cout << "mostrarInvertidaR (l) cuando l = { 1 } muestra: ";
	mostrarInvertidaR ( l );

	l->eliminar ( );	// elimina el único nodo de la l => la deja vacía

	if ( !l-> estaVacia () ) {
		cerr << "Tras eliminar el único elemento la l debe estar vacía" << endl;
	}

	delete l;


	// Creación de una lista con 10 elementos => l = {1, 2, ..., 10}

	l = crearLista ( 1, 10 );

	if ( l-> estaVacia () ) {
		cerr << "Tras insertar 10 elementos la lista no puede estar vacía" << endl;
	}

	cout << "mostrar (l) cuando l = { 1 2 3 4 5 6 7 8 9 10 } muestra: " << endl;
	mostrar ( l );

	cout << "mostrarR (l) cuando l = { 1 2 3 4 5 6 7 8 9 10 } muestra: " << endl;
	mostrarR ( l );

	cout << "mostrarInvertida (l) cuando l = { 1 2 3 4 5 6 7 8 9 10 } muestra: " << endl;
	mostrarInvertida ( l );

	cout << "mostrarInvertidaR (l) cuando l = { 1 2 3 4 5 6 7 8 9 10 } muestra: " << endl;
	mostrarInvertidaR ( l );

	cout << "Cuenta iterativa de los elementos de la lista = " << contarElementos ( l ) << endl;
	cout << "Cuenta recursiva de los elementos de la lista = " << contarElementosR ( l ) << endl;

	cout << "Suma iterativa de los elementos de la lista = " << sumarElementos ( l ) << endl;
	cout << "Suma recursiva de los elementos de la lista = " << sumarElementosR ( l ) << endl;

	eliminarImpares ( l );

	cout << "Tras eliminar impares de l = { 1 2 3 4 5 6 7 8 9 10 } se muestra: " << endl;
	mostrar ( l );
	delete l;

	// Creación de una lista con 10 elementos => l = {1, 2, ..., 10}

	l = crearLista ( 1, 10 );

	cout << "Tras eliminar imparesR de l = { 1 2 3 4 5 6 7 8 9 10 } se muestra: " << endl;
	eliminarImparesR ( l );
	mostrar ( l );

	insertarNEnPosicionesImpares ( l, 1111 );
	cout << "Tras insertar (iterativo) 1111 en posiciones impares de l se muestra: " << endl;
	mostrar ( l );

	eliminarPosicionesImpares ( l );
	cout << "Tras eliminar (iterativo) posiciones impares de l se muestra: " << endl;
	mostrar ( l );

	insertarNEnPosicionesImparesR (l, 2222);
	cout << "Tras insertar (recursivo) 2222 en posiciones impares de l se muestra: " << endl;
	mostrar ( l );

	eliminarPosicionesImparesR ( l );
	cout << "Tras eliminar (recursivo) posiciones impares de l se muestra: " << endl;
	mostrar ( l );

	delete l;

	cout << "Fin del programa " << endl;

	return 0;
}

*/
