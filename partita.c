#include "partita.h"

/* gioca_partita gestisce la fase di gioco, contiene un nuovo menu apposito e si occupa di tutto cio che riguarda il gioco vero e proprio,
   caso di vittoria, caso di sconfitta, inserire le bandierine, undo in caso di bomba scoperta, apertura casella e uscita dal gioco con
   ritorno al menu principale, tramite l uso di sottofunzioni */

void gioca_partita (int righe, int colonne, int undo_permessi, casella_t** campo)
{
	int a;
	int b;
	char colonna_utente;
	char user_input;
	/* variabile di controllo input */
	int trovati;
	/* variabile controllo bomba scoperta */
	int esploso = 0;
	/* variabile controllo undo */
	int utilizzo_undo = 0;

	mossa_t* p_ultima_mossa = 0;

	while (1)
	{
		stampa_campo(righe, colonne, campo);


		if (esploso && utilizzo_undo < undo_permessi)
		{
			printf("Boom! \nPremi u per riprovare! \n\nUndo rimanenti:%d \n", undo_permessi - utilizzo_undo); 	
		}
		else if(esploso)
		{
			printf("Mi dispiace hai perso, premi q per tornare al menu principale \n\n");
		}

		printf("Scrivi h per aiuto \n\n");
		printf("Comando: ");
		scanf("\n%c", &user_input);

		switch (user_input)
		{
			case 'h':
				printf("\033[H\033[J");

				printf("Inserisci u per annullare l'ultima mossa: \n");
				printf("Inserisci f per inserire una bandiera: \n");
				printf("Inserisci o per scoprire una casella: \n");
				printf("Inserisci q per tornare al menu principale: \n");

				break;

			case 'u':
				if (utilizzo_undo < undo_permessi)
				{
					utilizzo_undo++;
					undo(campo, utilizzo_undo, &p_ultima_mossa);
				}
				esploso = 0;

				printf("\033[H\033[J");

				break;

			case 'f':
				if (esploso)
				{
					while ((getchar()) != '\n'){}
					break;
				}
				trovati = 0;
				trovati = scanf(" %c%d", &colonna_utente, &a);
				while ((getchar()) != '\n'){}

				if (trovati == 2)
				{
					b = toupper(colonna_utente) - 65;
					
					if (a < righe && b < colonne && a >= 0 && b >= 0 )
					{
						inserisci_bandierina(righe, colonne, a, b, campo);
					}
				}

				printf("\033[H\033[J");

				break;
			
			case 'o':
				if (esploso)
				{
					while ((getchar()) != '\n'){}
					break;
				}
				trovati = 0;
				trovati = scanf(" %c%d", &colonna_utente, &a);
				while ((getchar()) != '\n'){}

				if (trovati == 2)
				{
					b = toupper(colonna_utente) - 65;

					if (a < righe && b < colonne && a >= 0 && b >= 0)
					{
						esploso = scopri_casella(righe, colonne, a, b, campo, &p_ultima_mossa);

						if (vittoria(righe, colonne, campo))
						{
							printf("\033[H\033[J");
							stampa_campo(righe, colonne, campo);
							printf("Complimenti hai vinto! \n\nPremi invio per tornare al menu principale \n");
							while ((getchar()) != '\n'){}
							pulisci_campo(righe, colonne, campo, &p_ultima_mossa);
							return;
						}
					}
				}

				printf("\033[H\033[J");

				break;
			
			case 'q':
				pulisci_campo(righe, colonne, campo, &p_ultima_mossa);
				return;
				break;
			
			default:
				while ((getchar()) != '\n'){}

				printf("\033[H\033[J");

				break;
		}
	}
}

/* inserisci_bandierina ci permette di mettere e togliere le bandierine */

void inserisci_bandierina(int righe, int colonne, int a, int b, casella_t** campo)
{
	if (campo[a][b].bandiera)
	{
		campo[a][b].bandiera = 0;
		return;
	}
	/* in caso di bandierina posizionata su casella scoperta */
	if (campo[a][b].scoperta)
	{
		printf("Impossibile posizionare bandierina \n");
		return;
	}
	
	campo[a][b].bandiera = 1;
}

/* scopri_casella si occupa di scoprire la casella selezionata da l utente e di gestire i vari casi che ne derivano, come per esempio
   l apertura di una casella vuota che porta a diverse aperture automatiche di caselle vuote adiacenti */

int scopri_casella(int righe, int colonne, int a, int b, casella_t** campo, mossa_t** pp_ultima_mossa)
{
	mossa_t* nuova_mossa;

	if(campo[a][b].scoperta)
	{
		printf("Casella gia scoperta! \n");
		return 0;
	}

	if (campo[a][b].bandiera)
	{
		printf("La casella ha una bandiera! \n");
		return 0;
	}

	/* da qui in poi iniziamo ad allocare la memoria necessaria a conservare la mossa dell utente,
	   visto che i due casi piu sopra sono assolutamente irrilevanti nella successione delle mosse */

	nuova_mossa = malloc(sizeof(mossa_t));
	nuova_mossa->prev = *pp_ultima_mossa;
	*pp_ultima_mossa = nuova_mossa;


	nuova_mossa->apertura = malloc(sizeof(apertura_casella_t));
	nuova_mossa->apertura->a = a;
	nuova_mossa->apertura->b = b;
	/* assegnamo il NULL pointer a nuova_mossa per definire la fine della lista */
	nuova_mossa->apertura->next = 0;

	/* la funzione ritorna un int perche usiamo il valore di ritorno 1 per sapere se abbiamo scoperto una bomba */
	if (campo[a][b].bomba)
	{
		campo[a][b].scoperta = 1;
		return 1;
	}

	if (campo[a][b].numero != 0)
	{
		campo[a][b].scoperta = 1;
		return 0;
	}

	campo[a][b].scoperta = 1;
	
	/* chiamiamo espandi casella per occuparci delle caselle vuote che sono un caso particolare di apertura per tutto cio che en deriva */
	espandi_casella(a, b, righe, colonne, campo, nuova_mossa);
	return 0;
}



