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
