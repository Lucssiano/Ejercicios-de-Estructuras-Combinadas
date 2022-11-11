#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct ArchivoCredito
{
  int codCredito, cupos;
  char descrip[36];
};

struct ArchivoInscripto
{
  int dni, codCredito, ingMensual;
  char apellidoYNombre[36];
};

struct Inscripto
{
  int dni, ingMensual;
  char apellidoYNombre[36];
};

struct NodoSL
{
  Inscripto info;
  NodoSL *subSig;
};

struct Credito
{
  int codCredito, cupos;
  NodoSL *subLista;
};

struct NodoL
{
  Credito info;
  NodoL *sig;
};

void generarArchivoCreditos();
void generarArchivoInscriptos();
void armarEstructuras(NodoL *&listaCred, FILE *archCred, FILE *archInsc);
void insertarListaCred(NodoL *&lista, Credito cred);
NodoL *buscarInsertar(NodoL *&lista, int codCredito);
void insertar(NodoSL *&lista, Inscripto insc);
void mostrarListado(NodoL *lista);

int main()
{
  // generarArchivoCreditos();   // Solo para probarlo
  // generarArchivoInscriptos(); // Solo para probarlo
  FILE *archivoCreditos = fopen("Creditos.dat", "rb");
  FILE *archivoInscriptos = fopen("Inscriptos.dat", "rb");

  if (archivoCreditos == NULL || archivoInscriptos == NULL)
    cout << "ERROR" << endl;
  else
  {
    NodoL *listaCreditos = NULL;
    armarEstructuras(listaCreditos, archivoCreditos, archivoInscriptos);
    mostrarListado(listaCreditos);
  }
  return 0;
}

void armarEstructuras(NodoL *&listaCred, FILE *archCred, FILE *archInsc)
{
  ArchivoCredito datosArchCred;
  Credito cred;

  cred.subLista = NULL;
  fread(&datosArchCred, sizeof(ArchivoCredito), 1, archCred);
  while (!feof(archCred))
  {
    cred.codCredito = datosArchCred.codCredito;
    cred.cupos = datosArchCred.cupos;
    insertarListaCred(listaCred, cred);
    fread(&datosArchCred, sizeof(ArchivoCredito), 1, archCred);
  }
  fclose(archCred);

  ArchivoInscripto datosArchInsc;
  Inscripto insc;
  NodoL *p;
  fread(&datosArchInsc, sizeof(ArchivoInscripto), 1, archInsc);
  while (!feof(archInsc))
  {
    p = buscarInsertar(listaCred, datosArchInsc.codCredito);

    if (p != NULL)
    {
      insc.dni = datosArchInsc.dni;
      insc.ingMensual = datosArchInsc.ingMensual;
      strcpy(insc.apellidoYNombre, datosArchInsc.apellidoYNombre);
      insertar(p->info.subLista, insc);
    }
    else
    {
      cout << "No se encontro el codigo de credito " << datosArchInsc.codCredito << endl;
    }
    fread(&datosArchInsc, sizeof(ArchivoInscripto), 1, archInsc);
  }
  fclose(archInsc);
}

void insertarListaCred(NodoL *&lista, Credito cred)
{
  NodoL *q, *p, *ant;
  q = new NodoL;
  q->info = cred;
  p = lista;
  while (p != NULL && p->info.codCredito < cred.codCredito)
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

NodoL *buscarInsertar(NodoL *&lista, int codCredito)
{
  NodoL *ant, *p = lista;
  while (p != NULL && p->info.codCredito < codCredito)
  {
    ant = p;
    p = p->sig;
  }
  if (p != NULL && p->info.codCredito == codCredito)
    return p;
  else
    return NULL;
}

void insertar(NodoSL *&lista, Inscripto insc) // ordenado de MAYOR a MENOR por ingreso mensual
{
  NodoSL *n, *p = lista, *ant;
  n = new NodoSL;
  n->info = insc;
  while (p != NULL && p->info.ingMensual > insc.ingMensual)
  {
    ant = p;
    p = p->subSig;
  }
  n->subSig = p;
  if (p != lista)
    ant->subSig = n;
  else
    lista = n;
}

void mostrarListado(NodoL *lista)
{
  NodoL *p = lista;
  NodoSL *q;

  while (p != NULL)
  {
    cout << "--------------------" << endl;
    cout << "Codigo de credito: " << p->info.codCredito << endl;
    q = p->info.subLista;
    while (q != NULL)
    {
      if (p->info.cupos >= 1)
      {
        cout << "DNI: " << q->info.dni << endl;
        cout << "Apellido y Nombre: " << q->info.apellidoYNombre << endl;
        cout << "Ingreso mensual: " << q->info.ingMensual << endl;
        cout << endl;
        p->info.cupos--;
        q = q->subSig;
      }
      else
      {
        cout << "No hay mas cupos en el codigo de credito " << p->info.codCredito << endl;
        q = NULL;
      }
    }
    p = p->sig;
  }
}

void generarArchivoCreditos()
{
  FILE *archCred = fopen("Creditos.dat", "wb");
  if (archCred == NULL)
    cout << "ERROR" << endl;
  else
  {
    ArchivoCredito cred;

    cout << "ARMANDO ARCHIVO DE CREDITOS" << endl;
    cout << "Ingrese el codigo de credito (0 para finalizar): ";
    cin >> cred.codCredito;
    while (cred.codCredito != 0)
    {
      cout << "Ingrese el cupos del credito: ";
      cin >> cred.cupos;

      strcpy(cred.descrip, "DESCRIPCION");

      fwrite(&cred, sizeof(ArchivoCredito), 1, archCred);

      cout << "Ingrese el codigo de credito (0 para finalizar): ";
      cin >> cred.codCredito;
    }
    fclose(archCred);
  }
}

void generarArchivoInscriptos()
{
  FILE *archInsc = fopen("Inscriptos.dat", "wb");
  if (archInsc == NULL)
    cout << "ERROR" << endl;
  else
  {
    ArchivoInscripto insc;

    cout << "ARMANDO ARCHIVO DE INSCRIPTOS" << endl;
    cout << "Ingrese el codigo de credito (0 para finalizar): ";
    cin >> insc.codCredito;
    while (insc.codCredito != 0)
    {
      cout << "Ingrese el dni del inscripto: ";
      cin >> insc.dni;

      cout << "Ingrese el nombre y apellido del inscripto: ";
      fflush(stdin);
      cin.getline(insc.apellidoYNombre, 36);

      cout << "Ingrese el ingreso mensual del inscripto: ";
      cin >> insc.ingMensual;

      fwrite(&insc, sizeof(ArchivoInscripto), 1, archInsc);

      cout << "Ingrese el codigo de credito (0 para finalizar): ";
      cin >> insc.codCredito;
    }
    fclose(archInsc);
  }
}
