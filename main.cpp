#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h> //On inclut la bibliothèque SDL qui nous permet de créer des jeux 2D
#include <SDL_image.h>
#include "structure.h"



int main(int argc, char* argv[])
{
    SDL_Surface *ecran = NULL, *surface = NULL; //Création de surfaces (variables) pour allouer de l'espace en mémoire
    SDL_Rect position; //On crée une variable qui comprend une position (x, y)
    int continuer = 1;
    SDL_Event event; //Création d'une variable particulière qui s'occupe de la gestion d'événement
    int verifiePasse = 0;
    int verifieClique = 0;

    position.x = 0; //Ce sont des sous-variables de la variable position
    position.y = 0;

    SDL_Init(SDL_INIT_VIDEO); //Initialisation de la SDL (ici: chargement du système vidéo)
    //SDL_Init(SDL_INIT_AUDIO);

    SDL_WM_SetIcon(SDL_LoadBMP("Fichiers/labyrinthe.bmp"), NULL); //Charger une icone pour notre fenêtre. IMPORTANT! On doit le faire avant SDL_SetVideoMode

    ecran = SDL_SetVideoMode(1200, 670, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ceci va créer une fenêtre de 800x600 pixels. 32bits est le format des couleurs (nombre de couleurs affichables, soit des millairds)
    // HWSURFACE nous permet de charger les données dans la memoire vidéo (carte 3D), possibilité de le charger sur SWSURFACE ---> mémoire système (RAM) mais moins rapide
    SDL_WM_SetCaption("Le Labyrinthe", NULL); //Donner un titre à notre fenêtre. On envoie également NULL pour la deuxième valeur car elle nous sert pas ici
    surface = IMG_Load("Fichiers/menu.png"); //On charge une image dans notre surface (ici en bmp)

    while(continuer) //On effectue une boucle TANT QUE continuer ne vaut pas 0
    {
       SDL_WaitEvent(&event); //On attend qu'un événement se passe, qu'on récupérera dans notre variable event

       switch(event.type) //On agit en fonction du type d'événement
       {

           case SDL_KEYDOWN: // type d'événement: clavier
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: //clique sur Echap
                    continuer = 0; //Notre boucle se ferme
                    break;
                }
            break;


            case SDL_MOUSEMOTION: //type d'événement : mouvement de souris

            if (verifiePasse = passeSurIcone(event, 323, 66, 438, 371))
            surface = IMG_Load("Fichiers/jouer.png");
            else if (verifiePasse = passeSurIcone(event, 323, 66, 438, 475))
            surface = IMG_Load("Fichiers/reglages.png");
            else if (verifiePasse = passeSurIcone(event, 162, 49, 1009, 604))
            surface = IMG_Load("Fichiers/quitter.png");
            else
            surface = IMG_Load("Fichiers/menu.png");

            break;

            case SDL_MOUSEBUTTONUP: //type d'événement : clique (UP si il relache le bouton)

            if (verifieClique = cliqueSurIcone(event, 162, 49, 1009, 604))
            continuer = 0;
            if (verifieClique = cliqueSurIcone(event, 323, 66, 438, 371))
            jouer(ecran);
            break;
       }

       SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //On remplit notre surface d'une couleur. On indique premièrement la surface qu'on veut colorier, ensuite on envoie NULL car cette valeur nous intéresse pas et en troisième, on fait appel à la fonction "MapRGB".
       //La fonction MapRGB focntionne comme ceci: On indique premièrement le nombre de couleur (32bits) qu'on va chercher dans notre variable ecran dans laquelle on avait indiqué le format, puis le code rgb de notre couleur (ici: 0, 0, 0 ---> noir)

       SDL_BlitSurface(surface, NULL, ecran, &position); //On colle notre surface hatred sur la surface ecran, et à une position bien précise qu'on a déjà indiqué

       SDL_Flip(ecran); //Mise à jour de l'écran
    }

    SDL_FreeSurface(surface); // On libère la mémoire utilisée par la surface
    SDL_Quit(); //Arrêt de la SDL

    return EXIT_SUCCESS;

}


