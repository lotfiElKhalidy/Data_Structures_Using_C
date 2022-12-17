#ifndef CODE_H
#define CODE_H

// Structure représentant un noeud
typedef struct noeud{
    float valeur;
    struct noeud * filsGauche;
    struct noeud * filsDroit;
}noeud_t;   

#endif 