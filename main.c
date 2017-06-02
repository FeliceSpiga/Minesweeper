#include <time.h>
#include <stdlib.h>
#include "memoria.h"
#include "carica_campo.h"
#include "genera_campo.h"
#include "stampa_campo.h"
#include "salva_campo.h"
#include "partita.h"

/* campo minato e diviso in sotto funzioni che si trovano in file separati, ho deciso cio per avere un maggior ordine e chiarezza durante la 
realizzazione del progetto, il main contiene quindi il menu principale, da cui una volta scelta l opzione si dirama nelle varie sotto funzioni */
int main()
{
	/* campo inizializzato a NULL pointer */
	casella_t** campo = 0;
	/* variabile utilizzata per l uscita dal programma */
	int should_exit = 0;
	int righe;
	int colonne;
	int righe_utente;
	int colonne_utente;
	int numero_bombe_utente;
	/* variabile di controllo per corretto input */
	int trovati;
	/* variabile che contiene il numero di undo possibili durante la partita */
	int undo;
	/* inizializza rand ad un valore diverso ogni volta che il programma viene avviato (perche' usa la datetime corrente) */
	
	srand(time(NULL));

	printf("\033[H\033[J");

	while (!should_exit)
	{
		int user_input;

		printf("1 - Genera campo \n\n");
		printf("2 - Carica campo \n\n");
		if (campo)
		{
			printf("3 - Salva campo \n\n");
			printf("4 - Gioca partita \n\n");
		}
		printf("5 - Esci \n\n\n\n");
		printf("Scegli l'opzione che preferisci: ");
		
		trovati = scanf("%d", &user_input);
		
		while ((getchar()) != '\n'){}
		
		if(!trovati)
		{
			continue;
		}

		switch (user_input)
		{

		case 1:
			
			trovati = 0;
			while(trovati != 1)
			{ 
				printf("Inserire il numero delle righe: \n");
				trovati = scanf("%d", &righe_utente);
			
				while ((getchar()) != '\n'){}

				printf("\033[H\033[J");

				if (righe_utente == 1)
				{
					trovati = 0;
					printf("Inserire un numero intero maggiore di uno \n");
					continue;
				}	

				if (righe_utente > 50 || righe_utente <= 0)
				{
					trovati = 0;
					printf("Inserire un numero intero minore o uguale a 50 \n");
					continue;
				}

				if (!trovati)
				{
					printf("Inserire un numero intero minore o uguale a 50 \n");
					continue;
				}
			}

			trovati = 0;
			while (trovati != 1)
			{
				printf("Inserire il numero delle colonne: \n");
				trovati = scanf("%d", &colonne_utente);

				while ((getchar()) != '\n'){}

				printf("\033[H\033[J");

				if (colonne_utente == 1)
				{
					trovati = 0;
					printf("Inserire un numero intero maggiore di uno \n");
					continue;
				}


				if (colonne_utente > 26 || colonne_utente <= 0)
				{
					trovati = 0;
					printf("Inserire un numero intero minore o uguale a 26 \n");
					continue;
				}

				if (!trovati)
				{
					printf("Inserire un numero intero minore o uguale a 26 \n");
					continue;
				}
			}

			trovati = 0;
			while (trovati != 1)
			{
				printf("Inserire il numero delle bombe: \n");
				trovati = scanf("%d", &numero_bombe_utente);

				while ((getchar()) != '\n'){}

				printf("\033[H\033[J");

				if (numero_bombe_utente > (righe_utente * colonne_utente - 1) || numero_bombe_utente <= 0)
				{
					trovati = 0;
					printf("Inserire un numero intero minore di %d \n", (righe_utente * colonne_utente - 1));
					continue;
				}

				if (!trovati)
				{
					printf("Inserire un numero intero minore di %d \n", (righe_utente * colonne_utente - 1));
					continue;
				}
			}

			if (campo)
			{
				free_campo(righe, campo);
			}

			campo = genera_campo(righe_utente, colonne_utente, numero_bombe_utente);
			righe = righe_utente;
			colonne = colonne_utente;
			printf("\033[H\033[J");

			break;

		case 2:
			if (campo)
			{
				free_campo(righe, campo);
			}
			printf("\033[H\033[J");

			campo = carica_campo(&righe, &colonne);

			break;

		case 3:
			
			printf("\033[H\033[J");
			if (campo)
			{
				salva_campo(righe, colonne, campo);

				printf("Hai salvato il campo con successo \n");
			}
			
			break;

		case 4:

			printf("\033[H\033[J");

			if (campo)
			{
				trovati = 0;
				while (trovati != 1)
				{
					printf("Inserire il numero di undo: \n");
					trovati = scanf("%d", &undo);
					while ((getchar()) != '\n'){}

					printf("\033[H\033[J");


					if (undo > 10 || undo < 0)
					{
						trovati = 0;
						printf("Inserire un numero minore o uguale a 10  \n");
					}
				}
				gioca_partita(righe, colonne, undo, campo);
				printf("\033[H\033[J");

			}
			break;

		case 5:

			should_exit = 1;
			break;
		}
	}

	printf("Grazie per aver giocato! \n");
	return 0;
}