/* espandi_casella riceve una casella VUOTA da scopri_casella, successivamente 
   il controllo delle caselle adiacenti parte dalla cella in prossimita "mid-left"
   si sposta poi a "top left" poi "top-middle" e così via a controlllare tutta la 
   "corona" di caselle attorno a quella selezionata da l utente, una volta completato questo "ciclo"
   dalle caselle che abbiamo aperto verra richiamata la funzione stessa per controllare le nuove "corone" */

void espandi_casella(int a, int b, int righe, int colonne, casella_t** campo, mossa_t* mossa)
{
	int bordo_superiore = (a == 0);
	int bordo_inferiore = (a == (righe - 1));
	int bordo_sinistro = (b == 0);
	int bordo_destro = (b == (colonne - 1));
	


	if (!bordo_superiore)
	{
		if (!bordo_sinistro)
		{
			espandi_casella_helper(a - 1, b - 1, righe, colonne, campo, mossa); /* top left */
		}
		
		espandi_casella_helper(a - 1, b, righe, colonne, campo, mossa); /* top middle */
		
		if (!bordo_destro)
		{
			espandi_casella_helper(a - 1, b + 1, righe, colonne, campo, mossa); /* top right */
		}
	}

	if (!bordo_sinistro)
	{
		espandi_casella_helper(a, b - 1, righe, colonne, campo, mossa); /* middle left */
	}

	if (!bordo_destro)
	{
		espandi_casella_helper(a, b + 1, righe, colonne, campo, mossa); /* middle right */
	}

	if (!bordo_inferiore)
	{
		if (!bordo_sinistro)
		{
			espandi_casella_helper(a + 1, b - 1, righe, colonne, campo, mossa); /* bottom left */
		}

		espandi_casella_helper(a + 1, b, righe, colonne, campo, mossa); /* bottom middle */
		
		if (!bordo_destro)
		{
			espandi_casella_helper(a + 1, b + 1, righe, colonne, campo, mossa); /* bottom right */
		}
	}
}



void espandi_casella_helper(int a, int b, int righe, int colonne, casella_t** campo, mossa_t* mossa)
{
	int scoperta_prima;
	apertura_casella_t* nuova_apertura;


	if (campo[a][b].bandiera)
	{
		return;
	}

	nuova_apertura = malloc(sizeof(apertura_casella_t));
	nuova_apertura->a = a;
	nuova_apertura->b = b;
	nuova_apertura->next = mossa->apertura;
	mossa->apertura = nuova_apertura;

	scoperta_prima = campo[a][b].scoperta;
	campo[a][b].scoperta = 1;

	if (campo[a][b].numero == 0 && !scoperta_prima)
	{
		espandi_casella(a, b, righe, colonne, campo, mossa);
	}
}

/* vittoria controlla il campo per controllare che tutte le caselle tranne le bombe siano state scoperte */

int vittoria(int righe, int colonne, casella_t** campo)
{
	int i;
	int j;

	for (i = 0; i < righe; i++)
	{
		for (j = 0; j < colonne; j++)
		{
			if (!campo[i][j].scoperta && !campo[i][j].bomba)
			{
				return 0;
			}
		}
	}
	/* ritoniamo 1 in caso di vittoria */
	return 1;
}

/* la funzione undo si occupa di richiudere tutte le caselle che sono state scoperte di conseguenza alle mosse effettuate dall utente */

void undo(casella_t** campo, int utilizzo_undo, mossa_t** pp_ultima_mossa)
{
	int i;
	mossa_t* mossa_da_eliminare;
	apertura_casella_t* apertura_da_eliminare;

	/* annulliamo tante mosse quante l utilizzo di undo, come richiesto */
	for(i=0; i < utilizzo_undo; i++)
	{

		if (*pp_ultima_mossa == 0)
		{
			return;
		}
		/* il while si occupa di richiudere tutte le aperture derivanti dalle mosse utente, viene ripetuto dal for per il numero di mosse
		   uguale al numero di utilizzi di undo */
		while ((*pp_ultima_mossa)->apertura)
		{
			campo[(*pp_ultima_mossa)->apertura->a][(*pp_ultima_mossa)->apertura->b].scoperta = 0;
			apertura_da_eliminare = (*pp_ultima_mossa)->apertura;
			(*pp_ultima_mossa)->apertura = (*pp_ultima_mossa)->apertura->next;
			/* liberiamo la lista di aperture che non ci interessa piu */
			free(apertura_da_eliminare);
		}

		mossa_da_eliminare = *pp_ultima_mossa;
		*pp_ultima_mossa = (*pp_ultima_mossa)->prev;
		/* liberiamo la lista di mosse che non ci interessa piu */
		free(mossa_da_eliminare);
	}
}

/* pulisci_campo si occupa di riportare il campo alla condizione iniziale, undo copre tutte le caselle e il for toglie le bandierine */

void pulisci_campo(int righe, int colonne, casella_t** campo, mossa_t** pp_ultima_mossa)
{
	int i;
	int j;

	undo(campo, righe * colonne, pp_ultima_mossa);

	for (i = 0; i < righe; i++)
	{
		for (j = 0; j < colonne; j++)
		{
			campo[i][j].bandiera = 0;
		}
	}
}
