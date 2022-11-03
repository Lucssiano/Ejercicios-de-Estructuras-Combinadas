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

/* 2)
- Se me ocurre hacer una lista que este ordenada por nacionalidad y que tenga una sublista
con los autores que tiene cada nacionalidad, por cada autor que encuentro de la nacionalidad,
debo poner la cantidad de titulos que tiene y su apellido.

- Para armar la lista leo el archivo actualizado y voy insertando en orden por nacionalidad y si la nacionalidad ya existe agrego al autor en la sublista


- La nacionalidad como hago para agrupar? se supone que en la lista está desordenado ,
no se podria un corte de control
cant autores (por nacionalidad?)- recorro la lista y sumo 1 en el contador hasta que sea null la lista
(cambie de nacionalidad ?)
por cada autor que encuentro de la nacionalidad, debo poner la cantidad de titulos que tiene
 */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Libro
{
  int cod, cantEjemplares, nacionalidad;
  char titulo[30], apellidoAutor[15];
};

struct NodoL
{
  Libro info;
  NodoL *sig;
};

void generarArchivoLibros();
void generarArchivoNovedades();
void punto1(FILE *archLibros, FILE *archNovedades);
void insertar(NodoL *&lista, Libro lib);
void apareo(NodoL *lista, FILE *archLib, FILE *archLibAct);
void mostrarArchivoLibrosActualizados();
void punto2();

int main()
{
  // generarArchivoLibros();
  // generarArchivoNovedades();
  FILE *archivoDeLibros = fopen("LIBROS.dat", "rb");
  FILE *archivoDeNovedades = fopen("NOVEDADES.dat", "rb");

  if (archivoDeLibros == NULL || archivoDeNovedades == NULL)
  {
    cout << "ERROR" << endl;
  }
  else
  {
    punto1(archivoDeLibros, archivoDeNovedades);
    fclose(archivoDeLibros);
    fclose(archivoDeNovedades);
    mostrarArchivoLibrosActualizados();
    // punto2(archivoDeLibros, archivoDeNovedades);
  }
  return 0;
}

void punto1(FILE *archLibros, FILE *archNovedades)
{
  FILE *archivoDeLibrosActualizados = fopen("LIBROSACT.dat", "wb");
  if (archivoDeLibrosActualizados == NULL)
  {
    cout << "ERROR" << endl;
  }
  else
  {
    NodoL *listaNovedades = NULL;
    Libro datosArchNovedades;

    fread(&datosArchNovedades, sizeof(Libro), 1, archNovedades);
    while (!feof(archNovedades))
    {
      insertar(listaNovedades, datosArchNovedades);
      fread(&datosArchNovedades, sizeof(Libro), 1, archNovedades);
    }
    apareo(listaNovedades, archLibros, archivoDeLibrosActualizados);
    fclose(archivoDeLibrosActualizados);
  }
}

void insertar(NodoL *&lista, Libro lib)
{
  NodoL *q, *p, *ant;
  q = new NodoL;
  q->info = lib;
  p = lista;
  while (p != NULL && p->info.cod < lib.cod)
  {
    ant = p;
    p = p->sig;
  }
  q->sig = p;
  if (p != lista)
    ant->sig = q;
  else
    lista = q;
}

void apareo(NodoL *lista, FILE *archLib, FILE *archLibAct)
{
  NodoL *p1 = lista;
  Libro lib;

  fread(&lib, sizeof(Libro), 1, archLib);
  while (p1 != NULL && !feof(archLib))
  {
    if (p1->info.cod < lib.cod)
    {
      fwrite(&p1->info, sizeof(Libro), 1, archLibAct);
      p1 = p1->sig;
    }
    else
    {
      if (p1->info.cod == lib.cod)
      {
        p1->info.cantEjemplares += lib.cantEjemplares;
        fwrite(&p1->info, sizeof(Libro), 1, archLibAct);
        p1 = p1->sig;
        fread(&lib, sizeof(Libro), 1, archLib);
      }
      else
      {
        fwrite(&lib, sizeof(Libro), 1, archLibAct);
        fread(&lib, sizeof(Libro), 1, archLib);
      }
    }
  }
  while (p1 != NULL)
  {
    fwrite(&p1->info, sizeof(Libro), 1, archLibAct);
    p1 = p1->sig;
  }
  while (!feof(archLib))
  {
    fwrite(&lib, sizeof(Libro), 1, archLibAct);
    fread(&lib, sizeof(Libro), 1, archLib);
  }
}

void mostrarArchivoLibrosActualizados()
{
  FILE *arch = fopen("LIBROSACT.dat", "rb");
  if (arch == NULL)
    cout << "ERROR" << endl;
  else
  {
    Libro lib;

    fread(&lib, sizeof(Libro), 1, arch);
    while (!feof(arch))
    {
      cout << "Cod: " << lib.cod << " Cant ejemplares: " << lib.cantEjemplares << endl;
      cout << "Apellido autor: " << lib.apellidoAutor << " Titulo libro: " << lib.titulo << endl;
      cout << "Nacionalidad: " << lib.nacionalidad << endl;
      cout << endl;
      fread(&lib, sizeof(Libro), 1, arch);
    }
    fclose(arch);
  }
}

// CON ORDEN
void generarArchivoLibros()
{
  FILE *archLib = fopen("LIBROS.dat", "wb");
  if (archLib == NULL)
    cout << "ERROR" << endl;
  else
  {
    Libro lib;
    lib.nacionalidad = 0;

    cout << "ARMANDO ARCHIVO LIBROS" << endl;
    cout << "Ingrese el codigo de libro (0 para finalizar): ";
    cin >> lib.cod;
    while (lib.cod != 0)
    {
      cout << "Ingrese el titulo del libro (30 caracteres max): ";
      fflush(stdin);
      cin.getline(lib.titulo, 30);

      cout << "Ingrese el apellido del autor (15 caracteres max): ";
      fflush(stdin);
      cin.getline(lib.apellidoAutor, 15);

      cout << "Ingrese la cantidad de ejemplares: ";
      cin >> lib.cantEjemplares;

      lib.nacionalidad++;

      fwrite(&lib, sizeof(Libro), 1, archLib);

      cout << "Ingrese el codigo de libro (0 para finalizar): ";
      cin >> lib.cod;
    }
    fclose(archLib);
  }
}

// SIN ORDEN
void generarArchivoNovedades()
{
  FILE *archNov = fopen("NOVEDADES.dat", "ab");
  if (archNov == NULL)
    cout << "ERROR" << endl;
  else
  {
    Libro lib;
    lib.nacionalidad = 0;

    cout << "ARMANDO ARCHIVO NOVEDADES" << endl;
    cout << "Ingrese el codigo de libro (0 para finalizar): ";
    cin >> lib.cod;
    while (lib.cod != 0)
    {
      cout << "Ingrese el titulo del libro (30 caracteres max): ";
      fflush(stdin);
      cin.getline(lib.titulo, 30);

      cout << "Ingrese el apellido del autor (15 caracteres max): ";
      fflush(stdin);
      cin.getline(lib.apellidoAutor, 15);

      cout << "Ingrese la cantidad de ejemplares: ";
      cin >> lib.cantEjemplares;

      lib.nacionalidad++;

      fwrite(&lib, sizeof(Libro), 1, archNov);

      cout << "Ingrese el codigo de libro (0 para finalizar): ";
      cin >> lib.cod;
    }
    fclose(archNov);
  }
}