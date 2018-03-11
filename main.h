#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define TAILLE_DECK 20
#define NB_DOMINOS_DECK 6

typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
    int x, y;
};

typedef struct Domino Domino;
struct Domino
{
    int case1, case2;//Les 2 cases d'un domino
};

typedef struct Placement Placement;
struct Placement
{
    Coordonnees position;//Position de la case1 du domino
    char direction;//2 possibilités : h (horieontal), v (vertical)
    Domino aPlacer;
};

typedef struct Joueur Joueur;
struct Joueur
{
    int numero;
    Domino *deck;
    int nbDominoDeck;
};

int **creationCarte(int taille);
void innitialisationCarte(int **carte, int taille);
Domino* creationTalon(int nbMax);
void melangeTalon(Domino *talon, int nbDominos);
void distributionDominos(Domino *talon, int nbDominos, Joueur *participants, int nbJoueurs);
void creationDeckJoueurs(Joueur *participants, int nbJoueurs, Domino *talon, int *nbDominos);
Domino piocheDominos(Domino *talon, int *nbDominos);
int sum(int nb);
int placeDomino(int **carte, int tailleMap, Placement choix);
int verifDispoCase (int **carte, Coordonnees actuelles);
int placementCorrect(int **carte, Coordonnees case1, Coordonnees case2, Domino actuel);
#endif // MAIN_H_INCLUDED
