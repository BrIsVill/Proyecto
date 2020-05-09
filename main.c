/* Programa para sumar n numeros 
 * Hecho por bVill
 * 
 * 
 */


#include <stdio.h>
#include "util.h"

int main(int argc, char **argv)
{
		int n, arreglo[100],indice;
	printf("Cuantos numeros se van a sumar?:");
	scanf("%d",&n);
	leeArreglo(n, arreglo);
	return 0;
}

