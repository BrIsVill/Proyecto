/* Programa para sumar n numeros 
 * Hecho por bVill
 * 
 * 
 */


#include <stdio.h>
#include "util.h"

int main(int argc, char **argv)
{
		int n, arreglo[100],indice,suma=0;
	printf("Cuantos numeros se van a sumar?:");
	scanf("%d",&n);
	leeArreglo(n, arreglo);
	for(indice=0; indice<n; indice++)
		suma+=arreglo[indice];
	printf("La suma es: %d", suma);
	return 0;
}

