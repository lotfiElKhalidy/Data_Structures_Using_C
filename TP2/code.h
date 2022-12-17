#ifndef CODE_H
#define CODE_H

// On ajoute cette ligne pour utiliser la pile après avec n'importe quelle structure qu'on veut
typedef char empilable_t;
typedef char enfilable_t;

// Structure de la pile 
typedef struct pile {
  int taille;
  int sommet; // Le sommet est géré par son indice
  empilable_t * tab;
} pile_t;

// Structure de la file 
typedef struct file {
  int tailleMax;
  int nbElements; // On ajoute le nb d'élts pour distinguer la file pleine de la file vide 
  enfilable_t * premierElt;
  enfilable_t * dernierElt; 
  enfilable_t * tab;
} file_t;


// Prototypes des fonctions
pile_t * initPile(int );
int estVide(pile_t *);
void empiler(pile_t **, empilable_t );
empilable_t depiler(pile_t **);
empilable_t sommet(pile_t *);
void libererPile(pile_t ** tete);
#endif
