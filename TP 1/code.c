                /* ----------------------------------------------------------------------- */
                                        /* Nom du fichier : code.c */
                        /* Rôle : Le fichier contient l'implémentation des fonctions */
                /* ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

/* ----------------------------------------------------------------------- */
/* existe vérifie si une chaîne existe dans une liste chaînée ou non */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La valeur entière retournée est 1 si la chaîne existe */
/* dans la liste et 0 si la chaîne n'existe pas. */
/* ----------------------------------------------------------------------- */
int existe(char * chaine, listeS_t * lch) {
    int          res = 0;
    semaine_t  * cour = NULL;

    cour = lch->tete->suivant;

    while (cour != NULL) {
        if (comparerChaine(chaine, cour->anneeSemaine, 6) == 0) { 
            res = 1;
        }
        cour = cour->suivant;
    }
    return res;
}

/* ----------------------------------------------------------------------- */
/* Tri permet de trouver l'emplacement où on doit insérer la semaine */
/* pour avoir une liste triée */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La fonction retourne l'adresse de l'élément précédent */
/* l'emplacement où on souhaite insérer la nouvelle semaine */
/* ----------------------------------------------------------------------- */
semaine_t * Tri(char * chaine, listeS_t * lch) {
    semaine_t   * prec;
    semaine_t   * cour;

    prec = lch->tete;
    cour = lch->tete->suivant;

    while ((cour != NULL) && (comparerChaine(chaine, cour->anneeSemaine, 6) > 0)) {
        prec = prec->suivant;
        cour = cour->suivant;
    }
    return prec;
}

/* ----------------------------------------------------------------------- */
/* rechercheSemaine permet de trouver une semaine dans une liste chaînée */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La fonction retourne l'adresse du bloc qui contient */
/* la semaine entrée en paramètre */
/* ----------------------------------------------------------------------- */
semaine_t * rechercheSemaine(char * chaine, listeS_t * lch) {
    semaine_t   * cour = NULL;

    cour = lch->tete->suivant;

    while ((cour != NULL) && (comparerChaine(chaine, cour->anneeSemaine, 6) != 0)) {
        cour = cour->suivant;
    }
    return cour;
}

/* ----------------------------------------------------------------------- */
/* Tri2 permet de trouver l'emplacement où on doit insérer l'action */
/* pour avoir une liste triée */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La fonction retourne l'adresse de l'élément précédent */
/* l'emplacement où on souhaite insérer la nouvelle action */
/* ----------------------------------------------------------------------- */
action_t * Tri2(char * chaine, listeA_t * lch) {
    action_t   * prec;
    action_t   * cour;

    prec = lch->tete;
    cour = lch->tete->suivant;

    while ((cour != NULL) && (comparerChaine(chaine, cour->jourHeure, 3) > 0)) {
        prec = prec->suivant;
        cour = cour->suivant;
    }
    return prec;
}

