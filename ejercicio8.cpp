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

struct DatosSubLista2
{
  int cantTitulos;
  char apellidoAutor[15];
};

struct NodoSL2
{
  DatosSubLista2 info;
  NodoSL2 *subSig;
};

struct DatosLista2
{
  int nacionalidad, cantAutores;
  NodoSL2 *subLista;
};

struct NodoL2
{
  DatosLista2 info;
  NodoL2 *sig;
};

void generarArchivoLibros();
void generarArchivoNovedades();
void punto1y2(FILE *archLibros, FILE *archNovedades);
void insertar(NodoL *&lista, Libro lib);
void apareo(NodoL *lista, FILE *archLib, FILE *archLibAct);
NodoL2 *buscarInsertarL2(NodoL2 *&lista, DatosLista2 datosLis2);
bool buscarInsertarSL2(NodoSL2 *&lista, DatosSubLista2 datosSubLis2);
void ordenarLista(NodoL2 *&lista);
void insertarOrdenado(NodoL2 *&lista, DatosLista2 datosLis2);
void mostrarArchivoLibrosActualizados();
void mostrarListadoPunto2(NodoL2 *lista);

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
    punto1y2(archivoDeLibros, archivoDeNovedades);
    fclose(archivoDeLibros);
    fclose(archivoDeNovedades);
  }
  return 0;
}

void punto1y2(FILE *archLibros, FILE *archNovedades)
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
  NodoL2 *lista2 = NULL;
  NodoL2 *p2;
  DatosLista2 datLis2;
  DatosSubLista2 datSubLis2;
  Libro lib;

  datLis2.subLista = NULL;
  fread(&lib, sizeof(Libro), 1, archLib);
  while (p1 != NULL && !feof(archLib))
  {
    if (p1->info.cod < lib.cod)
    {
      fwrite(&p1->info, sizeof(Libro), 1, archLibAct);

      datLis2.nacionalidad = p1->info.nacionalidad;
      p2 = buscarInsertarL2(lista2, datLis2);
      strcpy(datSubLis2.apellidoAutor, p1->info.apellidoAutor);
      if (buscarInsertarSL2(p2->info.subLista, datSubLis2))
        p2->info.cantAutores++;

      p1 = p1->sig;
    }
    else
    {
      if (p1->info.cod == lib.cod)
      {
        p1->info.cantEjemplares += lib.cantEjemplares;
        fwrite(&p1->info, sizeof(Libro), 1, archLibAct);

        datLis2.nacionalidad = p1->info.nacionalidad;
        p2 = buscarInsertarL2(lista2, datLis2);
        strcpy(datSubLis2.apellidoAutor, p1->info.apellidoAutor);
        if (buscarInsertarSL2(p2->info.subLista, datSubLis2))
          p2->info.cantAutores++;

        p1 = p1->sig;
        fread(&lib, sizeof(Libro), 1, archLib);
      }
      else
      {
        fwrite(&lib, sizeof(Libro), 1, archLibAct);

        datLis2.nacionalidad = lib.nacionalidad;
        p2 = buscarInsertarL2(lista2, datLis2);
        strcpy(datSubLis2.apellidoAutor, lib.apellidoAutor);
        if (buscarInsertarSL2(p2->info.subLista, datSubLis2))
          p2->info.cantAutores++;

        fread(&lib, sizeof(Libro), 1, archLib);
      }
    }
  }
  while (p1 != NULL)
  {
    fwrite(&p1->info, sizeof(Libro), 1, archLibAct);

    datLis2.nacionalidad = p1->info.nacionalidad;
    p2 = buscarInsertarL2(lista2, datLis2);
    strcpy(datSubLis2.apellidoAutor, p1->info.apellidoAutor);
    if (buscarInsertarSL2(p2->info.subLista, datSubLis2))
      p2->info.cantAutores++;

    p1 = p1->sig;
  }
  while (!feof(archLib))
  {
    fwrite(&lib, sizeof(Libro), 1, archLibAct);

    datLis2.nacionalidad = lib.nacionalidad;
    p2 = buscarInsertarL2(lista2, datLis2);
    strcpy(datSubLis2.apellidoAutor, lib.apellidoAutor);
    if (buscarInsertarSL2(p2->info.subLista, datSubLis2))
      p2->info.cantAutores++;

    fread(&lib, sizeof(Libro), 1, archLib);
  }
  ordenarLista(lista2);
  // mostrarListadoPunto2(lista2);
}

void ordenarLista(NodoL2 *&lista)
{
  NodoL2 *listaOrd = NULL;
  NodoL2 *r;
  while (lista != NULL)
  {
    r = lista;
    lista = lista->sig;
    insertarOrdenado(listaOrd, r->info);
    delete r;
  }
  lista = listaOrd;
  mostrarListadoPunto2(lista);
}

void insertarOrdenado(NodoL2 *&lista, DatosLista2 datosLis2)
{
  NodoL2 *q, *p, *ant;
  q = new NodoL2;
  q->info = datosLis2;
  p = lista;
  while (p != NULL && p->info.cantAutores > datosLis2.cantAutores)
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

void mostrarListadoPunto2(NodoL2 *lista)
{
  NodoL2 *p = lista;
  NodoSL2 *q;

  while (p)
  {
    q = p->info.subLista;

    cout << "Nacionalidad: " << p->info.nacionalidad << endl;
    cout << endl;
    cout << "Cantidad total de autores: " << p->info.cantAutores << endl;
    while (q)
    {
      cout << "Apellido del Autor: " << q->info.apellidoAutor << " Cantidad total de titulos: " << q->info.cantTitulos << endl;
      q = q->subSig;
    }
    cout << endl;

    p = p->sig;
  }
}

NodoL2 *buscarInsertarL2(NodoL2 *&lista, DatosLista2 datosLis2)
{
  NodoL2 *ant, *p = lista;

  while (p != NULL && datosLis2.nacionalidad != p->info.nacionalidad)
  {
    ant = p;
    p = p->sig;
  }

  if (p != NULL)
    return p;
  else
  {
    NodoL2 *n = new NodoL2;
    datosLis2.cantAutores = 0;
    n->info = datosLis2;
    n->sig = p;
    if (p != lista)
      ant->sig = n;
    else
      lista = n;
    return n;
  }
}

bool buscarInsertarSL2(NodoSL2 *&lista, DatosSubLista2 datosSubLis2)
{
  NodoSL2 *p = lista, *ant;

  while (p != NULL && strcmpi(p->info.apellidoAutor, datosSubLis2.apellidoAutor) != 0)
  {
    ant = p;
    p = p->subSig;
  }

  if (p != NULL)
  {
    p->info.cantTitulos++;
    return false;
  }
  else
  {
    NodoSL2 *q = new NodoSL2;
    datosSubLis2.cantTitulos = 1;
    q->info = datosSubLis2;
    q->subSig = p;
    if (p != lista)
      ant->subSig = q;
    else
      lista = q;
    return true;
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

      cout << "Nacionalidad: ";
      cin >> lib.nacionalidad;

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

      cout << "Nacionalidad: ";
      cin >> lib.nacionalidad;

      fwrite(&lib, sizeof(Libro), 1, archNov);

      cout << "Ingrese el codigo de libro (0 para finalizar): ";
      cin >> lib.cod;
    }
    fclose(archNov);
  }
}