#ifndef PARTITA
#define PARTITA

#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"
#include "stampa_campo.h"
#include <ctype.h>

void gioca_partita(int righe, int colonne, int undo, casella_t** campo);
void inserisci_bandierina(int righe, int colonne, int a, int b, casella_t** campo);
int scopri_casella(int righe, int colonne, int a, int b, casella_t** campo, mossa_t** pp_ultima_mossa);
void espandi_casella(int a, int b, int righe, int colonne, casella_t** campo, mossa_t* mossa);
void espandi_casella_helper(int a, int b, int righe, int colonne, casella_t** campo, mossa_t* mossa);
int vittoria(int righe, int colonne, casella_t** campo);
void undo(casella_t** campo, int utilizzo_undo, mossa_t** pp_ultima_mossa);
void pulisci_campo(int righe, int colonne, casella_t** campo, mossa_t** pp_ultima_mossa);

#endif
