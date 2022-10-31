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

#define cantCodDeptos 50

struct EmpleadoArchivo
{
  int numLeg, dni, codDepto;
  char nombreYApellido[36];
};

struct VacantesArchivo
{
  int codDepto, cantVacantes;
};

struct PostulantesArchivo
{
  int numLeg, codDepto;
};

struct DatosSublista
{
  int numLeg, dni;
  char nombreYApellido[36];
};

struct NodoSL
{
  DatosSublista info;
  NodoSL *sig;
};

struct DeptoPostulado
{
  int codDepto;
  NodoSL *subLista;
};

struct NodoL
{
  DeptoPostulado info;
  NodoL *sig;
};

void generarArchivoEmpleados();   // Solo para probarlo
void generarArchivoPostulantes(); // Solo para probarlo
void generarArchivoVacantes();    // Solo para probarlo
void puntoA(FILE *archPost, FILE *archEmple, NodoL *&listaPost);
NodoL *buscarInsertar(NodoL *&lista, DeptoPostulado deptoPost);
void insertarSinOrden(NodoSL *&lista, DatosSublista datSub);
void mostrarListado(NodoL *lista);
void puntoB(FILE *archVac, NodoL *&lista);
void mostrarArchivoActualizado();

int main()
{
  // generarArchivoEmpleados(); // Solo para probarlo
  // generarArchivoPostulantes(); // Solo para probarlo
  // generarArchivoVacantes(); // Solo para probarlo
  FILE *archivoDePostulantes = fopen("Postulantes.dat", "rb");
  FILE *archivoDeEmpleados = fopen("Empleados.dat", "rb");
  FILE *archivoDeVacantes = fopen("Vacantes.dat", "rb");

  if (archivoDePostulantes == NULL && archivoDeEmpleados == NULL && archivoDeVacantes == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *listaEmplePostulados = NULL;
    puntoA(archivoDePostulantes, archivoDeEmpleados, listaEmplePostulados);
    fclose(archivoDePostulantes);
    fclose(archivoDeEmpleados);
    puntoB(archivoDeVacantes, listaEmplePostulados);
    fclose(archivoDePostulantes);
    fclose(archivoDeEmpleados);
    fclose(archivoDeVacantes);
  }

  return 0;
}

void puntoA(FILE *archPost, FILE *archEmple, NodoL *&listaPost)
{
  DeptoPostulado deptoPost;
  PostulantesArchivo postulante;
  NodoL *p;
  EmpleadoArchivo empleado;
  DatosSublista datoSub;

  deptoPost.subLista = NULL;
  fread(&postulante, sizeof(PostulantesArchivo), 1, archPost);
  while (!feof(archPost))
  {
    deptoPost.codDepto = postulante.codDepto;
    p = buscarInsertar(listaPost, deptoPost);

    do
    {
      fread(&empleado, sizeof(EmpleadoArchivo), 1, archEmple);
    } while (!feof(archEmple) && empleado.numLeg != postulante.numLeg);
    fseek(archEmple, 0, SEEK_SET);

    if (empleado.numLeg == postulante.numLeg)
    {
      datoSub.numLeg = empleado.numLeg;
      datoSub.dni = empleado.dni;
      strcpy(datoSub.nombreYApellido, empleado.nombreYApellido);
      insertarSinOrden(p->info.subLista, datoSub);
    }
    else
    {
      cout << "No se encontro al cod de depto" << endl;
      fseek(archPost, 0, SEEK_SET);
    }
    fread(&postulante, sizeof(PostulantesArchivo), 1, archPost);
  }

  mostrarListado(listaPost);
}

NodoL *buscarInsertar(NodoL *&lista, DeptoPostulado deptoPost)
{
  NodoL *ant, *p = lista;
  while (p != NULL && p->info.codDepto < deptoPost.codDepto)
  {
    ant = p;
    p = p->sig;
  }
  if (p != NULL && deptoPost.codDepto == p->info.codDepto)
    return p;
  else
  {
    NodoL *n = new NodoL;
    n->info = deptoPost;
    n->sig = p;
    if (p != lista)
      ant->sig = n;
    else
      lista = n;
    return n;
  }
}

void insertarSinOrden(NodoSL *&lista, DatosSublista datSub)
{
  NodoSL *n, *p = lista;
  n = new NodoSL;
  n->info = datSub;
  if (p == NULL)
  {
    n->sig = p;
    lista = n;
  }
  else
  {
    p->sig = n;
    n->sig = NULL;
  }
}

