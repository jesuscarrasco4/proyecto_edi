# Proyecto EDI - Sistema de Musica
#### Jesus Carrasco Toscano y Pedro Ledo Alvarez

Este proyecto implementa en C++ un sistema de gestion musical desarrollado para la
asignatura de Estructuras de Datos e Informacion. La aplicacion permite cargar datos
desde ficheros CSV y gestionar usuarios, artistas, canciones, playlists y favoritos.

El sistema esta construido con programacion orientada a objetos y utiliza varias
estructuras de datos trabajadas durante el curso: listas doblemente enlazadas, colas
y arboles binarios de busqueda.

## Funcionalidades principales

- Cargar usuarios desde `usuarios.csv`.
- Cargar artistas desde `artistas.csv`.
- Cargar canciones desde `canciones.csv`.
- Cargar playlists desde `playList.csv`.
- Mostrar todos los usuarios registrados.
- Mostrar todos los artistas junto con sus canciones.
- Buscar un usuario por nombre.
- Buscar un artista por nombre.
- Compartir playlists entre usuarios.
- Eliminar playlists de un usuario.
- Anadir artistas a favoritos.
- Eliminar artistas de favoritos.
- Mostrar el artista con mas seguidores.
- Ejecutar una bateria de pruebas del sistema.

## Menu de ejecucion

El programa principal se encuentra en `src/progPrincipal.cpp` y ofrece el siguiente
menu:

```text
1. Mostrar todos los Usuarios
2. Mostrar todos los Artistas y Canciones
3. Buscar Usuario (Info completa)
4. Compartir PlayList entre Usuarios
5. Buscar Artista por nombre
6. Eliminar PlayList
7. Anadir Artista a Favoritos
8. Eliminar Artista de Favoritos
9. Mostrar Artista con mas Seguidores
10. Ejecutar Bateria de Pruebas
0. Salir
```

## Clases principales

### `Sistema`

Clase central de la aplicacion. Contiene los gestores de usuarios y artistas, carga
los datos iniciales desde los CSV y ofrece las operaciones principales al menu.

### `GestorUsuarios`

Gestiona los usuarios del sistema. En la version actual utiliza:

```cpp
BSTree<KeyValue<string, Usuario*>>
```

La clave de busqueda es el nombre completo del usuario.

### `GestorArtistas`

Gestiona los artistas del sistema. En la version actual utiliza:

```cpp
BSTree<KeyValue<string, Artista*>>
```

La clave de busqueda es el nombre del artista.

### `Usuario`

Representa un usuario registrado. Contiene sus datos personales, su fecha de
nacimiento, sus playlists y su lista de artistas favoritos.

### `Artista`

Representa un artista musical. Contiene su nombre, pais, numero de seguidores y lista
de canciones.

### `Cancion`

Representa una cancion, almacenando titulo, genero y duracion en segundos.

### `PlayList`

Representa una lista de reproduccion. Internamente usa una cola de punteros a
canciones:

```cpp
Cola<Cancion*>
```

### `Fecha`

Representa la fecha de nacimiento de un usuario.

## Estructuras de datos utilizadas

| Estructura | Uso en el proyecto |
|-----------|--------------------|
| `ListaDPI<TipoDato>` | Listas de playlists, favoritos y canciones |
| `Cola<TipoDato>` | Cola de reproduccion de cada playlist |
| `BSTree<TipoDato>` | Almacenamiento de usuarios y artistas |
| `KeyValue<Key, Value>` | Pares clave-valor dentro de los arboles |

## Ficheros CSV

El programa carga informacion desde los siguientes ficheros:

| Fichero | Contenido |
|--------|-----------|
| `usuarios.csv` | Usuarios registrados |
| `artistas.csv` | Artistas disponibles |
| `canciones.csv` | Canciones asociadas a artistas |
| `playList.csv` | Playlists asociadas a usuarios |

Los CSV se encuentran en la raiz del proyecto.

## Relaciones importantes

- `Sistema` contiene `GestorUsuarios` y `GestorArtistas`.
- `GestorUsuarios` almacena objetos `Usuario`.
- `GestorArtistas` almacena objetos `Artista`.
- `Usuario` contiene sus `PlayList`.
- `Usuario` referencia artistas favoritos.
- `Artista` contiene sus `Cancion`.
- `PlayList` referencia canciones ya existentes.

La diferencia entre composicion y agregacion es importante:

- Las playlists pertenecen al usuario.
- Las canciones pertenecen al artista.
- Los favoritos solo referencian artistas.
- Las playlists solo referencian canciones.

## Gestion de memoria

El proyecto utiliza memoria dinamica con punteros. Por ello se han implementado
destructores y constructores de copia en las clases principales.

Aspectos destacados:

- `Usuario` destruye sus playlists, pero no destruye sus artistas favoritos.
- `Artista` destruye sus canciones.
- `PlayList` destruye su cola, pero no destruye las canciones.
- `Sistema` destruye sus gestores.
- Los gestores liberan los usuarios y artistas que almacenan.

## Pruebas

El proyecto incluye pruebas para las clases principales:

- Usuario
- Artista
- Cancion
- PlayList
- GestorUsuarios
- GestorArtistas

La bateria de pruebas puede ejecutarse desde la opcion `10` del menu principal.

---

Este README resume los puntos principales, mientras que `Documentacion.txt` contiene
una explicacion mas detallada de la arquitectura, las clases, las estructuras de datos,
las relaciones UML, la gestion de memoria y las funcionalidades implementadas.
