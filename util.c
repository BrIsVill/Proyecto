/* Programa para sumar n numeros 
 * Hecho por bVill
 * 
 * 
 */


#include <stdio.h>

void leeArreglo(int n, int arreglo[])
{
		int indice;
	printf("Cuantos numeros se van a sumar?:");
	for(indice =0; indice <n; indice++)
		{
			printf("Cual es el numero n?: %d",indice);
			scanf("%d",&(arreglo[indice]));
			printf("%d/n", arreglo[indice]);
		}
	
}

