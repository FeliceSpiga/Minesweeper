#ifndef MEMORIA
#define MEMORIA

/* definizione delle struct delle caselle del campo con i vari stati che puo assumere durante la partita */

typedef struct casella
{
	int bomba;
	int bandiera;
	int numero;
	int scoperta;
}casella_t;

/* per l implementazione della funzione undo ho deciso di utilizzate due liste, una contenente le mosse utente e un altra le apertura_casella derivanti */

/* defiizione delle struct che contengono le cordinate delle caselle scoperte dalle mosse dell utente */

typedef struct apertura_casella apertura_casella_t;
struct apertura_casella
{
	int a;
	int b;
	apertura_casella_t *next;
};

/* definizione delle struct contenenti i puntatoti alle apertura_casella necessari per il raggruppamento delle aperture derivanti dalla mossa utente,
   cio per facilitare la divisione in blocchi delle aperture derivanti dalla mossa, utile nel caso di una mossa che scopre una casella dando
   il via a una apertura di massa */

typedef struct mossa mossa_t;
struct mossa
{
	mossa_t *prev;
	apertura_casella_t *apertura;
};



casella_t** alloca_memoria_campo(int, int);
int inserisci_bomba(int righe, int colonne, int a, int b, casella_t** campo);
void free_campo(int righe, casella_t** campo);

#endif
