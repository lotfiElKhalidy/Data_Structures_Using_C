#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#define MAX 100


/* ----------------------------------------------------------------------- */
/* construireABR permet de construire un arbre binaire de recherche à */
/* à partir d'un fichier contenant les valeurs numériques */ 
/* */
/* En entrée: fichier un fichier */
/* */
/* En sortie: La fonction retourne la tete de l'arbre */
/* ----------------------------------------------------------------------- */
noeud_t * construireABR(FILE * fichier) {
    noeud_t     * t;
    noeud_t     * noeud;
    noeud_t     * cour;
    char        * buffer;
    float         valeur;

    // Allocation de la racine de l'arbre
    t = (noeud_t *) malloc(sizeof(noeud_t));

    // Allocation des pointeurs nécessaires
    buffer = (char *) malloc(20*sizeof(char));


    if (!t || !noeud || !buffer) {
        printf("Erreur : Allocation dynamique échouée\n");
        exit(0);
    }

    // Initialisation de la racine de l'arbre
    t = NULL;
    
    // Parcours du fichier : On crée l'arbre binaire de recherche
    while (fgets(buffer, 20, fichier) != NULL) {
        valeur = (float) buffer; 

        cour = t;

        // On ajoute cette condition pour gérer le cas de la liste vide
        if (cour == NULL){
            noeud = (noeud_t *) malloc(sizeof(noeud_t));

            if (!noeud) {
                printf("Erreur : Allocation dynamique échouée");
                exit(0);
            } 

            neoud->valeur = valeur;
            noeud->filsDroit = NULL;
            noeud->filsGauche = NULL;
            
        } 

        while (cour != NULL) {

            // Le cas ou il faut insérer dans la sous arborescence de droite
            if (cour->valeur < valeur) {
                if (cur->filsDroit == NULL) {
                    noeud = (noeud_t *) malloc(sizeof(noeud_t));

                    if (!noeud) {
                        printf("Erreur : Allocation dynamique échouée");
                        exit(0);
                    } 

                    neoud->valeur = valeur;
                    noeud->filsDroit = NULL;
                    noeud->filsGauche = NULL;
                }
                else {
                    cour = cour->filsDroit;
                }    
            }

            // Le cas ou il faut insérer dans la sous arborescence de gauche
            if (cour->valeur > valeur){
                if (cur->filsGauche == NULL) {
                    noeud = (noeud_t *) malloc(sizeof(noeud_t));

                    if (!noeud) {
                        printf("Erreur : Allocation dynamique échouée");
                        exit(0);
                    } 

                    neoud->valeur = valeur;
                    noeud->filsDroit = NULL;
                    noeud->filsGauche = NULL;
                }
                else {
                    cour = cour->filsGauche;
                } 
            }  
        }
    } 
    free(buffer);

    return t;   
} 

/* ----------------------------------------------------------------------- */
/* parcoursInfixe permet de faire un parcours infixe de l'arbre */
/* */
/* En entrée: a0 tete de l'arbre */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* */
/* Ce code fait appel aux fonctions de pile */
/* ----------------------------------------------------------------------- */
void parcoursInfixe(noeud_t * a0) {
    empilable     * cour;
    pile_t        * pile;
    
    cour = a0;
    pile = initPile(MAX);
    int fin = 0;
    
    while (!fin) {
        
        while (cour != NULL) {
            empiler(&pile, cour);
            cour = cour->filsGauche;
        } 
        
        if (!estVide(pile)) {
            cour = depiler(&pile);
            printf("%f", cour->valeur);
            cour = cour->filsDroit;
        }
        else {
            fin = 1;
        }  
    }

    libererPile(&tete);
}

