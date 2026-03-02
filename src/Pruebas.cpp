#include "Pruebas.h"
#include <iostream>

using namespace std;

void pruebasUsuario() {
    cout << "--- Inicio de pruebasUsuario ---" << endl;

    // Caso 1: Constructor por defecto y setters
    Usuario u1;
    u1.setApellidosNombre("Alberto, Núñez");
    if(u1.getApellidosNombre() != "Alberto, Núñez")
        cout << " * Error con apellidosNombre defecto" << endl;

    u1.setIdUsuario("Bernabeu3000");
    if(u1.getIdUsuario() != "Bernabeu3000")
        cout << " * Error con idUsuario defecto" << endl;

    u1.setEmail("alberto@gmail.com");
    if(u1.getEmail() != "alberto@gmail.com")
        cout << " * Error con email defecto" << endl;

    u1.setContrasena("1234");
    if(u1.getContrasena() != "1234")
        cout << " * Error con contraseña defecto" << endl;

    // Caso 2: Constructor con parámetros (7 argumentos) [cite: 48, 51]
    Usuario u2 = Usuario("1", "Candela", "gmail@com.a", "1234", 15, 5, 1995);

    if(u2.getApellidosNombre() != "Candela")
        cout << " * Error con apellidosNombre" << endl;

    if(u2.getIdUsuario() != "1")
        cout << " * Error con idUsuario" << endl;

    if(u2.getEmail() != "gmail@com.a")
        cout << " * Error con email" << endl;

    if(u2.getContrasena() != "1234")
        cout << " * Error con contraseña" << endl;

    cout << "U2 datos cargados: " << u2.pasarACadena() << endl;

    cout << "--- Fin de pruebasUsuario ---" << endl;
}
