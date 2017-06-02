#include <stdlib.h>
#include <stdio.h>
#include "stampa_campo.h"

/* stampa_casella si occupa di stampare i caratteri voluti per ogni tipo di casella nel campo */

void stampa_casella(casella_t casella)
{
	if (casella.scoperta)
	{
		if (casella.bomba)
		{
			printf(" X ");
		}
		else if (casella.numero)
		{
			printf(" %d ", casella.numero);
		}
		else
		{
			printf("   ");
		}
	}
	else
	{
		if (casella.bandiera) 
		{
			printf(" F ");
		}
		else
		{
			printf(" ? ");
		}
	}
}

/* stampa_campo si occupa di stampare il campo a schermo, avendo cura di tradurre l input di colonna char a int, e creando la riga guida e la colonna 
   guida per l inserimento da parte dell utente delle coordinate durante la partita */

void stampa_campo(int righe, int colonne, casella_t** campo)
{
	int i;
	int j;

	for (j = 0; j < colonne; j++) 
	{
		printf(" %c ",j+65);
	}
	
	printf("\n");

	for (j = 0; j < colonne; j++)
	{
		printf("---");
	}
	
	for (i = 0; i < righe; i++)
	{
		printf("\n");

		for (j = 0; j < colonne; j++)
		{	
			stampa_casella(campo[i][j]);
		}
		printf("| %d", i);
	}
	printf("\n\n");
}
