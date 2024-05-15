#ifndef PROYECTO_H
#define PROYECTO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct libro{
char titulo[100];
int edicion;
char autor[60];
struct libro *sig;
} Libro;
typedef Libro* PLibro;

typedef struct usuario{
char nombre[60];
char identificacion[20];
char tipo_usuario[15];
struct usuario *sig;
} Usuario;
typedef Usuario* PUsuario;

typedef struct prestamo{
char titulo_libro[100];
char nombre_usuario[60];
char fecha_prestamo[12];
char fecha_devolucion[12];
struct prestamo *sig;
} Prestamo;
typedef Prestamo* PPrestamo;

PLibro nodoLibro(void);
PUsuario nodoUsuario(void);
PPrestamo nodoPrestamo(void);
void darDeAltaLibro(PLibro* cab);
void darDeBajaLibro(PLibro *cab,PPrestamo prestamos);
void darDeAltaUsuario(PUsuario *cab);
void darDeBajaUsuario(PUsuario *cab,PPrestamo prestamos);
void darDeAltaPrestamo(PPrestamo *cab,PLibro libros,PUsuario usuarios);
void darDeBajaPrestamo(PPrestamo *cab);
void actualizarFicheroLibros(PLibro cab);
void actualizarFicheroUsuarios(PUsuario cab);
void actualizarFicheroPrestamos(PPrestamo cab);
void verListaDeLibros(PLibro cab);
void verListaDeUsuarios(PUsuario cab);
void verListaDePrestamos(PPrestamo cab);
void librosPrestadosPorUsuarioDeterminado(PPrestamo prestamos,PUsuario listaUsuarios);
void listaDeLibrosPrestados(PPrestamo prestamos);
void cadenaMinuscula(char cadena[]);







#endif
