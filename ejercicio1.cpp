/* 1) En una empresa de construcción se quiere almacenar en un archivo los importes y
fechas de los materiales comprados para cada una de las obras que está construcción.

Para ello se ingresa por teclado, por cada compra de materiales realizada:
. El código de la obra, la fecha y el importe de la compra.
Los datos son ingresados sin orden. Para cada obra se puede haber comprado materiales varias veces.

Se pide generar un archivo secuencial con código de obra, fecha e importe,
ordenado por código de obra y por fecha, con los datos ingresados por teclado */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct CompraMateriales
{
  int fecha, impCompra;
};

struct NodoSL
{
  CompraMateriales info;
  NodoSL *sig;
};

struct Obra
{
  int codObra;
  NodoSL *subLista;
};

struct NodoL
{
  Obra info;
  NodoL *sig;
};

struct infoObraCompleto // Hay alguna manera de no armar este?
{
  int fecha, impCompra, codObra;
};

void generarLista(NodoL *&lista);
void generarArchivo(FILE *archMat, NodoL *lista);
void mostrarArchivo(FILE *archivo, NodoL *lista);
void insertar(NodoSL *&lista, CompraMateriales datCompra);
NodoL *buscarInsertar(NodoL *&lista, Obra datObra);

int main()
{
  NodoL *lista = NULL;
  // generarLista(lista);

  // FILE *archMateriales = fopen("MaterialesComprados.dat", "wb");
  // generarArchivo(archMateriales, lista);

  FILE *archMaterialesPrueba = fopen("MaterialesComprados.dat", "rb");
  mostrarArchivo(archMaterialesPrueba, lista);

  return 0;
}

void generarArchivo(FILE *archMat, NodoL *lista)
{
  if (archMat == NULL)
    cout << "ERROR" << endl;
  else
  {
    infoObraCompleto infoTotal;
    NodoL *p = lista;
    NodoSL *q;

    while (p != NULL)
    {
      infoTotal.codObra = p->info.codObra;
      q = p->info.subLista;
      while (q != NULL)
      {
        infoTotal.fecha = q->info.fecha;
        infoTotal.impCompra = q->info.impCompra;
        fwrite(&infoTotal, sizeof(infoObraCompleto), 1, archMat);
        q = q->sig;
      }
      p = p->sig;
    }
  }
  fclose(archMat);
  mostrarArchivo(archMat, lista);
}

void mostrarArchivo(FILE *archivo, NodoL *lista)
{
  archivo = fopen("MaterialesComprados.dat", "rb");
  if (archivo == NULL)
    cout << "ERROR" << endl;
  else
  {
    infoObraCompleto infoTotal;

    fread(&infoTotal, sizeof(infoObraCompleto), 1, archivo);
    while (!feof(archivo))
    {
      cout << endl;
      cout << "Cod obra: " << infoTotal.codObra << endl;
      cout << "Fecha de compra: " << infoTotal.fecha << endl;
      cout << "Importe de compra: " << infoTotal.impCompra << endl;
      fread(&infoTotal, sizeof(infoObraCompleto), 1, archivo);
    }
    fclose(archivo);
  }
}

void generarLista(NodoL *&lista)
{
  NodoL *p;
  CompraMateriales datosCompra;
  Obra datosObra;

  cout << "COMPRA DE MATERIALES" << endl;
  cout << "Ingrese el codigo de obra (0 para finalizar): ";
  cin >> datosObra.codObra;
  while (datosObra.codObra != 0)
  {
    cout << "Ingrese la fecha de la compra de materiales: ";
    cin >> datosCompra.fecha;

    cout << "Ingrese el importe de la compra de materiales: ";
    cin >> datosCompra.impCompra;

    datosObra.subLista = NULL;
    p = buscarInsertar(lista, datosObra);

    insertar(p->info.subLista, datosCompra);

    cout << "Ingrese el codigo de obra (0 para finalizar): ";
    cin >> datosObra.codObra;
  }
}

NodoL *buscarInsertar(NodoL *&lista, Obra datObra)
{
  NodoL *ant, *p = lista;
  while (p != NULL && p->info.codObra < datObra.codObra)
  {
    ant = p;
    p = p->sig;
  }
  if (p != NULL && datObra.codObra == p->info.codObra)
    return p;
  else
  {
    NodoL *n = new NodoL;
    n->info = datObra;
    n->sig = p;
    if (p != lista)
      ant->sig = n;
    else
      lista = n;
    return n;
  }
}

void insertar(NodoSL *&lista, CompraMateriales datCompra) // ordenado por fecha
{
  NodoSL *n, *p, *ant;
  n = new NodoSL;
  n->info = datCompra;
  p = lista;
  while (p != NULL && p->info.fecha < datCompra.fecha)
  {
    ant = p;
    p = p->sig;
  }
  n->sig = p;
  if (p != lista)
    ant->sig = n;
  else
    lista = n;
}