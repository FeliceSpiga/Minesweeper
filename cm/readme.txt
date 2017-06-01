This is a university project made for the Programming course, it is a version of Minesweeper, the language used is C std89, the game have some interesting fetures, like Undo function that can be used only if you step on a bomb and with a limited number of use choosen by the player, with a maximum of 10, there is also the function Flag, used to mark a bomb

Here is the command to build on linux:

gcc -std=gnu89 -pedantic -Wall carica_campo.c main.c genera_campo.c memoria.c partita.c salva_campo.c stampa_campo.c -o campo_minato
