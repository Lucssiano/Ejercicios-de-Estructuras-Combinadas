/* 8) Una biblioteca necesita un programa que efectúe las altas en el archivo maestro de
libros. Para ello cuenta con:

a) LIBROS.dat, archivo maestro de libros ordenado por código de libro,
con un registro por cada libro, con el siguiente diseño:
. Código de libro (int)
. Título del libro (30 caracteres)
. Apellido del autor (15 caracteres)
. Nacionalidad (int)
. Cantidad de ejemplares
b) NOVEDADES.dat, archivo con los libros a dar de alta sin ningún
orden, con el mismo diseño del archivo maestro.

Se pide realizar la metodología necesaria para que el programa:
1) Genere un nuevo archivo LIBROSACT.dat, con el mismo diseño y orden que el
maestro y con las altas incorporadas.
2) Emitir el siguiente listado, agrupado por nacionalidad y ordenado ascendente
por cantidad total de autores:
Nacionalidad  .............. Cantidad Total de autores: 999
Apellido del Autor          Cantidad total de títulos
......................              99
*/

// Que serian las altas?

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Libro
{
  int cod, cantEjemplares;
  char titulo[30], apellidoAutor[15];
  // Nacionalidad int (????)
};

int main()
{

  return 0;
}
