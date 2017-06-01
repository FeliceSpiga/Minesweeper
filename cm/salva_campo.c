#include <stdio.h>
#include "salva_campo.h"

/* salva_campo si occupa di scrivere nel file di testo le dimensioni del campo e tute le coordinate delle bombe */

void salva_campo(int righe, int colonne, casella_t** campo)
{
	int i;
	int j;

	FILE *fp;
	fp = fopen("mappa.txt", "w");
	/* gestione del caso NULL file */
	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(1);
	}
	/* scriviamo la dimensione del campo nella prima riga del file */
	fprintf(fp, "%d, %d\n\n", righe, colonne);
	/* scriviamo le coordinate delle bombe */
	for (i = 0; i < righe; i++)
	{
		for (j = 0; j < colonne; j++)
		{
			if (campo[i][j].bomba == 1)
			{
				fprintf(fp, "%d, %d\n", i, j);
			}
		}
	}
	fclose(fp);
}
