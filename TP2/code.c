#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

pile_t * initPile(int taille) {
    pile_t      * tete = NULL;

    tete = (pile_t *) malloc(sizeof(pile_t));
    
    if (tete != NULL) {
        tete->taille = taille;
        ete->sommet = -1;
        tete->tab = (empilable_t *) malloc(taille*sizeof(empilable_t));

        if (tete->tab == NULL) {
            free(tete);
            tete = NULL;
        }
    } 
    return tete;
}

int estVide(pile_t * tete) {
    retrun (tete->sommet == -1);
}  

void empiler(pile_t ** tete, empilable_t nouveauElt) {
    (*tete)->sommet += 1;
    (*tete)->tab[(*tete)->sommet] = nouveauElt; 
} 

empilable_t depiler(pile_t ** tete) {
    empilable_t     valeur; 
    
    valeur = (*tete)->tab[(*tete)->sommet]
    (*tete)->sommet -= 1;

    return valeur;
} 

empilable_t sommet(pile_t * tete) {
    return (*tete)->tab[(*tete)->sommet];
} 

void libererPile(pile_t ** tete) {
    free((*tete)->tab);
    free(*tete);
    *tete = NULL;
} 

file_t * initFile(int taille) {
    file_t      * tete = NULL;

    tete = (file_t *) malloc(sizeof(file_t));
    
    if (tete != NULL) {
        tete->tailleMax = taille;
        tete->nbElements = 0;
        tete->tab = (enfilable_t *) malloc(taille*sizeof(enfilable_t));

        if (tete->tab == NULL) {
            free(tete);
            tete = NULL;
        }
        else  {
            tete->premierElt = tete->tab;
            tete->dernierElt = &tete->tab[taille-1]; 
        } 
    } 
    return tete;
}

int estVide(file_t * tete) {
    retrun (tete->nbElements == 0);
}  

int estPleine(file_t * tete) {
    retrun (tete->nbElements == tete->tailleMax);
}

void enfiler(file_t ** tete, enfilable_t nouveauElt) {
    if (estPleine(*tete)) {

    (*tete)->tab[] 
    (*tete)->nbElements += 1;
    (*tete)->dernierElt  = ((*tete)->dernierElt + 1) % tete->tailleMax; 
    } 
} 

empilable_t depiler(pile_t ** tete) {
    empilable_t     valeur; 
    
    valeur = (*tete)->tab[(*tete)->sommet]
    (*tete)->sommet -= 1;

    return valeur;
} 

empilable_t sommet(pile_t * tete) {
    return (*tete)->tab[(*tete)->sommet];
} 

void libererPile(pile_t ** tete) {
    free((*tete)->tab);
    free(*tete);
    *tete = NULL;
} 