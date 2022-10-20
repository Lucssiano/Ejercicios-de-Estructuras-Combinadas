/* 5) Una compañía que ofrece préstamos a sus clientes a pagar en 12 meses, desea
obtener un listado con los códigos de clientes y los números de las cuotas
adeudadas de aquellos clientes que adeuden cuotas, ordenado por código de cliente.
Para ello cuenta con un archivo de cobranzas, sin ningún orden, con el siguiente diseño:
Código de cliente (int)
Número de cuota (1 a 12) */
// El número de cuota de que sería? El número de cuota que llegó a pagar?

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Cobranzas
{
  int codigoCliente, nroCuota;
};

struct NodoL
{
  Cobranzas info;
  NodoL *sig;
};

// void generarArchivoCobranzas(); // Solo para probarlo

int main()
{
  // generarArchivoCobranzas(); // Solo para probarlo
  FILE *archivoDeCobranzas = fopen("Cobranzas.dat", "rb");

  if (archivoDeCobranzas == NULL)
    cout << "ERROR" << endl;
  else
  {
  }

  return 0;
}

void generarArchivoCompetidores()
{
  FILE *archivoDeCobranzas = fopen("Cobranzas.dat", "wb");
  if (archivoDeCobranzas == NULL)
    cout << "ERROR" << endl;
  else
  {
    Cobranzas cobranza;

    cout << "ARMANDO ARCHIVO" << endl;
    cout << "Ingrese el codigo de cliente (0 para finalizar): ";
    cin >> cobranza.codigoCliente;
    while (cobranza.codigoCliente != 0)
    {
      cout << "Ingrese el numero de cuota (1 a 12): ";
      cin >> cobranza.nroCuota;

      fwrite(&cobranza, sizeof(Cobranzas), 1, archivoDeCobranzas);

      cout << "Ingrese el codigo de cliente (0 para finalizar): ";
      cin >> cobranza.codigoCliente;
    }
    fclose(archivoDeCobranzas);
  }
}