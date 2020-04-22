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

void remplirMat(matrice_creuse *m, int N, int M);
void afficherMat(matrice_creuse m);
void addMat(matrice_creuse m1, matrice_creuse m2);
int getValue(matrice_creuse m, int i, int j);
void putValue(matrice_creuse m, int i, int j, int val);
