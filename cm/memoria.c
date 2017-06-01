#include <stdlib.h>
#include "memoria.h" 

/* alloca_memoria_campo si occupa di creare l area di memoria del campo e lo inizializza a zero */

casella_t** alloca_memoria_campo(int righe, int colonne)
{
	casella_t **campo_allocato;

	int i;
	int j;

	campo_allocato = malloc(righe * sizeof(casella_t *));
	for (i = 0; i < righe; i++)
	{
		campo_allocato[i] = malloc(colonne * sizeof(casella_t));
		for (j = 0; j < colonne; j++)
		{
			campo_allocato[i][j].bomba = 0;
			campo_allocato[i][j].bandiera = 0;
			campo_allocato[i][j].numero = 0;
			campo_allocato[i][j].scoperta = 0;
		}
	}

	return campo_allocato;
}


/* inserisci_bomba inserisce le bombe nel campo e contemporaneamente gestisce la corona di numeri che avvolge ogni bomba */

int inserisci_bomba(int righe, int colonne, int a, int b, casella_t** campo)
{
	/* qui gestisco i numeri in prossimità delle bombe in modo da non inserirli fuori dal campo */
	int bordo_superiore = (a == 0);
	int bordo_inferiore = (a == (righe - 1));
	int bordo_sinistro = (b == 0);
	int bordo_destro = (b == (colonne - 1));

	if (campo[a][b].bomba)
	{
		/* ritorno zero se e gia presente una bomba */
		return 0;
	}

	campo[a][b].bomba = 1;

	if (!bordo_superiore)
	{
		if (!bordo_sinistro)
		{
			/* top left* */
			campo[a - 1][b - 1].numero++;
		}

		/* top middle */
		campo[a - 1][b].numero++;

		if (!bordo_destro)
		{
			/* top right */
			campo[a - 1][b + 1].numero++;
		}
	}

	if (!bordo_sinistro)
	{
		/* middle left */
		campo[a][b - 1].numero++;
	}

	if (!bordo_destro)
	{
		/* middle right */
		campo[a][b + 1].numero++;
	}

	if (!bordo_inferiore)
	{
		if (!bordo_sinistro)
		{
			/* bottom left */
			campo[a + 1][b - 1].numero++;
		}

		/* bottom middle */
		campo[a + 1][b].numero++;

		if (!bordo_destro)
		{
			/* bottom right */
			campo[a + 1][b + 1].numero++;
		}
	}
	/* ritorno uno se l inserimento e andato a buon fine */
	return 1;
}


/* free_campo si occupa di liberare la memoria allocata per il campo, scorrendo il campo riga per riga */


void free_campo(int righe, casella_t** campo)
{
	int i;

	for (i = 0; i < righe; i++)
	{
		free(campo[i]);
	}
	free(campo);
}
