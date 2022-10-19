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

// Un vector de punteros que cada posicion apunta a una lista por cada vendedor

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
  int codVendedor[10];
  NodoL *sig;
};

// struct DatosArchivoVentas // Hay alguna manera, al igual que en el 1, para que esto no lo tenga que usar?
// {
//   int numFactura, codVendedor;
//   float imp;
// };

// struct DatosVendedor // Hay alguna manera, al igual que en el 1, para que esto no lo tenga que usar?
// {
//   int codVendedor;
//   float impTotal;
// };

// void generarArchivoVentas(); // Solo para probarlo
void puntoA(FILE *archVentas, NodoL *&lista);
// NodoL *buscarInsertar(NodoL *&lista, Vendedor vdor);
// void insertar(NodoSL *&lista, DatosVentas datVentas);
// void mostrarLista(NodoL *&lista); // Solo para probarlo
// void puntoB(NodoL *&lista);
// void mostrarArchivo(FILE *archivo, NodoL *lista); // Solo para probarlo

int main()
{
  // generarArchivoVentas(); // Solo para probarlo
  FILE *archivoDeVentas = fopen("VENTAS.dat", "rb");
  NodoL *lista = NULL;
  puntoA(archivoDeVentas, lista);

  return 0;
}

// void puntoA(FILE *archVentas, NodoL *&lista)
// {
//   if (archVentas == NULL)
//     cout << "ERROR" << endl;
//   else
//   {
//     NodoL *p;
//     Vendedor vdor;
//     DatosVentas infoVts;
//     DatosArchivoVentas dtsArch;

//     vdor.subLista = NULL;
//     fread(&dtsArch, sizeof(DatosArchivoVentas), 1, archVentas);
//     while (!feof(archVentas))
//     {
//       vdor.codVendedor = dtsArch.codVendedor;
//       p = buscarInsertar(lista, vdor);

//       infoVts.imp = dtsArch.imp;
//       infoVts.numFactura = dtsArch.numFactura;
//       insertar(p->info.subLista, infoVts);

//       fread(&dtsArch, sizeof(DatosArchivoVentas), 1, archVentas);
//     }
//     fclose(archVentas);
//     // mostrarLista(lista); // Solo para probarlo
//   }
// }