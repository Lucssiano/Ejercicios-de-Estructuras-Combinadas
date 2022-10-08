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
