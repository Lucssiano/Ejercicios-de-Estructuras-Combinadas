/* 7) En una empresa se quiere hacer una reestructuración de sus departamentos
administrativos, ofreciendo la posibilidad de cambios voluntarios de
departamentos a sus empleados

Para ello cuenta con los siguientes archivos:

- “Empleados.dat”, con un registro por cada empleado de la empresa, ordenado por
número de legajo, según el siguiente diseño:
. Número de legajo (int)
. Apellido y nombre
. Dni
. Código de departamento actual

- “Vacantes.dat”, con un registro por cada departamento en el que hay vacantes a
ofrecer a los empleados, sin orden, según el siguiente diseño:
. Código de departamento (1 a 50)
. Cantidad de vacantes

- “Postulantes.dat”, con un registro por cada postulación realizada, cada empleado
solo se pudo postular a una vacante, ordenado según se han postulado, con el
siguiente diseño:
. Número de legajo
. Código de departamento

Se pide desarrollar la metodología necesaria para realizar un algoritmo que permita:
a) Hacer un listado, ordenado por código de departamento, con todos los
empleados postulados al mismo por orden de llegada (número de legajo,
dni y apellido y nombre).
b) Asignar los postulantes a los departamentos según el orden de llegada y la
cantidad de vacantes requeridas, actualizando el archivo “Empleados.dat”
*/

#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct Empleado
{
  int numLeg, dni, codDepto;
  char nombreYApellido[36];
};

struct Vacantes
{
  int codDepto, cantVacantes;
};

struct NodoSL
{
  Empleado info; // no necesito el cod de depto
  NodoSL *sig;
};

struct Postulantes
{
  int numLeg, codDepto;
  NodoSL *sublista;
};

struct NodoL
{
  Postulantes info; // no necesito numLeg
  NodoL *sig;
};

void generarArchivoEmpleados();   // Solo para probarlo
void generarArchivoPostulantes(); // Solo para probarlo
// void generarArchivoVacantes(); // Solo para probarlo
void puntoA(FILE *archPost, FILE *archEmple, NodoL *&listaPost);
NodoL *buscarInsertar(NodoL *&lista, Postulantes post);
void insertar(NodoSL *&lista, Empleado emple);
void mostrarListado(NodoL *lista);
void puntoB(FILE *archVacantes, FILE *archEmple, NodoL *listaPost);

int main()
{
  // generarArchivoEmpleados();   // Solo para probarlo
  // generarArchivoPostulantes(); // Solo para probarlo
  // generarArchivoVacantes(); // Solo para probarlo
  FILE *archivoDePostulantes = fopen("Postulantes.dat", "rb");
  FILE *archivoDeEmpleados = fopen("Empleados.dat", "rb");
  FILE *archivoDeVacantes = fopen("Vacantes.dat", "rb");

  if (archivoDePostulantes == NULL && archivoDeEmpleados == NULL && archivoDeVacantes == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *lista = NULL;
    puntoA(archivoDePostulantes, archivoDeEmpleados, lista);
    fclose(archivoDePostulantes);
    fclose(archivoDeEmpleados);
    // puntoB(archivoDeEmpleados, archivoDeVacantes, lista);
  }

  return 0;
}

void puntoA(FILE *archPost, FILE *archEmple, NodoL *&listaPost)
{
  NodoL *p;
  Postulantes post;
  Empleado infoEmpleados;

  post.sublista = NULL;
  fread(&post, sizeof(Postulantes), 1, archPost);
  while (!feof(archPost))
  {

    p = buscarInsertar(listaPost, post);

    do
    {
      fread(&infoEmpleados, sizeof(Empleado), 1, archEmple);
    } while (!feof(archEmple) && infoEmpleados.numLeg != post.numLeg);

    if (infoEmpleados.numLeg == post.numLeg)
    {
      insertar(p->info.sublista, infoEmpleados);
      fseek(archEmple, 0, SEEK_SET);
      fread(&post, sizeof(Postulantes), 1, archPost);
    }
    else
    {
      cout << "No se encontro al cod de depto" << endl;
      fseek(archPost, 0, SEEK_END);
      fseek(archEmple, 0, SEEK_END);
    }
  }
  mostrarListado(listaPost);
}

void mostrarListado(NodoL *lista)
{
  NodoL *p = lista;
  NodoSL *q;

  while (p != NULL)
  {
    cout << endl;
    cout << "Codigo de depto: " << p->info.codDepto << endl;
    q = p->info.sublista;
    while (q != NULL)
    {
      cout << "Numero de legajo: " << q->info.numLeg << endl;
      cout << "Numero de DNI: " << q->info.dni << endl;
      cout << "Nombre y Apellido: " << q->info.nombreYApellido << endl;
      cout << endl;
      q = q->sig;
    }
    p = p->sig;
  }
}

