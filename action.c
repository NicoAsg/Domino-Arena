#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

Domino piocheDominos(Domino *talon, int *nbDominos)
{
    int indexDomino = rand() % (*nbDominos);//Index du domino choisit
    Domino choisit = talon[indexDomino];

    //Evite le cas ou il ne reste plus qu'1 domino
    if (indexDomino != *nbDominos)
    {
        Domino echange = talon[*nbDominos - 1];

        talon[indexDomino] = echange, talon[*nbDominos - 1] = choisit;//Echange le domino choisit avec le dernier du talon
        *nbDominos -= 1;//On retire 1 domino
        ///Le dernier domino (celui choisit) n'est donc plus pris en compte dans le talon
    }
    return choisit;
}

int placeDomino(int **carte, int tailleMap, Placement choix)
{
    Coordonnees case2;//Coordonnées de la 2e case prise par le domino
    Domino intermediaire;
    int coordonneeIntermediaire ;

    ///Orientation du domino
    if (choix.direction == 'd')
        case2.x = choix.position.x + 1, case2.y = choix.position.y;//Case 2 est la case à droite de la case 1 (x + 1)
    else if (choix.direction == 'g')
    {
        //Echange des 2 cases
        intermediaire.case1 = choix.aPlacer.case1, intermediaire.case2 = choix.aPlacer.case2;
        choix.aPlacer.case1 = intermediaire.case2, choix.aPlacer.case2 = intermediaire.case1;

        coordonneeIntermediaire = choix.position.x;//Case 1 est la case à gauche de la case 2 (x - 1)
        case2.x = choix.position.x, case2.y = choix.position.y;
        choix.position.x = coordonneeIntermediaire - 1;
    }
    else if (choix.direction == 'h')
    {
        //Echange des 2 cases
        intermediaire.case1 = choix.aPlacer.case1, intermediaire.case2 = choix.aPlacer.case2;
        choix.aPlacer.case1 = intermediaire.case2, choix.aPlacer.case2 = intermediaire.case1;

        coordonneeIntermediaire = choix.position.y;//Case 2 est la case en haut de la case 2 (y - 1)
        case2.x = choix.position.x, case2.y = choix.position.y;
        choix.position.y = coordonneeIntermediaire - 1;
    }
    else if (choix.direction == 'b')
        case2.x = choix.position.x, case2.y = choix.position.y + 1;//Case 2 est la case en bas de la case 1 (y + 1)
    else
        return 0;

    if (choix.position.x > 0 && choix.position.y > 0 && choix.position.x < (tailleMap - 1) && choix.position.y < (tailleMap - 1))//Si la case1 existe
        if (case2.x > 0 && case2.y > 0 && case2.x < (tailleMap - 1) && case2.y < (tailleMap - 1))
            if (verifDispoCase(carte, choix.position) && verifDispoCase(carte, case2))//Si les cases prises par le domino sont libres
                if (placementCorrect(carte, choix.position, case2, choix.aPlacer))//Si le domino coincide avec ceux autour
                {
                    carte[choix.position.y][choix.position.x] = choix.aPlacer.case1;
                    carte[case2.y][case2.x] = choix.aPlacer.case2;
                    return 1;
                }
    //Si la fonction s'exécute jusqu'ici, alors le placement ne s'est pas fait
    return 0;
}

int verifDispoCase (int **carte, Coordonnees actuelles)
{
    if (carte[actuelles.y][actuelles.x] != -1)//Si la case n'est pas vide
        return 0;//Alors la case n'est pas disponible
    else
        return 1;
}

//Vérifie si les cases autour du domino coincident avec celui-ci
int placementCorrect(int **carte, Coordonnees case1, Coordonnees case2, Domino actuel)
{
    ///On considère la case 1 la plus en haut et à gauche
    if (case1.y == case2.y)//Domino placé horizontalement
        if ((carte[case1.y][case1.x - 1] == actuel.case1 || carte[case1.y + 1][case1.x] == actuel.case1 || carte[case1.y - 1][case1.x] == actuel.case1) || (carte[case2.y][case2.x + 1] == actuel.case2 || carte[case2.y + 1][case2.x] == actuel.case2 || carte[case2.y - 1][case2.x] == actuel.case2))
            /*Si au moins une des cases autour du domino coincide avec celui-ci
            Alors on vérifie si toutes les cases coincident (soit égale, soit vide)*/
            if ((carte[case1.y][case1.x - 1] == actuel.case1 || carte[case1.y][case1.x - 1] == -1) && (carte[case1.y + 1][case1.x] == actuel.case1 || carte[case1.y + 1][case1.x] == -1) && (carte[case1.y - 1][case1.x] == actuel.case1 || carte[case1.y - 1][case1.x] == -1))//Case 1
                if ((carte[case2.y][case2.x + 1] == actuel.case2 || carte[case2.y][case2.x + 1] == -1) && (carte[case2.y + 1][case2.x] == actuel.case2 || carte[case2.y + 1][case2.x] == -1) && (carte[case2.y - 1][case2.x] == actuel.case2 || carte[case2.y - 1][case2.x] == -1))//Case 2
                    return 1;

    if (case1.x == case2.x)//Domino placé verticalement
        if ((carte[case1.y - 1][case1.x] == actuel.case1 || carte[case1.y][case1.x + 1] == actuel.case1 || carte[case1.y][case1.x - 1] == actuel.case1) || (carte[case2.y + 1][case2.x] == actuel.case2 || carte[case2.y][case2.x + 1] == actuel.case2 || carte[case2.y][case2.x - 1] == actuel.case2))
            /*Si au moins une des cases autour du domino coincide avec celui-ci
            Alors on vérifie si toutes les cases coincident (soit égale, soit vide)*/
            if ((carte[case1.y - 1][case1.x] == actuel.case1 || carte[case1.y - 1][case1.x] == -1) && (carte[case1.y][case1.x + 1] == actuel.case1 || carte[case1.y][case1.x + 1] == -1) && (carte[case1.y][case1.x - 1] == actuel.case1 || carte[case1.y][case1.x - 1] == -1))//Case 1
                if ((carte[case2.y + 1][case2.x] == actuel.case2 || carte[case2.y + 1][case2.x] == -1) && (carte[case2.y][case2.x + 1] == actuel.case2 || carte[case2.y][case2.x + 1] == -1) && (carte[case2.y][case2.x - 1] == actuel.case2 || carte[case2.y][case2.x - 1] == -1))//Case 2
                    return 1;

    //Si la fonction est exécutée jusqu'ici, alors les conditions sont fausses
    return 0;

}
