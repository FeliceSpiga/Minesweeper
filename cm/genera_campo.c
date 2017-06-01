#include "genera_campo.h"
/* la funzione genera_campo si occupa della generazione del campo di gioco date le righe le colonne e il numero di bombe in ingresso,
inoltre si occupa del posizionamento randomico delle bombe a l interno del campo, cio avviene grazie a l utilizzo della funzione rand
viene chiamata la funzione alloca_memoria con le dimensioni del campo, una volta prodotto un campo, il ciclio for vi posiziona il numero di
bombe inserito da l utente, il while invece si occupa di far ripetere l inserimento in caso esso non sia avvenuto per bomba gia presente */
casella_t** genera_campo(int righe, int colonne, int numero_bombe)
{
	casella_t** campo;
	int i;
	int a;
	int b;

	campo = alloca_memoria_campo(righe, colonne);
	
	for(i=0; i<numero_bombe; i++)
	{
		do
		{
			a = rand() % righe;
			b = rand() % colonne;
		} 
		while (!inserisci_bomba(righe, colonne, a, b, campo));	
	}

	return campo;
}