NodoL *buscarInsertar(NodoL *&lista, Postulantes post)
{
  NodoL *ant, *p = lista;
  while (p != NULL && p->info.codDepto < post.codDepto)
  {
    ant = p;
    p = p->sig;
  }
  if (p != NULL && post.codDepto == p->info.codDepto)
    return p;
  else
  {
    NodoL *n = new NodoL;
    n->info = post;
    n->sig = p;
    if (p != lista)
      ant->sig = n;
    else
      lista = n;
    return n;
  }
}

void insertar(NodoSL *&lista, Empleado emple) // Por orden de llegada
{
  NodoSL *n, *p, *ant;
  n = new NodoSL;
  n->info = emple; // el cod de depto tambien se escribe pero no es necesario
  p = lista;
  while (p != NULL)
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

/* Asignar los postulantes a los departamentos según el orden de llegada y la
cantidad de vacantes requeridas, actualizando el archivo “Empleados.dat */
/* Tendria que guardar los datos de los empleados que hay hasta ahora en una lista y agregar los que estan en la lista que cree, eso despues pasarlo al archivo con wb (Reescribiendolo) */
void puntoB(FILE *archVacantes, FILE *archEmple, NodoL *listaPost)
{
  archEmple = fopen("Empleados.dat", "wb");

  // NodoL *p = listaPost;
  // NodoSL *q;

  // while (p != NULL)
  // {
  //   cout << endl;
  //   cout << "Codigo de depto: " << p->info.codDepto << endl;
  //   q = p->info.sublista;
  //   while (q != NULL)
  //   {
  //     cout << "Numero de legajo: " << q->info.numLeg << endl;
  //     cout << "Numero de DNI: " << q->info.dni << endl;
  //     cout << "Nombre y Apellido: " << q->info.nombreYApellido << endl;
  //     cout << endl;
  //     q = q->sig;
  //   }
  //   p = p->sig;
  // }
}

void generarArchivoEmpleados()
{
  FILE *archEmple = fopen("Empleados.dat", "ab");
  if (archEmple == NULL)
    cout << "ERROR" << endl;
  else
  {
    Empleado emple;

    cout << "ARMANDO ARCHIVO DE EMPLEADOS" << endl;
    cout << "Ingrese el codigo de depto (0 para finalizar): ";
    cin >> emple.codDepto;
    while (emple.codDepto != 0)
    {
      cout << "Ingrese el dni del empleado: ";
      cin >> emple.dni;
      cout << "Ingrese el numero de legajo del empleado: ";
      cin >> emple.numLeg;
      cout << "Ingrese nombre y apellido del empleado: ";
      fflush(stdin);
      cin.getline(emple.nombreYApellido, 36);

      fwrite(&emple, sizeof(Empleado), 1, archEmple);

      cout << "Ingrese el codigo de depto (0 para finalizar): ";
      cin >> emple.codDepto;
    }
    fclose(archEmple);
  }
}

void generarArchivoPostulantes()
{
  FILE *archPost = fopen("Postulantes.dat", "ab");
  if (archPost == NULL)
    cout << "ERROR" << endl;
  else
  {
    Postulantes post;

    cout << "ARMANDO ARCHIVO DE POSTULANTES" << endl;
    cout << "Ingrese el codigo de depto (0 para finalizar): ";
    cin >> post.codDepto;
    while (post.codDepto != 0)
    {
      cout << "Ingrese el numero de legajo del empleado: ";
      cin >> post.numLeg;

      fwrite(&post, sizeof(Postulantes), 1, archPost);

      cout << "Ingrese el codigo de depto (0 para finalizar): ";
      cin >> post.codDepto;
    }
    fclose(archPost);
  }
}

void generarArchivoVacantes()
{
  FILE *archVacantes = fopen("Vacantes.dat", "wb");
  if (archVacantes == NULL)
    cout << "ERROR" << endl;
  else
  {
    Vacantes vac;

    cout << "ARMANDO ARCHIVO DE VACANTES" << endl;
    cout << "Ingrese el codigo de depto (0 para finalizar): ";
    cin >> vac.codDepto;
    while (vac.codDepto != 0)
    {
      cout << "Ingrese la cantidad de vacantes: ";
      cin >> vac.cantVacantes;

      fwrite(&vac, sizeof(Vacantes), 1, archVacantes);

      cout << "Ingrese el codigo de depto (0 para finalizar): ";
      cin >> vac.codDepto;
    }
    fclose(archVacantes);
  }
}
