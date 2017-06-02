#include "carica_campo.h"

/* la funzione carica_campo si occupa di creare un campo di gioco leggendo da un file di testo dimensioni e le coordinate delle bombe

le variabili sono inizializzate dal chiamante della funzione */
casella_t** carica_campo(int *righe, int *colonne)
{
	/* sono righe, colonne */
	int a, b;
	/* varibile di controllo per il corretto input */
	int risultato;

	casella_t** campo =0;

	FILE *fp;

	fp = fopen("mappa.txt", "r");
	/* gestisce un input NULL */
	if (fp == NULL)
	{
		printf("Attenzione impossibile caricare il file!\n");
		return campo;
	}
	/* lettura prima riga contenente dimensioni campo */
	risultato = fscanf(fp, "%d, %d\n", righe, colonne);
	/* alloca la memoria delle dimensioni giuste per il campo */
	campo = alloca_memoria_campo(*righe, *colonne);
	/* legge le cooridnate delle bombe e le inserisce fino a fine file EOF */
	while (risultato != EOF)
	{
		/* l intero restituito viene messo dentro risultato per essere valutato */
		risultato = fscanf(fp, "%d, %d\n", &a, &b);

		if (risultato == 2)
		{
			if (a < *righe && b < *colonne && a >= 0 && b >= 0)
			{
				if (!inserisci_bomba(*righe, *colonne, a, b, campo))
				{
					printf("Attenzione trovata bomba duplicata!\n");
				}
			}
			else
			{
				printf("Trovata bomba fuori dal campo!\n");
			}
		}
	}
	/* letto tutto, puoi chiudere */
	fclose(fp);

	return campo;

}
