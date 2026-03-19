#include "PruebaGestorUsuarios.h"
#include <iostream>

using namespace std;

void pruebasGestorUsuarios() {
    cout << "--- Inicio de Pruebas: GestorUsuarios ---" << endl;

    GestorUsuarios *gestor = new GestorUsuarios();

    // 1. Probar inserción ordenada [cite: 162]
    // Insertamos desordenado para ver si la lista los ordena sola
    gestor->insertar("2", "Casillas, Iker", "iker@real.com", "123", 20, 5, 1981); // Intermedio
    gestor->insertar("1", "Arbeloa, Alvaro", "alvaro@real.com", "123", 17, 1, 1983); // Al principio [cite: 184]
    gestor->insertar("3", "Zidane, Zinedine", "zizou@real.com", "123", 23, 6, 1972); // Al final [cite: 185]

    cout << "Usuarios tras inserciones (deben salir ordenados):" << endl;
    gestor->mostrar(); // [cite: 191]

    // 2. Probar duplicados [cite: 163]
    cout << "\nIntentando insertar duplicado (Arbeloa)..." << endl;
    gestor->insertar("1", "Arbeloa, Alvaro", "copy@real.com", "999", 1, 1, 1990);
    cout << "Numero de elementos (debe ser 3): " << gestor->numElementos() << endl;

    // 3. Probar Búsqueda [cite: 187, 188]
    cout << "\nBuscando a 'Casillas, Iker'..." << endl;
    Usuario *buscado = gestor->buscar("Casillas, Iker");
    if (buscado) {
        cout << "[OK] Encontrado: " << buscado->getEmail() << endl;
    } else {
        cout << "[ERROR] No encontrado" << endl;
    }

    // 4. Probar Constructor de Copia (Composición) [cite: 160]
    cout << "\nProbando constructor de copia (Copia Profunda)..." << endl;
    GestorUsuarios *copiaGestor = new GestorUsuarios(*gestor);
    cout << "Copia del gestor creada. Elementos en copia: " << copiaGestor->numElementos() << endl;

    // 5. Limpieza de memoria (Llama a los destructores) [cite: 166]
    delete gestor;
    delete copiaGestor;

    cout << "\n--- Fin de Pruebas: Memoria Liberada ---" << endl;
}
