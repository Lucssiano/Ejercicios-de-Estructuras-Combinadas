/* 3) Idem ejercicio 2, en el comercio hay 10 vendedores cuyo código de vendedor es un número
del 1 al 10 */

/* Dado el archivo VENTAS.DAT, ordenado por número de factura, con la siguiente
estructura de registro:
Número de factura (int)
Código de vendedor (int) (1 a 10)
Importe (float)
a) Imprima un listado ordenado por código de vendedor, con código de vendedor
y el detalle de cada venta, ordenadas de mayor a menor por importe.
b) Genere el archivo “VentasVendedor.dat” ordenado por código de vendedor,
con código de vendedor y el importe total de ventas. */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct DatosVentas
{
  int numFactura;
  float imp;
};

struct NodoL
{
  DatosVentas info;
  NodoL *sig;
};

struct DatosArchivoVentas
{
  int numFactura, codVendedor;
  float imp;
};

struct DatosVendedor
{
  int codVendedor;
  float impTotal;
};

void inicializarVector(NodoL *vecListas[10]);
void puntoA(FILE *archVentas, NodoL *vecListas[10]);
void insertar(NodoL *&lista, DatosVentas datVentas);
void mostrarLista(NodoL *vecListas[10]);
void puntoB(NodoL *vecListas[10]);
void mostrarArchivo(FILE *archivo);

int main()
{
  FILE *archivoDeVentas = fopen("VENTAS.dat", "rb");
  if (archivoDeVentas == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *vecCod[10];
    inicializarVector(vecCod);
    puntoA(archivoDeVentas, vecCod);
    puntoB(vecCod);
    return 0;
  }
}

void inicializarVector(NodoL *vecListas[10])
{
  for (int i = 0; i < 10; i++)
    vecListas[i] = NULL;
}

void puntoA(FILE *archVentas, NodoL *vecListas[10])
{
  DatosVentas infoVts;
  DatosArchivoVentas dtsArch;

  fread(&dtsArch, sizeof(DatosArchivoVentas), 1, archVentas);
  while (!feof(archVentas))
  {
    infoVts.imp = dtsArch.imp;
    infoVts.numFactura = dtsArch.numFactura;
    NodoL *listaALlenar = vecListas[dtsArch.codVendedor - 1];
    insertar(listaALlenar, infoVts);
    vecListas[dtsArch.codVendedor - 1] = listaALlenar;
    fread(&dtsArch, sizeof(DatosArchivoVentas), 1, archVentas);
  }
  fclose(archVentas);
  mostrarLista(vecListas);
}

void insertar(NodoL *&lista, DatosVentas datVentas)
{
  NodoL *q, *p, *ant;
  q = new NodoL;
  q->info = datVentas;
  p = lista;
  while (p != NULL && p->info.imp > datVentas.imp)
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

void mostrarLista(NodoL *vecListas[10])
{
  NodoL *p; // Lista que quiero mostrar del vector
  for (int i = 0; i < 10; i++)
  {
    cout << "--------------------" << endl;
    cout << "Codigo de vendedor: " << i + 1 << endl;
    p = vecListas[i];
    if (!p)
      cout << "No tiene ventas" << endl;

    while (p != NULL)
    {
      cout << "Importe: " << p->info.imp << endl;
      cout << "Numero de Factura: " << p->info.numFactura << endl;
      cout << endl;
      p = p->sig;
    }
  }
}

//  b) Genere el archivo “VentasVendedor.dat” ordenado por código de vendedor,
// con código de vendedor y el importe total de ventas.
void puntoB(NodoL *vecListas[10])
{
  FILE *archivoPuntoB = fopen("VentasVendedorPunto3.dat", "wb");
  if (archivoPuntoB == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosVendedor dtsVdor;
    NodoL *p;

    for (int i = 0; i < 10; i++)
    {
      p = vecListas[i];
      dtsVdor.codVendedor = i + 1;
      dtsVdor.impTotal = 0;
      while (p != NULL)
      {
        dtsVdor.impTotal += p->info.imp;
        p = p->sig;
      }
      fwrite(&dtsVdor, sizeof(DatosVendedor), 1, archivoPuntoB);
    }
  }
  fclose(archivoPuntoB);
  mostrarArchivo(archivoPuntoB);
}

void mostrarArchivo(FILE *archivo)
{
  archivo = fopen("VentasVendedorPunto3.dat", "rb");
  if (archivo == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosVendedor dtsVdor;

    fread(&dtsVdor, sizeof(DatosVendedor), 1, archivo);
    while (!feof(archivo))
    {
      if (dtsVdor.impTotal > 0)
      {
        cout << endl;
        cout << "Cod vendedor: " << dtsVdor.codVendedor << endl;
        cout << "Importe total de las ventas: " << dtsVdor.impTotal << endl;
      }
      fread(&dtsVdor, sizeof(DatosVendedor), 1, archivo);
    }
    fclose(archivo);
  }
}