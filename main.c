#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main() {
    
    int fin;
    int longestnomat1,longestnomat2,digitlength;
    matrice_creuse m1, m2;
    
    int i = 0; //drapeau qui permettra de déterminer si une matrice ou deux matrices ont été enregistré
    fin = 0; //drapeau qui permettra de déterminer la fin de notre programme
    

    while(!fin) {
        
        int c=0, a;
        int N, M, val;
        
        /* affichage menu */
        printf("\nMenu:\n\n"
               "1. Remplir une matrice creuse\n"
               "2. Afficher une matrice creuse\n"
               "3. Donner la valeur d'un élément d'une matrice creuse\n"
               "4. Affecter une valeur à un élément d'une matrice creuse\n"
               "5. Additionner deux matrices creuses\n"
               "6. Calculer le gain en espace en utilisant cette représentation pour une matrice donnée\n"
               "7. Quitter\n"
               "\nVotre choix: "
               );
        
        scanf("%d",&c);
        
        switch(c) {
                
            case 1:
                
                if (i > 1) {
                    printf("Deux matrices ont déjà été enregistrées. \n");
                    break;
                }
                else {
                    printf("Nb de lignes de la matrice: ");
                    scanf("%d", &N);
                    
                    printf("Nb de colonnes de la matrice: ");
                    scanf("%d", &M);
                    
                    if (i == 0) {
                       
                        longestnomat1=remplirMat(&m1, N, M); 
                        i = 1;
                    }
                    else if (i == 1) {
                        longestnomat2=remplirMat(&m2, N, M); 
                        i += 1;
                    }
            
                    printf("La matrice a bien été créee.\n");
                    break;
                }
                
            case 2:
                
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                
                else {
                    printf("Choisir la matrice a afficher: \n 1: Matrice N°1\n 2: Matrice N°2\n "
                           "Votre choix: ");
                    scanf("%d", &a);
                    
                    if ((a == 1) && (i>0))
                        afficherMat(m1,longestnomat1);
                    else if ((a == 2) && (i>1))
                        afficherMat(m2,longestnomat2);
                    else
                        printf("Mauvaise saisie\n");
                    
                    break;
                }
                
            case 3:
                
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                else {
                    
                    printf("Choisir la matrice: \n 1: Matrice N°1\n 2: Matrice N°2\n "
                           "Votre choix: ");
                    scanf("%d", &a);
                    
                    if ((a > 2) || (a < 0)) {
                        printf("Mauvaise saisie");
                        break;
                    }
                    else {
                        printf("Numéro de la ligne de l'élément a afficher: ");
                        scanf("%d", &N);
                        
                        printf("Numéro de la colonne de l'élément a afficher: ");
                        scanf("%d", &M);
                        
                        if (a == 1)
                            printf("%d\n",getValue(m1, N, M));
                        else if (a == 2)
                            printf("%d\n",getValue(m2, N, M));
                        break;
                    }
                }
                
            case 4:
                    
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                else {
                    
                    printf("Choisir la matrice: \n 1. Matrice N°1\n 2. Matrice N°2\n "
                           "Votre choix: ");
                    scanf("%d", &a);
                    
                    if ( (a<0) || (a>2) ) {
                        printf("Mauvaise saisie\n");
                        break;
                    }
                    
                    else {
                        printf("Numéro de la ligne de l'élément a modifier: ");
                        scanf("%d", &N);
                        
                        printf("Numéro de la colonne de l'élément a modifier: ");
                        scanf("%d", &M);
                        
                        printf("Valeur de l'élément a affecter: ");
                        scanf("%d", &val);
                        
                        if (a == 1) {
                            putValue(m1, N, M, val);
                            digitlength=get_int_len(val);        
                            if ( digitlength > longestnomat1)    
                                longestnomat1=digitlength;  
                            
                            printf("L'élément a bien été modifié. \n");
                        }
                        else if (a == 2) {
                            putValue(m2, N, M, val);
                            digitlength=get_int_len(val); 
                            if ( digitlength > longestnomat2)    
                                longestnomat2=digitlength;
                            printf("L'élément a bien été modifié. \n");
                        }
                        
                        break;
                    }
                }
                    
            case 5:
                
                 if(longestnomat2>longestnomat1){      
                    longestnomat1=longestnomat2+1;    
                }
                addMat(m1, m2);                      
                afficherMat(m1,longestnomat1);
    
                break;
                
            case 6:
                
                if (i == 0) {
                    printf("Il n'y'a aucune matrice stockée");
                    break;
                }
                else {
                    printf("Choisir la matrice: \n 1. Matrice N°1\n 2. Matrice N°2\n "
                           "Votre choix: ");
                    scanf("%d", &a);
                    
                    if ( (a<0) || (a>2) ) {
                        printf("Mauvaise saisie\n");
                        break;
                    }
                    
                    else {
                        
                        if (a == 1) {
                            printf("Le nombre d'octets gagnés pour la matrice : %d\n",nombreOctetsGagnes(m1));
                        }
                        else if (a == 2) {
                            printf("Le nombre d'octets gagnés pour la matrice : %d\n",nombreOctetsGagnes(m2));
                        }
                        
                        break;
                    }
                }

            case 7:
                fin = 1;
                break;
                
            default:
                printf("Choix erroné\n");
        }
    }
     if (i > 0) 
                freeMat(&m1);        
     if (i >1)     
                freeMat(&m2);        

    return 0;
}

