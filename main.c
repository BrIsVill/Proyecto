/* Programa para sumar n numeros 
 * Hecho por bVill
 * 
 * 
 */


#include <stdio.h>

int main(int argc, char **argv)
{
		int n, arreglo[100],indice;
	printf("Cuantos numeros se van a sumar?:");
	scanf("%d",&n);
	for(indice =0; indice <n; indice++)
		{
			printf("Cual es el numero n?: %d",indice);
			scanf("%d",&(arreglo[indice]));
			printf("%d/n", arreglo[indice]);
		}
	
	return 0;
}