void jouer(SDL_Surface *ecran)
{
    SDL_Surface *fond = NULL;
    SDL_Surface *surface = NULL; //Création de surfaces (variables) pour allouer de l'espace en mémoire
    SDL_Surface *surface2 = NULL;
    SDL_Surface *fondGrille = NULL;
    SDL_Surface *porteX[420] = {NULL};
    SDL_Surface *porteY[420] = {NULL};
    SDL_Surface *caseDone[400] = {NULL};
    SDL_Rect position; //On crée une variable qui comprend une position (x, y)
    SDL_Rect positionFond;
    SDL_Rect positionPorteX[420];
    SDL_Rect positionPorteY[420];
    SDL_Rect positionCase[400];
    int continuer = 1;
    SDL_Event event; //Création d'une variable particulière qui s'occupe de la gestion d'événement
    int verifiePasse = 0;
    int verifieClique = 0;
    int i = 0;
    int k = 0;
    int j = 0;
    int h = 0;
    int g = 0;
    int ligne = 0;
    int colonne = 0;
    int verif = 0;
    int random = 0;
    int random2 = 0;
    int r = 0;
    int temps_precedent = 0;
    int temps_actuel = 0;
    int temps_verif = 0;


    position.x = 0; //Ce sont des sous-variables de la variable position
    position.y = 0;

    positionFond.x = 100;
    positionFond.y = 5;


    for (i=0 ; i<420 ; i++)
    {
        positionPorteX[i].x = 100 + k*33;
        positionPorteX[i].y = 5 + j*33;
        k++;

        if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99 || i == 119 || i == 139 || i == 159 || i == 179 || i == 199 || i == 219)
        {
            j++;
            k = 0;
        }
         else if(i == 239 || i == 259 || i == 279 || i == 299 || i == 319 || i == 339 || i == 359 || i == 379 || i == 399 || i == 419)
        {
            j++;
            k = 0;
        }
    }

    j = 0;
    k = 0;
    for (i=0 ; i<420 ; i++)
    {
        positionPorteY[i].x = 100 + j*33;
        positionPorteY[i].y = 5 + k*33;
        k++;

        if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99 || i == 119 || i == 139 || i == 159 || i == 179 || i == 199 || i == 219)
        {
            j++;
            k = 0;
        }
         else if(i == 239 || i == 259 || i == 279 || i == 299 || i == 319 || i == 339 || i == 359 || i == 379 || i == 399 || i == 419)
        {
            j++;
            k = 0;
        }
    }

    j = 0;
    k = 0;
    for (i=0 ; i<400 ; i++)
    {
        positionCase[i].x = 102 + k*33;
        positionCase[i].y = 7 + j*33;
        k++;

        if(i == 19 || i == 39 || i == 59 || i == 79 || i == 99 || i == 119 || i == 139 || i == 159 || i == 179 || i == 199 || i == 219)
        {
            j++;
            k = 0;
        }
         else if(i == 239 || i == 259 || i == 279 || i == 299 || i == 319 || i == 339 || i == 359 || i == 379 || i == 399)
        {
            j++;
            k = 0;
        }
    }

    fond = IMG_Load("Fichiers/fond.bmp");
    surface = IMG_Load("Fichiers/generer.png"); //On charge une image dans notre surface (ici en png)
    surface2 = NULL;
    fondGrille = IMG_Load("Fichiers/fond_grille.png");

    for (i=0 ; i<420 ; i++)
    {
        porteX[i] = IMG_Load("Fichiers/porte.png");
    }
    for (i=0 ; i<420 ; i++)
    {
        porteY[i] = IMG_Load("Fichiers/porte2.png");
    }
    for (i=0 ; i<400 ; i++)
    {
        caseDone[i] = NULL;
    }


    while(continuer) //On effectue une boucle TANT QUE continuer ne vaut pas 0
    {

       if(verif > 5)
       SDL_PollEvent(&event);
       else
       SDL_WaitEvent(&event); //On attend qu'un événement se passe, qu'on récupérera dans notre variable event

       temps_actuel = SDL_GetTicks();
       temps_verif = temps_actuel - temps_precedent;
       if(verif > 5 && temps_verif > 2000)
       {
           temps_precedent = temps_actuel;
           r = bouger(r, &random, caseDone);
       }

       switch(event.type) //On agit en fonction du type d'événement
       {

           case SDL_KEYDOWN: // type d'événement: clavier
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: //clique sur Echap
                    continuer = 0; //Notre boucle se ferme
                    break;
                }
            break;


            case SDL_MOUSEMOTION: //type d'événement : mouvement de souris

            if (verifiePasse = passeSurIcone(event, 126, 28, 1030, 90))
            surface = IMG_Load("Fichiers/generer2.png");
            else if (verifiePasse = passeSurIcone(event, 126, 28, 1030, 144) && verif >= 1)
            surface2 = IMG_Load("Fichiers/jeu2.png");
            else if (verif < 1)
            surface = IMG_Load("Fichiers/generer.png");
            else
            {
                surface = IMG_Load("Fichiers/generer.png");
                surface2 = IMG_Load("Fichiers/jeu.png");
            }

            break;

            case SDL_MOUSEBUTTONDOWN: //type d'événement : clique (UP si il relache le bouton)

            if (verifieClique = cliqueSurIcone(event, 126, 28, 1030, 90) && verif < 1)
            {
                surface2 = IMG_Load("Fichiers/jeu.png");
                SDL_BlitSurface(surface2, NULL, ecran, &position);
                SDL_Flip(ecran);
                for(i=0; i<400; i++)
                {
                    ligne = rand_ab(1, 21);
                    SDL_Delay(rand_ab(1, 10));
                    colonne = rand_ab(0, 21);

                    h = (((ligne-1)*20)+ colonne)-1;

                    if(caseDone[h] == NULL)
                    {
                        caseDone[h] = IMG_Load("Fichiers/done.png");
                        SDL_BlitSurface(caseDone[h], NULL, ecran, &positionCase[h]);
                        SDL_Flip(ecran);
                    }
                    else
                    i--;
                }

                fondGrille = NULL;
                for (i=0 ; i<400 ; i++)
                {
                    caseDone[i] = NULL;
                }

                ligne = rand_ab(3, 19);
                SDL_Delay(rand_ab(1, 10));
                colonne = rand_ab(3, 19);

                h = (((ligne-1)*20)+ colonne)-1;

                caseDone[h]= IMG_Load("Fichiers/tresor.png");
                porteX[h] = NULL;
                porteX[h-1] = NULL;
                porteX[h+1] = NULL;
                porteX[h+20] = NULL;
                porteX[h+19] = NULL;
                porteX[h+21] = NULL;

                g = (19 + ((colonne-1)*20)) - (20-ligne);

                porteY[g] = NULL;
                porteY[g-1] = NULL;
                porteY[g+1] = NULL;
                porteY[g+20] = NULL;
                porteY[g+19] = NULL;
                porteY[g+21] = NULL;

                random = rand_ab(1, 9);
                switch(random)
                {
                    case HAUT_GAUCHE:
                    r = h-21;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case HAUT:
                    r = h-20;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case HAUT_DROIT:
                    r = h-19;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case DROIT:
                    r = h+1;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case BAS_DROIT:
                    r = h+21;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case BAS:
                    r = h+20;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case BAS_GAUCHE:
                    r = h+19;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case GAUCHE:
                    r = h-1;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                }
                verif++;
            }
            else if (verifieClique = cliqueSurIcone(event, 126, 28, 1030, 90) && verif >= 1 && verif <= 5)
            {
                caseDone[h]= NULL;
                porteX[h] = IMG_Load("Fichiers/porte.png");
                porteX[h-1] = IMG_Load("Fichiers/porte.png");
                porteX[h+1] = IMG_Load("Fichiers/porte.png");
                porteX[h+20] = IMG_Load("Fichiers/porte.png");
                porteX[h+19] = IMG_Load("Fichiers/porte.png");
                porteX[h+21] = IMG_Load("Fichiers/porte.png");
                porteY[g] = IMG_Load("Fichiers/porte2.png");
                porteY[g-1] = IMG_Load("Fichiers/porte2.png");
                porteY[g+1] = IMG_Load("Fichiers/porte2.png");
                porteY[g+20] = IMG_Load("Fichiers/porte2.png");
                porteY[g+19] = IMG_Load("Fichiers/porte2.png");
                porteY[g+21] = IMG_Load("Fichiers/porte2.png");
                caseDone[r]= NULL;

                ligne = rand_ab(2, 20);
                SDL_Delay(rand_ab(1, 10));
                colonne = rand_ab(2, 20);

                h = (((ligne-1)*20)+ colonne)-1;

                caseDone[h]= IMG_Load("Fichiers/tresor.png");
                porteX[h] = NULL;
                porteX[h-1] = NULL;
                porteX[h+1] = NULL;
                porteX[h+20] = NULL;
                porteX[h+19] = NULL;
                porteX[h+21] = NULL;

                g = (19 + ((colonne-1)*20)) - (20-ligne);

                porteY[g] = NULL;
                porteY[g-1] = NULL;
                porteY[g+1] = NULL;
                porteY[g+20] = NULL;
                porteY[g+19] = NULL;
                porteY[g+21] = NULL;

                random = rand_ab(1, 9);
                switch(random)
                {
                    case HAUT_GAUCHE:
                    r = h-21;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case HAUT:
                    r = h-20;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case HAUT_DROIT:
                    r = h-19;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case DROIT:
                    r = h+1;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case BAS_DROIT:
                    r = h+21;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case BAS:
                    r = h+20;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case BAS_GAUCHE:
                    r = h+19;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                    case GAUCHE:
                    r = h-1;
                    caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
                    break;
                }
                verif++;
            }
            else if (verifieClique = cliqueSurIcone(event, 126, 28, 1030, 144) || verif > 5)
            {
                verif = 6;
                k = 0;
                j = 1;
                for(i=20; i<400; i++)
                {
                    if (verifieClique = cliqueSurIcone(event, 33, 2, 100 + k*33, 5 + j*33))
                    porteX[i] = NULL;
                    k++;

                    if(i == 39 || i == 59 || i == 79 || i == 99 || i == 119 || i == 139 || i == 159 || i == 179 || i == 199 || i == 219)
                    {
                        j++;
                        k = 0;
                    }
                    else if(i == 239 || i == 259 || i == 279 || i == 299 || i == 319 || i == 339 || i == 359 || i == 379 || i == 399)
                    {
                        j++;
                        k = 0;
                    }

                }

                k = 0;
                j = 1;
                for(i=20; i<400; i++)
                {
                    if (verifieClique = cliqueSurIcone(event, 2, 33, 100 + j*33, 5 + k*33))
                    porteY[i] = NULL;
                    k++;

                    if(i == 39 || i == 59 || i == 79 || i == 99 || i == 119 || i == 139 || i == 159 || i == 179 || i == 199 || i == 219)
                    {
                        j++;
                        k = 0;
                    }
                    else if(i == 239 || i == 259 || i == 279 || i == 299 || i == 319 || i == 339 || i == 359 || i == 379 || i == 399)
                    {
                        j++;
                        k = 0;
                    }
                }
            }

            break;

       }

       SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //On remplit notre surface d'une couleur. On indique premièrement la surface qu'on veut colorier, ensuite on envoie NULL car cette valeur nous intéresse pas et en troisième, on fait appel à la fonction "MapRGB".
       //La fonction MapRGB focntionne comme ceci: On indique premièrement le nombre de couleur (32bits) qu'on va chercher dans notre variable ecran dans laquelle on avait indiqué le format, puis le code rgb de notre couleur (ici: 0, 0, 0 ---> noir)

       SDL_BlitSurface(fond, NULL, ecran, &position);
       SDL_BlitSurface(surface, NULL, ecran, &position); //On colle notre surface sur ecran, et à une position bien précise qu'on a déjà indiqué
       SDL_BlitSurface(surface2, NULL, ecran, &position);
       SDL_BlitSurface(fondGrille, NULL, ecran, &positionFond);
       for (i=0 ; i<420 ; i++)
       {
           SDL_BlitSurface(porteX[i], NULL, ecran, &positionPorteX[i]);
       }
       for (i=0 ; i<420 ; i++)
       {
           SDL_BlitSurface(porteY[i], NULL, ecran, &positionPorteY[i]);
       }
       for (i=0 ; i<400 ; i++)
       {
           SDL_BlitSurface(caseDone[i], NULL, ecran, &positionCase[i]);
       }

       SDL_Flip(ecran); //Mise à jour de l'écran

    }

    SDL_FreeSurface(fond);
    SDL_FreeSurface(surface); // On libère la mémoire utilisée par la surface
    SDL_FreeSurface(surface2);
    SDL_FreeSurface(fondGrille);
    for (i=0 ; i<420 ; i++)
    {
        SDL_FreeSurface(porteX[i]);
    }
    for (i=0 ; i<420 ; i++)
    {
        SDL_FreeSurface(porteY[i]);
    }
    for (i=0 ; i<400 ; i++)
    {
        SDL_FreeSurface(caseDone[i]);
    }

}

