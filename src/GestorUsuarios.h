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


class GestorUsuarios {
private:
	ListaDPI <Usuario *> *lUsuarios;
public:
    GestorUsuarios();                                      // Constructor por defecto [cite: 154]
    GestorUsuarios(const GestorUsuarios &otro);            // Constructor de copia (composición)
    ~GestorUsuarios();                                     // Destructor [cite: 156]

    // Métodos solicitados
    void insertar(string id, string nombre, string email, string pass, int d, int m, int a); // [cite: 162]
    int numElementos() const;                              // Número de usuarios [cite: 165]
    void mostrar() const;                                  // Muestra todos los usuarios [cite: 166]
    Usuario* buscar(string apellidosNombre);               // Devuelve la info si lo encuentra [cite: 164]

};
#endif /* GESTORUSUARIOS_H_ */
