/* 2) Dado el archivo VENTAS.DAT, ordenado por número de factura, con la siguiente
estructura de registro:
Número de factura (int)
Código de vendedor (int)
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

struct NodoSL
{
  DatosVentas info;
  NodoSL *sig;
};

struct Vendedor
{
  int codVendedor;
  NodoSL *subLista;
};

struct NodoL
{
  Vendedor info;
  NodoL *sig;
};

struct DatosArchivoVentas // Hay alguna manera, al igual que en el 1, para que esto no lo tenga que usar? // Capaz obviando el otro dato que no necesito y dejarlo con basura
{
  int numFactura, codVendedor;
  float imp;
};

struct DatosVendedor // Hay alguna manera, al igual que en el 1, para que esto no lo tenga que usar?
{
  int codVendedor;
  float impTotal;
};

// void generarArchivoVentas(); // Solo para probarlo
void puntoA(FILE *archVentas, NodoL *&lista);
NodoL *buscarInsertar(NodoL *&lista, Vendedor vdor);
void insertar(NodoSL *&lista, DatosVentas datVentas);
void mostrarLista(NodoL *lista);
void puntoB(NodoL *&lista);
void mostrarArchivo(FILE *archivo);

int main()
{
  // generarArchivoVentas(); // Solo para probarlo
  FILE *archivoDeVentas = fopen("VENTAS.dat", "rb");
  NodoL *lista = NULL;

  puntoA(archivoDeVentas, lista);
  puntoB(lista);

  return 0;
}

void puntoA(FILE *archVentas, NodoL *&lista)
{
  if (archVentas == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *p;
    Vendedor vdor;
    DatosVentas infoVts;
    DatosArchivoVentas dtsArch;

    vdor.subLista = NULL;
    fread(&dtsArch, sizeof(DatosArchivoVentas), 1, archVentas);
    while (!feof(archVentas))
    {
      vdor.codVendedor = dtsArch.codVendedor;
      p = buscarInsertar(lista, vdor);

      infoVts.imp = dtsArch.imp;
      infoVts.numFactura = dtsArch.numFactura;
      insertar(p->info.subLista, infoVts);

      fread(&dtsArch, sizeof(DatosArchivoVentas), 1, archVentas);
    }
    fclose(archVentas);
    mostrarLista(lista);
  }
}

void puntoB(NodoL *&lista)
{
  FILE *archivoPuntoB = fopen("VentasVendedor.dat", "wb");
  if (archivoPuntoB == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosVendedor dtsVdor;
    NodoL *p = lista;
    NodoSL *q;

    while (p != NULL)
    {
      dtsVdor.codVendedor = p->info.codVendedor;
      dtsVdor.impTotal = 0;
      q = p->info.subLista;
      while (q != NULL)
      {
        dtsVdor.impTotal += q->info.imp;
        q = q->sig;
      }
      fwrite(&dtsVdor, sizeof(DatosVendedor), 1, archivoPuntoB);
      p = p->sig;
    }
  }
  fclose(archivoPuntoB);
  mostrarArchivo(archivoPuntoB);
}

void mostrarArchivo(FILE *archivo)
{
  archivo = fopen("VentasVendedor.dat", "rb");
  if (archivo == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosVendedor dtsVdor;

    fread(&dtsVdor, sizeof(DatosVendedor), 1, archivo);
    while (!feof(archivo))
    {
      cout << endl;
      cout << "Cod vendedor: " << dtsVdor.codVendedor << endl;
      cout << "Importe total de las ventas: " << dtsVdor.impTotal << endl;
      fread(&dtsVdor, sizeof(DatosVendedor), 1, archivo);
    }
    fclose(archivo);
  }
}

void mostrarLista(NodoL *lista)
{
  NodoL *p = lista;
  NodoSL *q;

  while (p != NULL)
  {
    cout << "--------------------" << endl;
    cout << "Codigo de vendedor: " << p->info.codVendedor << endl;
    q = p->info.subLista;
    while (q != NULL)
    {
      cout << "Importe: " << q->info.imp << endl;
      cout << "Numero de Factura: " << q->info.numFactura << endl;
      cout << endl;
      q = q->sig;
    }
    p = p->sig;
  }
}

NodoL *buscarInsertar(NodoL *&lista, Vendedor vdor)
{
  NodoL *ant, *p = lista;
  while (p != NULL && p->info.codVendedor < vdor.codVendedor)
  {
    ant = p;
    p = p->sig;
  }
  if (p != NULL && vdor.codVendedor == p->info.codVendedor)
    return p;
  else
  {
    NodoL *n = new NodoL;
    n->info = vdor;
    n->sig = p;
    if (p != lista)
      ant->sig = n;
    else
      lista = n;
    return n;
  }
}

void insertar(NodoSL *&lista, DatosVentas datVentas) // ordenado de MAYOR a MENOR por importe
{
  NodoSL *n, *p, *ant;
  n = new NodoSL;
  n->info = datVentas;
  p = lista;
  while (p != NULL && p->info.imp > datVentas.imp)
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

void generarArchivoVentas()
{
  FILE *archVentas = fopen("VENTAS.dat", "wb");
  if (archVentas == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosArchivoVentas ventas;

    cout << "ARMANDO ARCHIVO" << endl;
    cout << "Ingrese el codigo de vendedor (0 para finalizar): ";
    cin >> ventas.codVendedor;
    while (ventas.codVendedor != 0)
    {
      cout << "Ingrese el numero de factura de la venta: ";
      cin >> ventas.numFactura;
      cout << "Ingrese el importe de la venta: ";
      cin >> ventas.imp;
      fwrite(&ventas, sizeof(DatosArchivoVentas), 1, archVentas);

      cout << "Ingrese el codigo de vendedor (0 para finalizar): ";
      cin >> ventas.codVendedor;
    }
    fclose(archVentas);
  }
}