/* ----------------------------------------------------------------------- */
/* creerListe permet de construire l'agenda (liste à deux niveaux) */
/* à partir d'un fichier */
/* */
/* En entrée: fichier (supposé ouvert) */
/* */
/* En sortie: La foction retourne l'adresse de tête de la liste */
/* qu'elle vient de construire. */
/* ----------------------------------------------------------------------- */
listeS_t * creerListe(FILE * fichier) {
    listeS_t    * lch;
    listeA_t    * lchA;
    semaine_t   * place;
    semaine_t   * semaine;
    semaine_t   * semaineCourante;
    action_t    * place2;
    action_t    * action;
    char        * buffer;
    char        * chaine;

    // Allocation de la tete de la liste
    lch = (listeS_t *) malloc(sizeof(listeS_t));
    lch->tete = (semaine_t *) malloc(sizeof(semaine_t));
    
    // Allocation des pointeurs nécessaires
    semaineCourante = (semaine_t *) malloc(sizeof(semaine_t));
    place = (semaine_t *) malloc(sizeof(semaine_t));
    place2 = (action_t *) malloc(sizeof(action_t));
    buffer = (char *) malloc(20*sizeof(char));
    chaine = (char *) malloc(20*sizeof(char));

    // Vérification des allocations
    if (!buffer || !chaine || !lch || !semaineCourante || !place || !place2 || !lch->tete) {
        printf("Erreur : Allocation dynamique échouée\n");
        exit(0);
    }

    // Initialisation de la tete de la liste
    lch->tete->suivant = NULL;
    
    // Premier parcours du fichier : On crée la liste des semaines (premier niveau de la liste)
    while (fgets(buffer, 20, fichier) != NULL) {
        strncpy(chaine, buffer, 6);

        // Si la semaine ne contient pas une action ou qu'elle existe déjà dans la liste, on ne crée pas le bloc 
        if ((strlen(buffer) > 9) && (existe(chaine, lch) == 0)) { 
            
            semaine = (semaine_t *) malloc(sizeof(semaine_t));
            lchA = (listeA_t *) malloc(sizeof(listeA_t));
            lchA->tete = (action_t *) malloc(sizeof(action_t));

            if(!semaine || !lchA || !lchA->tete) {
                printf("Erreur : Allocation dynamique echouee");
                exit(0);
            }
            
            lchA->tete->suivant = NULL; 

            strncpy(semaine->anneeSemaine, buffer, 6);
            semaine->action = lchA;
            place = Tri(chaine, lch);
            
            // Insertion du bloc semaine dans la liste
            semaine->suivant = place->suivant;
            place->suivant = semaine;
        }
    }
    
    // Avant de commencer le second parcours du fichier, il faut retourner au début du fichier
    fseek(fichier, 0, SEEK_SET);

    // Second parcours du fichier : On crée la liste des actions correspondante à chaque semaine
    while (fgets(buffer, 20, fichier)) {
        // Si la semaine ne contient pas une action, on ne crée pas le bloc
        if (strlen(buffer) > 9) {
            strncpy(chaine, buffer, 6);

            semaineCourante = rechercheSemaine(chaine, lch);

            action = (action_t *) malloc(sizeof(action_t));

            if (!action) {
                printf("Erreur : Allocation dynamique échouée\n");
                exit(0);
            }

            strncpy(action->jourHeure, buffer+6, 3);
            strncpy(action->nomAction, buffer+9, 10);

            place2 = Tri2(action->jourHeure, semaineCourante->action);
            
            // Insertion du bloc action dans la liste
            action->suivant = place2->suivant; 
            place2->suivant = action;
        }
    }
    free(buffer);
    free(chaine);

    return lch;   
} 

/* ----------------------------------------------------------------------- */
/* afficherListe permet d'afficher la liste d'adresse de début lch */
/* */
/* En entrée: lch Une chaîne de caractères */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void afficherListe(listeS_t * lch) {
    semaine_t   * cour;  
    action_t    * cour2;

    cour = lch->tete->suivant;
    printf("\n\n ================= AGENDA ================ \n\n");
    
    while (cour != NULL) {
        printf(" AnnéeSemaine : ");
        print(cour->anneeSemaine, 6);
        cour2 = cour->action->tete->suivant;

        while (cour2 != NULL) {
            printf("\t jourHeure : ");
            print(cour2->jourHeure, 3);
            
            printf("\t\t Action : ");
            print(cour2->nomAction, 10);
            printf("\n");

            cour2 = cour2->suivant;
        } 
        cour = cour->suivant;
    }
}

/* ----------------------------------------------------------------------- */
/* sauvegarderSDD permet de stocker une liste dans un fichier */
/* */
/* En entrée: nomfichier, lch Une chaîne de caractères */
/* et un fichier (supposé ouvert) */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void sauvegarderSDD(FILE * nomFichier, listeS_t * lch) {
    semaine_t   * cour ; 
    action_t    * cour2;

    
    if (lch != NULL) {
        cour = lch->tete->suivant;

        while (cour != NULL) {
            cour2 = cour->action->tete->suivant;

            while (cour2 != NULL) {
                fprint(nomFichier, cour->anneeSemaine, 6);
                fprint(nomFichier, cour2->jourHeure, 3);
                fprint(nomFichier, cour2->nomAction, 10);
                cour2 = cour2->suivant;
                fprintf(nomFichier, "\n");
            }
            cour = cour->suivant;
        }
    }
}

