/* 6) La ciudad de Buenos Aires requiere un estudio estadístico de infracciones
realizadas por los vehículos en sus calles. Para ello cuenta con un archivo de
infracciones “Infracciones.dat”, ordenado por fecha de la infracción creciente, con
el siguiente diseño:
. Patente (7 caracteres)
. Fecha de Infracción (int, aammdd)
. Código de infracción (int, 1 a 100)
Se desea obtener un listado ordenado por código de infracción decreciente con las
patentes que cometieron más de una vez la misma infracción. */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct DatosArchivo
{
  char patente[8];
  int fecha, cod;
};

struct Infraccion
{
  char patente[8];
  int fecha, contInfra;
};

struct NodoL
{
  Infraccion info;
  NodoL *sig;
};

void generarArchivoInfracciones(); // Solo para probarlo
void inicializarVector(NodoL *vecInfra[100]);
void generarListado(NodoL *vecInfra[100], FILE *archInfra);
void mostrarListado(NodoL *vecInfra[100]);
void *buscarInsertar(NodoL *&lista, Infraccion infra);

int main()
{
  // generarArchivoInfracciones(); // Solo para probarlo
  FILE *archivoDeInfracciones = fopen("Infracciones.dat", "rb");

  if (archivoDeInfracciones == NULL)
    cout
        << "ERROR" << endl;
  else
  {
    NodoL *vecInfracciones[100];
    inicializarVector(vecInfracciones);
    generarListado(vecInfracciones, archivoDeInfracciones);
    fclose(archivoDeInfracciones);
    mostrarListado(vecInfracciones);
  }
  return 0;
}

void generarListado(NodoL *vecInfra[100], FILE *archInfra)
{
  DatosArchivo datosArch;
  Infraccion datosInfra;

  fread(&datosArch, sizeof(DatosArchivo), 1, archInfra);
  while (!feof(archInfra))
  {
    datosInfra.fecha = datosArch.fecha;
    strcpy(datosInfra.patente, datosArch.patente);
    buscarInsertar(vecInfra[datosArch.cod - 1], datosInfra);
    fread(&datosArch, sizeof(DatosArchivo), 1, archInfra);
  }
}

void *buscarInsertar(NodoL *&lista, Infraccion infra)
{
  NodoL *p = lista, *ant;

  while (p != NULL && strcmpi(p->info.patente, infra.patente) != 0)
  {
    ant = p;
    p = p->sig;
  }

  if (p == NULL || strcmpi(p->info.patente, infra.patente) != 0)
  {
    NodoL *q = new NodoL;
    infra.contInfra = 1;
    q->info = infra;
    q->sig = p;
    if (p != lista)
      ant->sig = q;
    else
      lista = q;
  }
  else
    p->info.contInfra++;
}

void mostrarListado(NodoL *vecInfra[100])
{
  NodoL *p;
  for (int i = 99; i >= 0; i--)
  {
    p = vecInfra[i];

    while (p != NULL)
    {
      if (p->info.contInfra > 1)
        cout << "La patente " << p->info.patente << " cometio la infraccion numero " << i + 1 << " - " << p->info.contInfra << " veces" << endl;
      p = p->sig;
    }
  }
}

void inicializarVector(NodoL *vecInfra[100])
{
  for (int i = 0; i < 100; i++)
    vecInfra[i] = NULL;
}

void generarArchivoInfracciones()
{
  FILE *archivoDeInfracciones = fopen("Infracciones.dat", "wb");
  if (archivoDeInfracciones == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosArchivo datosArch;

    cout << "ARMANDO ARCHIVO" << endl;
    cout << "Ingrese el codigo de patente (1 a 100) (0 para finalizar): ";
    cin >> datosArch.cod;
    while (datosArch.cod != 0)
    {
      cout << "Ingrese la fecha de la infraccion (aammdd): ";
      cin >> datosArch.fecha;

      cout << "Ingrese la patente (7 digitos): ";
      fflush(stdin);
      cin.getline(datosArch.patente, 8);

      fwrite(&datosArch, sizeof(DatosArchivo), 1, archivoDeInfracciones);

      cout << "Ingrese el codigo de patente (1 a 100) (0 para finalizar): ";
      cin >> datosArch.cod;
    }
    fclose(archivoDeInfracciones);
  }
}