/* ----------------------------------------------------------------------------- */
/* recherchePere permet de rechercher le pere du noeud qu'on souhaite supprimer */
/* */
/* En entrée: a0 tete de l'arbre, valeur réelle qu'on est entrain de chercher */
/* */
/* En sortie: prec double pointeur qui pointe vers le bloc précèdant */
/* le bloc courant */
/* ----------------------------------------------------------------------------- */
noeud_t ** recherchePere (noeud_t * a0, float valeur) {
    noeud_t        ** prec;
    noeud_t        * cour;
    int fin; 

    prec = &a0;
    cour = a0;
    fin = 0;
    
    while (cour != NULL && !fin) { 
        if (cour->valeur < valeur) {
            prec = &cour;
            cour = cour->filsDroit;
        }
        else {
            if (cour->valeur > valeur) {
                prec = &cour;
                cour = cour->filsGauche;
            }
            else {
                fin = 1;
            }
        } 
    }

    // Cas où la valeur recherchée n'existe pas dans la l'arbre
    if (cour == NULL) {
        prec = NULL;
    } 

    return prec;
}

/* ----------------------------------------------------------------------------- */
/* recherchePlusPetitElement permet de rechercher le noeud qui contient */
/* la plus petite valeur dans un sous-arbre */
/* */
/* En entrée: a0 tete de l'arbre */
/* */
/* En sortie: *prec pointeur vers le bloc qui qui contient la plus petite valeur */
/* ----------------------------------------------------------------------------- */
noeud_t * recherchePlusPetitElement(noeud_t * a0) {
    noeud_t        ** prec;
    noeud_t        * cour;
    
    cour = a0;
    prec = &a0;

    while (cour != NULL) {
        prec = &cour;
        cour = cour->filsGauche;
    }

    return *prec;
}

/* ----------------------------------------------------------------------------- */
/* suppressionNoeud permet de supprimer le noeud qui contient la valeur */
/* */
/* En entrée: a0 tete de l'arbre, valeur réelle qu'on est entrain de chercher */
/* */
/* En sortie: prec double pointeur qui pointe vers le bloc précèdant */
/* le bloc courant */
/* ----------------------------------------------------------------------------- */
noeud_t * suppressionNoeud(noeud_t * a0, float valeur) {
    noeud_t        ** prec;
    noeud_t        * cour;
    noeud_t        * courPlusPetitElement;


    prec = recherchePere(a0, valeur);

    if (prec == NULL) {
        printf("La valeur recherchée n'existe pas dans l'arbre\n");
    }
    else {
        // Le noeud à supprimer est un fils droit
        if (prec->filsDroit->valeur == valeur) {
            cour = prec->filsDroit;
            prec->filsDroit = cour->filsDroit;
        }
        else {
            // Le noeud à supprimer est un fils gauche
            if (prec->filsGauche->valeur == valeur) {
                cour = prec->filsGauche;
                prec->filsGauche = cour->filsDroit;
            } 
        }  
        courPlusPetitElement = recherchePlusPetitElement(cour->filsDroit);
        courPlusPetitElement->filsGauche = cour->filsGauche;
        free(cour);
    }

    return a0;
} 

/* ----------------------------------------------------------------------- */
/* hauteurArbre permet de calculer la hauteur de l'arbre */
/* */
/* En entrée: a0 tete de l'arbre */
/* */
/* En sortie: hauteur entier qui contient la hauteur de l'arbre */
/* */
/* Ce code fait appel aux fonctions de file */
/* ----------------------------------------------------------------------- */
int hauteurArbre(noeud_t * a0) {
    enfilable     * cour;
    file_t        * file;
    
    cour = a0;
    file = initFile(MAX);
    int fin = 0;
    int hauteur = 0;
    
    while (!fin) {
        
        while (cour != NULL && cour->filsGauche != NULL) {
            enfiler(&file, cour->filsGauche);
            cour = cour->filsDroit;
        }
        hauteur += 1; 
        
        if (!estVide(file)) {
            cour = defiler(&file);
        }
        else {
            fin = 1;
        }
    }

    libererFile(&a0);
}
