/* 5) Una compañía que ofrece préstamos a sus clientes a pagar en 12 meses, desea
obtener un listado con los códigos de clientes y los números de las cuotas
adeudadas de aquellos clientes que adeuden cuotas, ordenado por código de cliente.
Para ello cuenta con un archivo de cobranzas, sin ningún orden, con el siguiente diseño:
Código de cliente (int)
Número de cuota (1 a 12) */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct CobranzasArchivo
{
  int codigoCliente, nroCuota;
};

struct DatosCliente
{
  int codigoCliente;
  bool nroCuota[12];
};

struct NodoL
{
  DatosCliente info;
  NodoL *sig;
};

void generarArchivoCobranzas(); // Solo para probarlo
void inicializarVector(bool vCuotas[12]);
void armarLista(FILE *archCobranzas, NodoL *&lista);
void insertar(NodoL *&lista, DatosCliente dtsCliente);
void mostrarLista(NodoL *lista);
NodoL *buscarClienteYaIngresado(NodoL *lista, int codCliente);

int main()
{
  // generarArchivoCobranzas(); // Solo para probarlo
  FILE *archivoDeCobranzas = fopen("Cobranzas.dat", "rb");

  if (archivoDeCobranzas == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *lista = NULL;
    armarLista(archivoDeCobranzas, lista);
  }

  return 0;
}

void armarLista(FILE *archCobranzas, NodoL *&lista)
{
  CobranzasArchivo datosArch;
  DatosCliente datosClt;

  fread(&datosArch, sizeof(CobranzasArchivo), 1, archCobranzas);
  while (!feof(archCobranzas))
  {
    datosClt.codigoCliente = datosArch.codigoCliente;
    for (int i = 0; i < 12; i++)
      datosClt.nroCuota[i] = false;

    NodoL *clienteRepetido = buscarClienteYaIngresado(lista, datosArch.codigoCliente);

    datosClt.nroCuota[datosArch.nroCuota - 1] = true;
    if (!clienteRepetido)
      insertar(lista, datosClt);
    else
      clienteRepetido->info.nroCuota[datosArch.nroCuota - 1] = true;

    fread(&datosArch, sizeof(CobranzasArchivo), 1, archCobranzas);
  }
  mostrarLista(lista);
}

NodoL *buscarClienteYaIngresado(NodoL *lista, int codCliente)
{
  NodoL *p;
  p = lista;
  while (p != NULL && p->info.codigoCliente != codCliente)
    p = p->sig;
  return p;
}

void mostrarLista(NodoL *lista)
{
  NodoL *p = lista;
  while (p != NULL)
  {
    cout << "Codigo de cliente: " << p->info.codigoCliente << endl;
    for (int i = 0; i < 12; i++)
    {
      if (!p->info.nroCuota[i])
        cout << "Adeuda cuota " << i + 1 << endl;
    }
    cout << endl;
    p = p->sig;
  }
}

void insertar(NodoL *&lista, DatosCliente dtsCliente)
{
  NodoL *q, *p, *ant;
  q = new NodoL;
  q->info = dtsCliente;
  p = lista;
  while (p != NULL && p->info.codigoCliente < dtsCliente.codigoCliente)
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

void inicializarVector(bool vCuotas[12])
{
  for (int i = 0; i < 12; i++)
    vCuotas[i] = false;
}

void generarArchivoCobranzas()
{
  FILE *archivoDeCobranzas = fopen("Cobranzas.dat", "wb");
  if (archivoDeCobranzas == NULL)
    cout << "ERROR" << endl;
  else
  {
    CobranzasArchivo cobranza;

    cout << "ARMANDO ARCHIVO" << endl;
    cout << "Ingrese el codigo de cliente (0 para finalizar): ";
    cin >> cobranza.codigoCliente;
    while (cobranza.codigoCliente != 0)
    {
      cout << "Ingrese el numero de cuota (1 a 12): ";
      cin >> cobranza.nroCuota;

      fwrite(&cobranza, sizeof(CobranzasArchivo), 1, archivoDeCobranzas);

      cout << "Ingrese el codigo de cliente (0 para finalizar): ";
      cin >> cobranza.codigoCliente;
    }
    fclose(archivoDeCobranzas);
  }
}