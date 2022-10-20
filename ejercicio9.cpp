/* 9) Un restaurant desea manejar en forma computarizada las adiciones de sus mesas.
Para ello dispone de los siguientes datos:
a) Un archivo de platos y bebidas, ordenado por código de plato con el siguiente
diseño:
. Código de plato (1 a 200)
. Descripción del plato (40 caracteres)
. Precio unitario (float)
b) Número de factura inicial y fecha del día.
c) Por cada producto servido se ingresan por teclado la siguiente información:
. Número de mesa (1..48)
. Código de operación (‘A’, ‘B’, ‘F’)
. Código de plato (1..200)
. Unidades pedidas

Operación A: significa plato servido
Operación B: significa devolución del plato
Operación F: fin del pedido, emitir la adición y el campo de código de plato
contiene el número del mozo (1..10) que atendió esa mesa.

Cuando se ingrese nro de mesa igual a 0 indica fin del día. En caso de que queden
adiciones pendientes, informar una leyenda.

Se pide realizar un programa que:
1. Imprima la factura de cada mesa que fue ocupada:

Restaurant Fecha :.................. Factura:.......................
 Cant Descripción Precio Unitario Importe
 ....... ................... ............ ............
Mozo: .... Total:........................

Los platos deben estar ordenados por código de plato y acumuladas las unidades en
caso de repetición.

2. Grabar un archivo de facturación con los siguientes datos: fecha, número
de factura, mesa, mozo, e importe.

3. Al final del día emitir un listado con el total a cobrar por cada mozo,
ordenado por número de mozo (cobran el 1% sobre cada adición) */

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

// arch platos y bebidas
struct Plato
{
  int cod;
  float precio;
  char descrip[40];
};

int main()
{

  return 0;
}