/* ----------------------------------------------------------------------- */
/* verifJour permet de verifier si le jour est deja present dans la lco */
/* */
/* En entrée: jour, lcoTete, lcofin Un caractere qui contient le jour   */
/* et deux pointeurs (tete et fin de la liste contigue) */
/* */
/* En sortie: La valeur entiere retournee est 1 si on trouve jour dans */
/* la liste contigue et 0 sinon. */
/* ----------------------------------------------------------------------- */
int verifJour(char * lcoTete, char * lcoFin, char jour){
    int       trouve = 0;
    char    * cour = lcoTete;

    while ((cour != lcoFin) && (!trouve)){
        if(strcmp(cour, &jour) == 0){
            trouve = 1;
        }
        cour++;
    }
    return trouve;
}

/* ----------------------------------------------------------------------- */
/* comparerChaine compare deux chaines de caractere de longueur n */
/* */
/* En entrée: motif, nomAction, n Deux chaines de caracteres et la   */
/* longueur du motif */
/* */
/* En sortie: La valeur entiere retournee est 0 si le motif est le nom  */
/* de l'action, 0 sinon.  */
/* ----------------------------------------------------------------------- */
int comparerChaine(char motif[], char nomAction[], int n){
    int    res = 0;
    int    cpt = 0;

    while((cpt < n) && (motif[cpt] == nomAction[cpt])){
        cpt++;
    }
    if (cpt < n){
        if (motif[cpt] > nomAction[cpt]) {
            res = 1;
        }
        else {
            res = -1;
        }
        
    }
    return res;
}

/* ----------------------------------------------------------------------- */
/* creerLco cree une liste contigue des jours où une action contenant un */
/* un motif est presente*/
/* */
/* En entrée: motif, lch Une chaine de caractere et la liste chainee */
/* cree dans la question 1  */
/* */
/* En sortie: Le pointeur de tete de la liste contigue qu'on a cree  */
/* ----------------------------------------------------------------------- */
void creerLco (listeS_t * lch, char motif[], char ** lcoTete, char ** lcoFin){
    semaine_t   * courLch;
    action_t    * cour2;
    char        * courLco;

    courLch = lch->tete->suivant;

    *lcoTete = (char *) malloc(100*sizeof());

    if (!*lcoTete) {
        printf("Erreur : Allocation dynamique échouée\n");
        exit(0);
    }

    *lcoFin = *lcoTete;
    courLco = *lcoTete;

    while(courLch != NULL){
        cour2 = courLch->action->tete->suivant;
        
        while(cour2 != NULL){
            if(comparerChaine(motif, cour2->nomAction, 10) == 0){
                if(!verifJour(*lcoTete, *lcoFin, cour2->jourHeure[0])){
                    strncpy(courLco, cour2->jourHeure, 1);
                    courLco++;
                    *lcoFin = courLco;
                }
            }
            cour2 = cour2->suivant;
        }
        courLch = courLch->suivant;
    }   
}

