#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int **creationCarte(int taille)
{
    int **carte = NULL;
    int i;

    carte = malloc((taille - 1) * sizeof(int*));//Allocation du nombre de case pour la 1ere dimension(y)
    for (i = 0; i < taille; i++)
        carte[i] = malloc((taille - 1) * sizeof(int));//Allocation des cases pour la 2e dimension(x)

    return carte;
}

void innitialisationCarte(int **carte, int taille)
{
    int i, j;
    for (i = 0; i < taille; i++)
        for(j = 0; j < taille; j++)
            carte[i][j] = -1;//Innitialisation des cases de la carte à -1
}

Domino* creationTalon(int nbMax)
{
    int i, j, k = 0;
    Domino *talon;
    talon = malloc((sum(nbMax + 1)) * sizeof(Domino));

    for (i = 0; i <= nbMax; i++)
        for (j = i; j <= nbMax; j++)
        {
            talon[k].case1 = i, talon[k].case2 = j;
            k += 1;
        }

    return talon;
}

void melangeTalon(Domino *talon, int nbDominos)
{
    int i, j;
    Domino vI;

    for (i = 0; i < nbDominos; i++)
    {
        j = rand() % (nbDominos - 1);
        vI = talon[i];
        talon[i] = talon[j], talon[j] = vI;
    }
}

void creationDeckJoueurs(Joueur *participants, int nbJoueurs, Domino *talon, int *nbDominos)
{
    int i, j;

    for (i = 0; i < nbJoueurs; i++)
    {
        participants[i].numero = i + 1;
        participants[i].deck = malloc((TAILLE_DECK - 1) * sizeof(Domino));//Allocation du deck

        for (j = 0; j < NB_DOMINOS_DECK; j++)///On pioche le nombre de domino voulu dans le deck
            participants[i].deck[j] = piocheDominos(talon, nbDominos);

        participants[i].nbDominoDeck = NB_DOMINOS_DECK;
    }

}
