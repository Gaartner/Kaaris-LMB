#ifndef DEF_STRUCTURE // Si la constante n'a pas été définie le fichier n'a jamais été inclus
#define DEF_STRUCTURE // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus

/* Contenu de votre fichier .h (autres include, prototypes, define...) */
void jouer(SDL_Surface*);
int passeSurIcone(SDL_Event, int, int, int, int); //prototype
int cliqueSurIcone(SDL_Event, int, int, int, int);
int rand_ab(int, int);
int bouger(int, int*, SDL_Surface*[]);

#define HAUT_GAUCHE 1
#define HAUT 2
#define HAUT_DROIT 3
#define DROIT 4
#define BAS_DROIT 5
#define BAS 6
#define BAS_GAUCHE 7
#define GAUCHE 8

#endif