/* ----------------------------------------------------------------------- */
/* afficherListe permet d'afficher la liste d'adresse de début lch */
/* */
/* En entrée: lch Une chaîne de caractères */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void afficherLco(char * lcoTete, char * lcoFin) {
    char   * cour = lcoTete;

    printf("\n\n ================= LCO ================ \n\n");
  
    while(cour != lcoFin) {
        printf("jour : ");
        print(cour, 1);
        cour++;
    }
}
noeud_t     * noeud;
/* ----------------------------------------------------------------------- */
/* recherche permet de chercher l'action correspondante à l'année, la */
/* semaine, le jour et l'heure passés en paramètre */
/* */
/* En entrée: a0, anneeSemaine, jourHeure Deux chaînes de caractères */
/* et un pointeur (adresse de tête de la liste) */
/* */
/* En sortie: La fonction retourne l'adresse de tête de la liste */
/* qu'elle vient de construire. */
/* ----------------------------------------------------------------------- */
action_t * recherche(listeS_t * a0, char * anneeSemaine, char * jourHeure) {
    semaine_t    * cour;
    action_t     * cour2;
    action_t     * prec2;

    cour = a0->tete->suivant;
    
    while ((cour != NULL) && (comparerChaine(cour->anneeSemaine, anneeSemaine, 6) < 0)) {
        cour = cour->suivant;
    }
    
    if (comparerChaine(cour->anneeSemaine, anneeSemaine, 6) == 0) {
        prec2 = cour->action->tete;
        cour2 = cour->action->tete->suivant; 

        while ((cour2 != NULL) && (comparerChaine(cour2->jourHeure, jourHeure, 3) < 0)) {
            prec2 = prec2->suivant;
            cour2 = cour2->suivant;
        }
    }
    else {
        printf("Les coordonnées que vous avez entré ne correspond à aucun élément de la liste\n");
        prec2 = NULL;
    }
    return prec2;
}

/* ----------------------------------------------------------------------- */
/* recherche permet de supprimer l'action correspondante à l'année, la */
/* semaine, le jour et l'heure passés en paramètre */
/* */
/* En entrée: a0, anneeSemaine, jourHeure Deux chaînes de caractères */
/* et un double pointeur (adresse de tête de la liste) */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void supprimerAction(listeS_t ** a0, char * anneeSemaine, char * jourHeure) {
    action_t    * tmp = NULL;
    action_t    * prec = NULL;
    
    prec = recherche(*a0, anneeSemaine, jourHeure); 

    if (!prec) {
        exit(0);
    }

    if ((prec->suivant != NULL) && (comparerChaine(prec->suivant->jourHeure, jourHeure, 3) == 0)) {
        tmp = prec->suivant;
        prec->suivant = tmp->suivant;  
        free(tmp);
    } 
}

/* ----------------------------------------------------------------------- */
/* libererListe permet de libérer la liste d'adresse de dénut lch */
/* */
/* En entrée : lch Un double pointeur (adresse de tête de la liste) */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void libererListe(listeS_t ** lch) {
    semaine_t    * cour;
    semaine_t    * tmp;
    action_t     * cour2;
    action_t     * tmp2;

    cour = (*lch)->tete->suivant;
    
    while (cour != NULL) {
        cour2 = cour->action->tete->suivant;
        
        while (cour2 != NULL) {
            tmp2 = cour2;
            cour2 = cour2->suivant;
            free(tmp2);
        }
        tmp = cour;
        cour = cour->suivant;
        free(tmp->action->tete);   
        free(tmp->action);
        free(tmp);
    }
    free(*lch);
}

/* --------------------------------------------------------------------------- */
/* libererLco permet de libérer la liste contigue d'adresse de dénut lcoTete */
/* */
/* En entrée : lcoTete Un double pointeur (adresse de tête de la liste) */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* --------------------------------------------------------------------------- */
void libererLco(char ** lcoTete) {
    char    * cour;
    
    cour = *lcoTete;
    free(cour);
}

/* ----------------------------------------------------------------------- */
/* print permet d'afficher les taille premières caractères */
/* d'une chaine de caractères d'adresse chaine */
/* */
/* En entrée : chaine, taille Une chaine de caractères */
/* et un entier */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void print(char * chaine, int taille) {
    for (int i=0; i<taille; i++) {
        printf("%c",chaine[i]);
    }
    printf("\n");
}

/* ----------------------------------------------------------------------- */
/* fprint permet d'écrire les taille premières caractères */
/* d'une chaine de caractères d'adresse chaine dans un fichier */
/* */
/* En entrée : chaine, fichier, taille Une chaine de caractères */
/* un fichier (supposé ouvert) et un entier */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */
void fprint(FILE * fichier, char * chaine, int taille) {
    for (int i=0; i<taille; i++) {
        fprintf(fichier, "%c", chaine[i]);
    }
    //printf("\n");
}
