#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

// Fonction pour saisir les éléments non-nuls d'une matrice creuse
void remplirMat(matrice_creuse *m, int N, int M) {
    
    int i, j;
    int first_elem; //first_elem sera un drapeau qui nous permettra de déterminer si le premier élément a été saisi ou non
    int saisie;

    element *elem, *temp = NULL;
    
    m->tableauLignes = malloc(N*sizeof(liste_lignes)); //on alloue de la mémoire aux N lignes
    m->Ncolonnes = M;
    m->Nlignes = N;
    
    for (i=0; i<N; i++) {
        
        first_elem = 0; //on initialise notre drapeau à 0 à chaque itération de i donc à chaque nouvelle ligne
        m->tableauLignes[i] = NULL; //on initialise la liste à NULL au cas ou il n'y'ait aucun élément
        
        for(j=0;j<M; j++) {
            
            printf("Veuillez saisir l'élément à la case (%d,%d) : ",i,j);
            scanf("%d",&saisie);
            
            if(saisie!=0) {
                
                elem=malloc(sizeof(element)); //on alloue de la mémoire à l'élément qui est non nul
                elem->colonne=j;
                elem->valeur=saisie;
                elem->suivant = NULL; //on ne sait pas si notre élément sera le dernier élément de la liste donc on initialise toujours elem->suivant à NUL
                
                if (first_elem == 1) //si notre élément n'est pas le premier de la ligne
                    temp->suivant = elem;
                else { //si notre élément est le premier élément de notre ligne
                    m->tableauLignes[i] = elem;
                    first_elem = 1;
                }
                temp=elem; //on garde en mémoire cet élément afin de pouvoir le lier au suivant

            }
        }
    }
}



// Fonction pour afficher une matrice creuse
void afficherMat(matrice_creuse m) {

    int i,j;
    int zero = 0;
    
    for (i=0; i<m.Nlignes; i++) {
        
        element *pointeur = m.tableauLignes[i]; //pour chaque ligne on assigne un pointeur de type élément 
        
        for (j=0; j<m.Ncolonnes; j++ ) {
            
            if ((pointeur != NULL ) && (pointeur->colonne == j)) { //si la ligne n'est pas vide et que le pointeur est à la bonne colonne
                
                printf("%5d", pointeur->valeur); 
                pointeur = pointeur->suivant; //on passe à l'élément suivant
            }
            else //si le pointeur n'est pas à la bonne position ou si il est NULL alors l'élément est égal à 0
                printf("%5d", zero);
        }
        
        printf("\n");
    }
}
