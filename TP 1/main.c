                /* ------------------------------------------------------------------------- */
                                        /* Nom du fichier : main.c */
                    /* Rôle : Le fichier contient la fonction main et les tests unitaires */
                /* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teZZt.h"
#include "code.h"

BEGIN_TEST_GROUP(test)

TEST(agenda) {
    FILE         * fichier;
    listeS_t     * lch;

    // Cas de la liste vide (fichier vide)
    fichier = fopen("agendaTest1.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        
        CHECK(NULL != lch);
        CHECK( NULL == lch->tete->suivant);
        
        fclose(fichier);
        libererListe(&lch);
    }

    // Cas de la liste vide (fichier contenant des semaines sans actions)
    fichier = fopen("agendaTest2.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        
        CHECK(NULL != lch);
        CHECK( NULL == lch->tete->suivant);
        
        fclose(fichier);
        libererListe(&lch);
    } 

    // Cas d'une liste à un élément (fichier contenant une ligne)
    fichier = fopen("agendaTest3.txt", "r");
    
    if (fichier) {
        lch = creerListe(fichier);
        
        CHECK(NULL != lch);
        CHECK(0 == comparerChaine(lch->tete->suivant->anneeSemaine, "202215", 6));
        CHECK(0 == comparerChaine(lch->tete->suivant->action->tete->suivant->jourHeure, "108", 3));
        CHECK(0 == comparerChaine(lch->tete->suivant->action->tete->suivant->nomAction, "TPs de SDD", 10));
        
        fclose(fichier);
        libererListe(&lch);
    } 
}

TEST(lco) {
    listeS_t   * lch;
    FILE       * fichier;
    char         motif[10] = "TPs de XDD"; 
    char         motif2[10] = "TPs de SDD"; 
    char       * lcoTete = NULL;
    char       * lcoFin = NULL;

    // Cas de lco vide (motif n'existe pas dans la liste)
    fichier = fopen("lcoTest1.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        creerLco(lch, motif, &lcoTete, &lcoFin);
        
        CHECK(NULL != lch);
        CHECK(lcoFin == lcoTete);
        
        fclose(fichier);
        libererListe(&lch);
        libererLco(&lcoTete);
    }

    // Cas de lco à un élément  
    fichier = fopen("lcoTest2.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        creerLco(lch, motif2, &lcoTete, &lcoFin);
        
        CHECK(NULL != lch);
        CHECK(lcoTete != lcoFin);
        CHECK(0 == comparerChaine(lcoTete, "1", 1));
        
        fclose(fichier);
        libererListe(&lch);
        libererLco(&lcoTete);
    }

    // Cas de lco à deux éléments   
    fichier = fopen("lcoTest3.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        creerLco(lch, motif2, &lcoTete, &lcoFin);
        
        CHECK(NULL != lch);
        CHECK(lcoTete != lcoFin);
        CHECK(0 == comparerChaine(lcoTete, "7", 1));
        CHECK(0 == comparerChaine(lcoTete+1, "1", 1));
        
        fclose(fichier);
        libererListe(&lch);
        libererLco(&lcoTete);
    }
}  

TEST(suppAction) {
    FILE      * fichier;
    listeS_t  * lch;
    char        anneeSemaine[6] = "202215";
    char        jourHeure[3] = "108"; 
    char        anneeSemaine2[6] = "202016";
    char        jourHeure2[3] = "498"; 

    // Cas ou l'année, la semaine, le jour et l'heure existent dans la liste
    fichier = fopen("suppActionTest1.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        supprimerAction(&lch, anneeSemaine, jourHeure);
        
        CHECK(NULL != lch);
        CHECK(NULL != recherche(lch, anneeSemaine, jourHeure));
        
        fclose(fichier);
        libererListe(&lch);
    }

    // Cas ou l'année, la semaine, le jour et l'heure n'existent pas dans la liste
    fichier = fopen("suppActionTest2.txt", "r");

    if (fichier) {
        lch = creerListe(fichier);
        
        CHECK(NULL != lch);
        CHECK(NULL == recherche(lch, anneeSemaine2, jourHeure2));
        
        fclose(fichier);
        libererListe(&lch);
    }
}

END_TEST_GROUP(test)


// main 
int main(int argc, char ** argv) {
    FILE       * fichier;
    FILE       * file;
    listeS_t   * liste;
    char       * anneeSemaine = NULL;
    char       * jourHeure = NULL;
    char       * lcoTete = NULL;
    char       * lcoFin = NULL;
    char         motif[10] = "TPs de SDD";
    char         exempleAnneeSemaine[6] = "202205";
    char         exempleJourHeure[13] = "314TPs de AN ";

    anneeSemaine = (char *) malloc(50*sizeof(char));
    jourHeure = (char *) malloc(50*sizeof(char));

    if (!anneeSemaine || !jourHeure) {
        printf("Erreur : Allocation dynamique échouée\n");
        exit(0);
    }

    if (argv[1]) {
        fichier = fopen(argv[1], "r");

        if (!fichier) {
            printf("Erreur : Ouverture du fichier impossible\n");
            exit(0);
        }
        else {
            strcpy(anneeSemaine, exempleAnneeSemaine);
            strcpy(jourHeure, exempleJourHeure);
            
            liste = creerListe(fichier);
            supprimerAction(&liste, anneeSemaine, jourHeure);
            afficherListe(liste);

            file = fopen("sauvegarderSDD.txt", "w");

            if (file) {
                sauvegarderSDD(file, liste);
            }
            
            creerLco(liste, motif, &lcoTete, &lcoFin);
            afficherLco(lcoTete, lcoFin);
            
            libererListe(&liste);
            libererLco(&lcoTete);
    
            fclose(fichier);
            fclose(file);
            free(anneeSemaine);
            free(jourHeure);
        } 
    }
    else {
        printf("Vous n'avez pas entré le nom du fichier qui contient votre agenda\n");
        exit(0);
    }
    
    RUN_TEST_GROUP(test); 
    
    return 0;
} 