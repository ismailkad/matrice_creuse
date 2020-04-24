#ifndef tp3_h
#define tp3_h

#include <stdio.h>

typedef struct element {
    int colonne;
    int valeur;
    struct element* suivant;
} element;

typedef element* liste_lignes;

typedef struct matrice_creuse {
    liste_lignes* tableauLignes;
    int Nlignes;
    int Ncolonnes;
} matrice_creuse;

int get_int_len(int value);
element * newelement(element * suivant, int col,int valeur);
int remplirMat(matrice_creuse *m, int N, int M);
void PrintBorder(int j,int longestlength);
void PrintRow(int num_espaces,int valeur);
void afficherMat(matrice_creuse m, int longestlenght);
void addMat(matrice_creuse m1, matrice_creuse m2);
int getValue(matrice_creuse m, int i, int j);
void putValue(matrice_creuse m, int i, int j, int val);
int nombreOctetsGagnes(matrice_creuse m1);
void freeMat(matrice_creuse *m);


#endif /* tp3_h */
