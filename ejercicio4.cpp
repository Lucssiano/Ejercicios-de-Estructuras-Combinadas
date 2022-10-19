/* 4) En un club deportivo barrial se quiere hacer un programa para obtener datos
estadísticos de los atletas que compitieron en el año 2019 en las 15 actividades
deportivas que se practican en el mismo.

Se tiene el archivo “Competidores.dat”, con cada una de las participaciones de los
atletas competencias, sin orden, donde cada registro tiene el siguiente formato:
Código de actividad (1..15)
Número de socio del atleta
Fecha de la competencia (struct dia, mes, anio)
Resultado (int)

Se pide:
a) Informar por cada actividad, por cada mes, cada uno de los atletas que
compitieron y el resultado obtenido, ordenado por código de actividad, por
mes y por número de socio.
b) Informar por cada mes del año el total de atletas que compitieron en cada
actividad.
c) Informar en qué actividad deportiva hubo más de un primer puesto. */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

#define codigoActividad 15
#define meses 12

struct Fecha
{
  int dia, mes, año;
};

struct DatosArchivo
{
  int codActividad, numSocio, resultado;
  Fecha fechaComp;
};

struct DatosListaCompetidores
{
  int numSocio, resultado;
};

struct NodoL
{
  DatosListaCompetidores info;
  NodoL *sig;
};

// void generarArchivoCompetidores(); // Solo para probarlo
void inicializarMatriz(NodoL *mt[codigoActividad][meses], int m, int n);
void puntoA(FILE *archComp, NodoL *mt[codigoActividad][meses]);
void insertar(NodoL *&lista, DatosListaCompetidores competidor);
void listar(NodoL *lista);
void mostrarPorColumna(NodoL *mt[codigoActividad][meses], int m, int n);
void puntoB(NodoL *mt[codigoActividad][meses], int m, int n);
int totalDeAtletasPorActividad(NodoL *lista);
void puntoC(NodoL *mt[codigoActividad][meses], int m, int n);
int totalPrimerPuesto(NodoL *lista);

int main()
{
  // generarArchivoCompetidores(); // Solo para probarlo
  FILE *archivoDeCompetidores = fopen("Competidores.dat", "rb");

  if (archivoDeCompetidores == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *matrizActividades[codigoActividad][meses]; // Matriz de listas

    inicializarMatriz(matrizActividades, codigoActividad, meses);

    puntoA(archivoDeCompetidores, matrizActividades);
    fclose(archivoDeCompetidores);
    puntoB(matrizActividades, codigoActividad, meses);
    puntoC(matrizActividades, codigoActividad, meses);
  }
  return 0;
}

void puntoA(FILE *archComp, NodoL *mt[codigoActividad][meses])
{
  DatosArchivo datosArch;

  fread(&datosArch, sizeof(DatosArchivo), 1, archComp);
  while (!feof(archComp))
  {
    NodoL *listaALlenar = mt[datosArch.codActividad - 1][datosArch.fechaComp.mes - 1];
    DatosListaCompetidores datosLista;

    datosLista.numSocio = datosArch.numSocio;
    datosLista.resultado = datosArch.resultado;
    insertar(listaALlenar, datosLista);
    mt[datosArch.codActividad - 1][datosArch.fechaComp.mes - 1] = listaALlenar;

    fread(&datosArch, sizeof(DatosArchivo), 1, archComp);
  }
  mostrarPorColumna(mt, codigoActividad, meses);
}

void puntoB(NodoL *mt[codigoActividad][meses], int m, int n) // Mostrar por columna de matrices
{
  for (int c = 0; c < n; c++)
  {
    cout << "-------------------------------" << endl;
    cout << "Mes " << c + 1 << endl;
    for (int f = 0; f < m; f++)
    {
      if (mt[f][c] != NULL)
      {
        cout << endl;
        cout << "Codigo de actividad " << f + 1 << endl;
        cout << "Total de atletas: " << totalDeAtletasPorActividad(mt[f][c]);
      }
    }
    cout << endl;
  }
}

int totalDeAtletasPorActividad(NodoL *lista) // Es como la funcion listar
{
  NodoL *p;
  p = lista;
  int totAtletas = 0;
  while (p != NULL)
  {
    totAtletas++;
    p = p->sig;
  }
  return totAtletas;
}

void puntoC(NodoL *mt[codigoActividad][meses], int m, int n) // Mostrar por fila de matrices
{
  for (int f = 0; f < m; f++)
  {
    int cantPrimerPuesto = 0;
    for (int c = 0; c < n; c++)
    {
      if (totalPrimerPuesto(mt[f][c]) >= 1)
        cantPrimerPuesto++;
    }
    if (cantPrimerPuesto > 1)
      cout << "Codigo de actividad " << f + 1 << " tiene " << cantPrimerPuesto << " primer puesto" << endl;
  }
}

int totalPrimerPuesto(NodoL *lista) // Es como la funcion listar
{
  NodoL *p;
  p = lista;
  int cantPrimerPuesto = 0;
  while (p != NULL)
  {
    if (p->info.resultado == 1)
      cantPrimerPuesto++;
    p = p->sig;
  }
  return cantPrimerPuesto;
}

void inicializarMatriz(NodoL *mt[codigoActividad][meses], int m, int n)
{
  for (int f = 0; f < m; f++)
    for (int c = 0; c < n; c++)
      mt[f][c] = NULL;
}

void mostrarPorColumna(NodoL *mt[codigoActividad][meses], int m, int n)
{
  for (int c = 0; c < n; c++)
  {
    cout << "Mes " << c + 1 << endl;
    for (int f = 0; f < m; f++)
    {
      if (mt[f][c] != NULL)
      {
        cout << endl;
        cout << "Codigo de actividad " << f + 1 << endl;
        listar(mt[f][c]); // mostrar de menor a mayor los codigo de actividad
      }
    }
    cout << endl;
  }
}

void listar(NodoL *lista)
{
  NodoL *p;
  p = lista;
  while (p != NULL)
  {
    cout << "Numero de socio: " << p->info.numSocio << endl;
    cout << "Resultado: " << p->info.resultado << endl;
    p = p->sig;
  }
}

void insertar(NodoL *&lista, DatosListaCompetidores competidor)
{
  NodoL *q, *p, *ant;
  q = new NodoL;
  q->info = competidor;
  p = lista;
  while (p != NULL && p->info.numSocio < competidor.numSocio)
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

void generarArchivoCompetidores()
{
  FILE *archCompetidores = fopen("Competidores.dat", "ab");
  if (archCompetidores == NULL)
    cout << "ERROR" << endl;
  else
  {
    DatosArchivo competidores;

    cout << "ARMANDO ARCHIVO" << endl;
    cout << "Ingrese el codigo de actividad del 1 al 15 (0 para finalizar): ";
    cin >> competidores.codActividad;
    while (competidores.codActividad != 0)
    {
      cout << "Ingrese el numero de socio del competidor: ";
      cin >> competidores.numSocio;
      cout << "Ingrese el resultado del competidor: ";
      cin >> competidores.resultado;
      cout << "Ingrese el mes de la competencia: ";
      cin >> competidores.fechaComp.mes;

      // faltaria agregar bien la fecha

      fwrite(&competidores, sizeof(DatosArchivo), 1, archCompetidores);

      cout << "Ingrese el codigo de actividad del 1 al 15 (0 para finalizar): ";
      cin >> competidores.codActividad;
    }
    fclose(archCompetidores);
  }
}