void mostrarListado(NodoL *lista)
{
  NodoL *p = lista;
  NodoSL *q;

  while (p != NULL)
  {
    cout << endl;
    cout << "Codigo de depto: " << p->info.codDepto << endl;
    q = p->info.subLista;
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

void puntoB(FILE *archVac, NodoL *&lista)
{
  FILE *archivoDeEmpleados = fopen("EmpleadosActualizados.dat", "wb"); // deberia usar el mismo archivo pero para probar lo hago así
  if (archivoDeEmpleados == NULL)
    cout << "ERROR" << endl;
  else
  {
    VacantesArchivo vacanteArch;
    EmpleadoArchivo empleArch /* , empleadoOriginal */;

    // FILE *empleOrig = fopen("Empleados.dat", "rb");
    // do
    // {
    //   fread(&empleArch, sizeof(EmpleadoArchivo), 1, empleOrig);
    //   empleadoOriginal.codDepto = empleArch.codDepto;
    //   empleadoOriginal.numLeg = empleArch.numLeg;
    //   empleadoOriginal.dni = empleArch.dni;
    //   strcpy(empleadoOriginal.nombreYApellido, empleArch.nombreYApellido);
    //   fwrite(&empleadoOriginal, sizeof(EmpleadoArchivo), 1, archivoDeEmpleados);
    // } while (!feof(empleOrig));

    NodoL *p = lista;
    NodoSL *q;

    while (p != NULL)
    {
      do
      {
        fread(&vacanteArch, sizeof(VacantesArchivo), 1, archVac);
      } while (!feof(archVac) && vacanteArch.codDepto != p->info.codDepto);
      fseek(archVac, 0, SEEK_SET);

      if (vacanteArch.codDepto == p->info.codDepto)
      {
        int cantVacantes = vacanteArch.cantVacantes;
        empleArch.codDepto = p->info.codDepto;

        q = p->info.subLista;
        while (q != NULL)
        {
          if (cantVacantes > 0)
          {
            empleArch.numLeg = q->info.numLeg;
            empleArch.dni = q->info.dni;
            strcpy(empleArch.nombreYApellido, q->info.nombreYApellido);
            cantVacantes--;
            fwrite(&empleArch, sizeof(EmpleadoArchivo), 1, archivoDeEmpleados);
            q = q->sig;
          }
          else
            q = NULL;
        }
        p = p->sig;
      }
      else
        cout << "No se encontro al cod de depto" << endl;
    }
    fclose(archivoDeEmpleados);
    mostrarArchivoActualizado();
  }
}

void mostrarArchivoActualizado()
{
  FILE *archEmple = fopen("EmpleadosActualizados.dat", "rb");
  if (archEmple == NULL)
    cout << "ERROR" << endl;
  else
  {
    EmpleadoArchivo emple;

    cout << "ARCHIVO DE EMPLEADOS ACTUALIZADO" << endl;
    fread(&emple, sizeof(EmpleadoArchivo), 1, archEmple);
    while (!feof(archEmple))
    {
      cout << endl;
      cout << "Codigo de depto: " << emple.codDepto << endl;
      cout << "Dni del empleado: " << emple.dni << endl;
      cout << "Numero de legajo del empleado: " << emple.numLeg << endl;
      cout << "Nombre y apellido del empleado: " << emple.nombreYApellido << endl;
      /* FALTA QUE MUESTRE LARA KA QUE NO SE MOVIO DE DEPTO */
      fread(&emple, sizeof(EmpleadoArchivo), 1, archEmple);
    }
    fclose(archEmple);
  }
}

// Archivos
// void generarArchivoEmpleados()
// {
//   FILE *archEmple = fopen("Empleados.dat", "wb");
//   if (archEmple == NULL)
//     cout << "ERROR" << endl;
//   else
//   {
//     EmpleadoArchivo emple;

//     cout << "ARMANDO ARCHIVO DE EMPLEADOS" << endl;
//     cout << "Ingrese el codigo de depto (0 para finalizar): ";
//     cin >> emple.codDepto;
//     while (emple.codDepto != 0)
//     {
//       cout << "Ingrese el dni del empleado: ";
//       cin >> emple.dni;
//       cout << "Ingrese el numero de legajo del empleado: ";
//       cin >> emple.numLeg;
//       cout << "Ingrese nombre y apellido del empleado: ";
//       fflush(stdin);
//       cin.getline(emple.nombreYApellido, 36);

//       fwrite(&emple, sizeof(EmpleadoArchivo), 1, archEmple);

//       cout << "Ingrese el codigo de depto (0 para finalizar): ";
//       cin >> emple.codDepto;
//     }
//     fclose(archEmple);
//   }
// }

// void generarArchivoPostulantes()
// {
//   FILE *archPost = fopen("Postulantes.dat", "ab");
//   if (archPost == NULL)
//     cout << "ERROR" << endl;
//   else
//   {
//     PostulantesArchivo post;

//     cout << "ARMANDO ARCHIVO DE POSTULANTES" << endl;
//     cout << "Ingrese el codigo de depto (0 para finalizar): ";
//     cin >> post.codDepto;
//     while (post.codDepto != 0)
//     {
//       cout << "Ingrese el numero de legajo del empleado: ";
//       cin >> post.numLeg;

//       fwrite(&post, sizeof(PostulantesArchivo), 1, archPost);

//       cout << "Ingrese el codigo de depto (0 para finalizar): ";
//       cin >> post.codDepto;
//     }
//     fclose(archPost);
//   }
// }

// void generarArchivoVacantes()
// {
//   FILE *archVacantes = fopen("Vacantes.dat", "wb");
//   if (archVacantes == NULL)
//     cout << "ERROR" << endl;
//   else
//   {
//     VacantesArchivo vac;

//     cout << "ARMANDO ARCHIVO DE VACANTES" << endl;
//     cout << "Ingrese el codigo de depto (0 para finalizar): ";
//     cin >> vac.codDepto;
//     while (vac.codDepto != 0)
//     {
//       cout << "Ingrese la cantidad de vacantes: ";
//       cin >> vac.cantVacantes;

//       fwrite(&vac, sizeof(VacantesArchivo), 1, archVacantes);

//       cout << "Ingrese el codigo de depto (0 para finalizar): ";
//       cin >> vac.codDepto;
//     }
//     fclose(archVacantes);
//   }
// }

// Segundo programa - Intento con Cola
/*

struct NodoCola
{
  DatosSublista info;
  NodoCola *sig;
};

struct VectorColas
{
  NodoCola *pri;
  NodoCola *ult;
};

void inicializarVector(VectorColas v[cantCodDeptos])
{
  for (int i = 0; i < cantCodDeptos; i++)
  {
    v[i].pri = NULL;
    v[i].ult = NULL;
  }
}

void encolar(NodoCola *&pri, NodoCola *&ult, DatosSublista dato)
{
  NodoCola *p = new NodoCola;
  p->info = dato;
  p->sig = NULL;
  if (ult != NULL)
    ult->sig = p;
  else
    pri = p;
  ult = p;
}

DatosSublista desencolar(NodoCola *&pri, NodoCola *&ult)
{
  DatosSublista dato;
  NodoCola *p = pri;
  pri = p->sig;
  dato = p->info;
  delete p;
  if (pri == NULL)
    ult = NULL;
  return dato;
}

p = listaPost;

while (p)
{
  while (v[p->info.codDepto - 1].pri)
  {
    DatosSublista desencolado = desencolar(v[p->info.codDepto - 1].pri, v[p->info.codDepto - 1].ult);
    insertarSinOrden(p->info.subLista, desencolado);
  }
  p = p->sig;
}

encolar(v[postulante.codDepto - 1].pri, v[postulante.codDepto - 1].ult, datoSub);

*/

// Primer programa - Intento con Lista
/* void mostrarListado(NodoL *lista)
{
  NodoL *p = lista;
  NodoSL *q;

  while (p != NULL)
  {
    cout << endl;
    cout << "Codigo de depto: " << p->info.codDepto << endl;
    // q = p->info.sublista;
    while (q != NULL)
    {
      cout << "Numero de legajo: " << q->numLeg << endl;
      cout << "Numero de DNI: " << q->dni << endl;
      cout << "Nombre y Apellido: " << q->nombreYApellido << endl;
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

void puntoB(FILE *archVacantes, FILE *archEmple, NodoL *listaPost)
{
  archEmple = fopen("Empleados.dat", "wb");

  NodoL *p = listaPost;
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

 */