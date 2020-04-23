#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main() {
    
    int fin, nb_m;
    int i=0, j;
    
    all_matrice *matrice;
    
    printf("Entrez le nombre de matrice souhaité: ");
    scanf("%d", &nb_m);
    
    matrice->nb_matrice = nb_m;
    matrice->tab_mat = malloc(nb_m * sizeof(matrice_creuse)); //création d'un tableau dynamique qui stockera l'adresse de nos matrices
    
    fin = 0; //drapeau qui permettra de déterminer la fin de notre programme
    
    
    while(!fin) {
        
        int c, d, k;
        int N, M, val; //i sera incrementé à chaque fois qu'une matrice sera créee
        
        matrice_creuse m;
        
        /* affichage menu */
        printf("1. Remplir une matrice creuse\n"
               "2. Afficher une matrice creuse\n"
               "3. Donner la valeur d'un élément d'une matrice creuse\n"
               "4. Affecter une valeur à un élément d'une matrice creuse\n"
               "5. Additionner deux matrices creuses\n"
               "6. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n"
               "7. Quitter\n"
               );
        
        c = getchar();
        
        /* suppression des caracteres dans stdin */
        if(c != '\n' && c != EOF) {
            int d;
            while((d = getchar()) != '\n' && d != EOF);
        }
        
        switch(c) {
                
            case '1':
                
                printf("Nb de lignes de la matrice: ");
                scanf("%d", &N);
                
                printf("Nb de colonnes de la matrice: ");
                scanf("%d", &M);
                
                remplirMat(&m, N, M);
                
                matrice->tab_mat[i] = m;
                i++;
                
                printf("La matrice a bien été crée.\n");
            
                
                break;
                
            case '2':
                
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                
                else {
                    printf("Choisir la matrice a afficher: \n");
                    for (j=0; j<i; j++) {
                        printf("%d. Matrice n°%d.\n", j+1, j+1);
                    }
                    
                    d = getchar();
                    
                    if(d != '\n' && d != EOF) {
                        int e;
                        while((e = getchar()) != '\n' && e != EOF);
                    }
                    
                    afficherMat(matrice->tab_mat[d]);
                    
                    break;
                }
                
            case '3':
                
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                else {
                    
                    printf("Choisir la matrice de la valeur a afficher: \n");
                    for (j=0; j<i; j++) {
                        printf("Matrice n°%d.\t", j+1);
                    }
                    
                    d = getchar();
                    
                    if(d != '\n' && d != EOF) {
                        int e;
                        while((e = getchar()) != '\n' && e != EOF);
                    }
                    printf("Numéro de la ligne de l'élément a afficher: ");
                    scanf("%d", &N);
                    
                    printf("Numéro de la colonne de l'élément a afficher: ");
                    scanf("%d", &M);
                    
                    getValue(matrice->tab_mat[d], N, M);
                }
                
            case '4':
                    
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                else {
                    
                    printf("Choisir la matrice a modifier: \n");
                    for (j=0; j<i; j++) {
                        printf("Matrice n°%d.\t", j+1);
                    }
                    
                    d = getchar();
                    
                    if(d != '\n' && d != EOF) {
                        int e;
                        while((e = getchar()) != '\n' && e != EOF);
                    }
                    
                    printf("Numéro de la ligne de l'élément a modifier: ");
                    scanf("%d", &N);
                    
                    printf("Numéro de la colonne de l'élément a modifier: ");
                    scanf("%d", &M);
                    
                    printf("Valeur de l'élément a affecter: ");
                    scanf("%d", &val);
                    
                    putValue(matrice->tab_mat[d], N, M, val);
                    
                    printf("L'élément a bien été modifié. \n");
                    
                    break;
                }
                    
            case '5':
                
                printf("Choisir les deux matrices a afficher: \n");
                for (j=0; j<i; j++) {
                    printf("Matrice n°%d.\t", j+1);
                }
                
                d = getchar();
                k = getchar();
                
                if(d != '\n' && d != EOF) {
                    int e;
                    while((e = getchar()) != '\n' && e != EOF);
                }
                
                addMat(matrice->tab_mat[d], matrice->tab_mat[k]);
                afficherMat(matrice->tab_mat[d]);
                
                break;
                
            case '6':
                
                printf("Choisir la matrice: \n");
                for (j=0; j<i; j++) {
                    printf("Matrice n°%d.\t", j+1);
                }
                
                d = getchar();
                
                if(d != '\n' && d != EOF) {
                    int e;
                    while((e = getchar()) != '\n' && e != EOF);
                }
                
                nombreOctetsGagnes(matrice->tab_mat[d]);
                
                break;
                
            case '7':
                fin = 1;
                break;
                
            default:
                printf("Choix erroné\n");
        }
    }
    
    return 0;
}


