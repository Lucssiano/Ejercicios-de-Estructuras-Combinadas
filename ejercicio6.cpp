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

struct Infraccion
{
  char patente[7];
  int fecha, cod; // la fecha está de adorno mepa
};

struct NodoL
{
  Infraccion info;
  NodoL *sig;
};

// void generarArchivoInfracciones (); // Solo para probarlo

int main()
{
  // generarArchivoInfracciones (); // Solo para probarlo
  FILE *archivoDeInfracciones = fopen("Infracciones.dat", "rb");

  if (archivoDeInfracciones == NULL)
    cout << "ERROR" << endl;
  else
  {
    /* Se desea obtener un listado ordenado por código de infracción decreciente con las
patentes que cometieron más de una vez la misma infracción. */
  }
  return 0;
}

// void listar(NodoL *lista)
// {
//   NodoL *p;
//   p = lista;
//   while (p != NULL)
//   {
//     cout << "Numero de socio: " << p->info.numSocio << endl;
//     cout << "Resultado: " << p->info.resultado << endl;
//     p = p->sig;
//   }
// }
