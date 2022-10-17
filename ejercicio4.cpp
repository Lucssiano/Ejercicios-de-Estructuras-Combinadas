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

struct Fecha
{
  int dia, mes, año;
};

struct DatosCompetidores
{
  int codActividad, numSocio, resultado;
  Fecha fechaComp;
};

// void generarArchivoCompetidores(); // Solo para probarlo
void puntoA(FILE *archComp);
void puntoB();
void puntoC();

int main()
{
  // generarArchivoCompetidores(); // Solo para probarlo
  FILE *archivoDeCompetidores = fopen("Competidores.dat", "rb");

  puntoA(archivoDeCompetidores);
  puntoB();
  puntoC();

  return 0;
}

/* Informar por cada actividad, por cada mes, cada uno de los atletas que
compitieron y el resultado obtenido, ordenado por código de actividad, por
mes y por número de socio. */
void puntoA(FILE *archComp)
{
  if (archComp == NULL)
    cout << "ERROR" << endl;
  else
  {

    fclose(archComp);
  }
}

void puntoB()
{
}

void puntoC()
{
}

// void generarArchivoCompetidores()
// {
//   FILE *archVentas = fopen("Competidores.dat", "wb");
//   if (archVentas == NULL)
//     cout << "ERROR" << endl;
//   else
//   {
//     DatosArchivoVentas ventas;

//     cout << "ARMANDO ARCHIVO" << endl;
//     cout << "Ingrese el codigo de vendedor (0 para finalizar): ";
//     cin >> ventas.codVendedor;
//     while (ventas.codVendedor != 0)
//     {
//       cout << "Ingrese el numero de factura de la venta: ";
//       cin >> ventas.numFactura;
//       cout << "Ingrese el importe de la venta: ";
//       cin >> ventas.imp;
//       fwrite(&ventas, sizeof(DatosArchivoVentas), 1, archVentas);

//       cout << "Ingrese el codigo de vendedor (0 para finalizar): ";
//       cin >> ventas.codVendedor;
//     }
//     fclose(archVentas);
//   }
// }