int passeSurIcone(SDL_Event event, int largeur, int hauteur, int positionx, int positiony)
{

    int i = 0;
    int e = 0;
    int passe = 0;

            for (i=0; i <= largeur; i++)
              {

                    for (e=0; e <= hauteur; e++)
                    {
                        if (event.motion.x == i + positionx && event.motion.y == e + positiony)
                        {
                            passe = 1;
                        }

                    }

                    if (event.motion.x == i + positionx && event.motion.y == positiony)
                    {
                        passe = 1;
                    }

              }

    return passe;
}


int cliqueSurIcone(SDL_Event event, int largeur, int hauteur, int positionx, int positiony)
{

    int i = 0;
    int e = 0;
    int clique = 0;

            for (i=0; i <= largeur; i++)
              {

                    for (e=0; e <= hauteur; e++)
                    {
                        if (event.button.x == i + positionx && event.button.y == e + positiony)
                        {
                            clique = 1;
                        }

                    }

                    if (event.button.x == i + positionx && event.button.y == positiony)
                    {
                        clique = 1;
                    }

              }

    return clique;
}


int rand_ab(int a, int b)
{
    int temps = 0;

    temps = SDL_GetTicks();
    srand(time(NULL)+temps);
    return rand()%(b-a) +a;
}

int bouger(int r, int *random, SDL_Surface *caseDone[])
{
    int random2 = 0;

    random2 = rand_ab(1, 3);
    switch(random2)
    {
        case 1:
        switch(*random)
        {
            case HAUT_GAUCHE:
            caseDone[r]= NULL;
            *random = HAUT;
            r = r+1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case HAUT:
            caseDone[r]= NULL;
            *random = HAUT_DROIT;
            r = r+1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case HAUT_DROIT:
            caseDone[r]= NULL;
            *random = DROIT;
            r = r+20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case DROIT:
            caseDone[r]= NULL;
            *random = BAS_DROIT;
            r = r+20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case BAS_DROIT:
            caseDone[r]= NULL;
            *random = BAS;
            r = r-1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case BAS:
            caseDone[r]= NULL;
            *random = BAS_GAUCHE;
            r = r-1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case BAS_GAUCHE:
            caseDone[r]= NULL;
            *random = GAUCHE;
            r = r-20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case GAUCHE:
            caseDone[r]= NULL;
            *random = HAUT_GAUCHE;
            r = r-20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
        }
        break;
        case 2:
        switch(*random)
        {
            case HAUT_GAUCHE:
            caseDone[r]= NULL;
            *random = GAUCHE;
            r = r+20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case HAUT:
            caseDone[r]= NULL;
            *random = HAUT_GAUCHE;
            r = r-1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case HAUT_DROIT:
            caseDone[r]= NULL;
            *random = HAUT;
            r = r-1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case DROIT:
            caseDone[r]= NULL;
            *random = HAUT_DROIT;
            r = r-20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case BAS_DROIT:
            caseDone[r]= NULL;
            *random = DROIT;
            r = r-20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case BAS:
            caseDone[r]= NULL;
            *random = BAS_DROIT;
            r = r+1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case BAS_GAUCHE:
            caseDone[r]= NULL;
            *random = BAS;
            r = r+1;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
            case GAUCHE:
            caseDone[r]= NULL;
            *random = BAS_GAUCHE;
            r = r+20;
            caseDone[r]= IMG_Load("Fichiers/monstre.bmp");
            break;
        }
        break;
    }

    return r;
}

