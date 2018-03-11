#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int main()
{
    srand(time(NULL));
    deroulement();

    return 0;
}

void jeu()
{

    int **carte;
    carte = creationCarte(20);
    innitialisationCarte(carte, 20);

    srand(time(NULL));
    Domino *talon;
    int nbCarte = sum(7);
    talon = creationTalon(6);
    melangeTalon(talon, nbCarte);

    Placement test;
    test.position.x = 8, test.position.y = 6;
    test.direction = 'd';
    test.aPlacer = talon[7];
    carte[7][8] = talon[7].case1, carte[7][9] = talon[7].case2;
    printf("", placeDomino(carte, 20, test));
/*
    Joueur tous[2];
    creationDeckJoueurs(tous, 2, talon, &nbCarte);
    int i;
    for (i = 0; i < NB_DOMINOS_DECK; i++)
        printf("%4d|%d", tous[0].deck[i].case1, tous[0].deck[i].case2);
    printf("\n");
    for (i = 0; i < NB_DOMINOS_DECK; i++)
        printf("%4d|%d", tous[1].deck[i].case1, tous[1].deck[i].case2);
    printf("\n");
    for (i = 0; i < nbCarte; i++)
        printf("%4d|%d", talon[i].case1, talon[i].case2);
*/
int i, j;

    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 20; j++)
            printf("%3d", carte[i][j]);
        printf("\n");
    }

    free(carte);


}

void deroulement()
{
    int **carte;
    carte = creationCarte(20);
    innitialisationCarte(carte, 20);

    Domino *talon, premDomino;
    int nbDominos = sum(7);
    talon = creationTalon(6);
    melangeTalon(talon, nbDominos);
    premDomino = piocheDominos(talon, &nbDominos);
    carte[7][7] = premDomino.case1, carte[7][8] = premDomino.case2;

    Joueur participants[2];
    int nbJoueurs = 2;
    creationDeckJoueurs(participants, nbJoueurs, talon, &nbDominos);

    int i;
    while(!gagne(participants, nbJoueurs))
    {
        for (i = 0; i < nbJoueurs; i++)
            tour(participants[i], talon, &nbDominos, carte, 20);
    }
}

void afficheCarte(int **carte, int taille)
{
    int i, j;
    char espace = ' ';

    printf(" ");
    for (j = 0; j < 20; j++)
        printf("%3d", j);
    printf("\n");
    for (i = 0; i < 20; i++)
    {
        printf("%d", i);
        for (j = 0; j < 20; j++)
        {
            if(carte[i][j] != -1)
                printf("%3d", carte[i][j]);
            else
                printf("%3c", espace);
        }
        printf("\n");
    }
}

void tour(Joueur actuel, Domino *talon, int *tailleTalon, int **carte, int taille)
{
    int i;
    int choix;
    Placement dominoChoisit;

    afficheCarte(carte, taille);
    printf("\nDominos a placer :\n");
    for (i = 0; i < actuel.nbDominoDeck; i++)
        printf("%4d: %d|%d", i, actuel.deck[i].case1, actuel.deck[i].case2);

    printf("\n%d: Piocher\n\nChoix : ", i);
    scanf("%d", &choix);
    if (choix == i)
    {
        Domino aAjouter;
        aAjouter = piocheDominos(talon, tailleTalon);
        printf("%d", actuel.nbDominoDeck);
        actuel.deck[actuel.nbDominoDeck] = aAjouter;
        actuel.nbDominoDeck++;
    }
    else
    {
        printf("\nPosition x : ");
        scanf("%d", &dominoChoisit.position.x);
        fflush(stdin);
        printf("\nPosition y : ");
        scanf("%d", &dominoChoisit.position.y);
        fflush(stdin);
        printf("\nDirection (h, b, g, d) : ");
        scanf("%c", &dominoChoisit.direction);

        dominoChoisit.aPlacer = actuel.deck[choix];
        placeDomino(carte, taille, dominoChoisit);
    }
}

int sum(int nb)
{
    if (nb > 0)
        return nb + sum(nb - 1);
    else
        return nb;
}

int gagne(Joueur *participants, int nbJoueurs)
{
    int i;

    for (i = 0; i < nbJoueurs; i++)
        if (participants[i].nbDominoDeck == 0)
            return participants[i].numero;

    return 0;
}
