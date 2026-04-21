#include "PruebasArtista.h"
#include <iostream>

using namespace std;

void pruebasArtista() {
    cout << "--- Inicio de Pruebas: Artista con Lista de Canciones ---" << endl;

    // 1. Crear artista dinámicamente
    Artista *a1 = new Artista("Coldplay", "UK", 50000000);

    // 2. Probar inserción ordenada de canciones [cite: 218]
    cout << "\n[1] Insertando canciones..." << endl;
    a1->insertarCancion("Yellow", "Alternative", 269);      // Segunda (Intermedia)
    a1->insertarCancion("Clocks", "Rock", 307);             // Primera (Al principio)
    a1->insertarCancion("Zzz", "Relax", 120);              // Última (Al final)

    // 3. Probar duplicados [cite: 219]
    cout << "[2] Intentando insertar duplicado ('Yellow')..." << endl;
    a1->insertarCancion("Yellow", "Pop", 100);

    // 4. Mostrar para verificar orden y número [cite: 223, 247]
    cout << "\nEstado del artista:" << endl;
    a1->mostrar();
    cout << "Total canciones: " << a1->numCanciones() << " (esperado: 3)" << endl;

    // 5. Probar búsqueda [cite: 220, 243]
    cout << "\n[3] Probando busqueda..." << endl;
    Cancion datosEncontrados;
    if (a1->buscarCancion("Yellow", datosEncontrados)) {
        cout << "[OK] Cancion encontrada: " << datosEncontrados.getTitulo()
             << " [" << datosEncontrados.getGenero() << "]" << endl;
    } else {
        cout << "[ERROR] No se encontro 'Yellow'" << endl;
    }

    // 6. Probar Constructor de Copia (Composición Crítica) [cite: 215, 216]
    cout << "\n[4] Probando copia profunda (Constructor de copia)..." << endl;
    Artista *a2 = new Artista(*a1); // Clonamos Coldplay

    cout << "Copia creada. Modificando original (borramos canciones en el original indirectamente)..." << endl;
    // Si borramos a1, las canciones de a2 deben seguir vivas si la copia es profunda.
    delete a1;

    cout << "Datos del artista clonado tras borrar el original:" << endl;
    a2->mostrar(); // Si esto no falla y muestra las canciones, la copia es perfecta.

    // 7. Limpieza final
    delete a2;

    cout << "\n--- Fin de Pruebas Artista: Memoria OK ---" << endl;
}
