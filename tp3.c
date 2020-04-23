#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

 int get_int_len(int value)
    {
        int length=1;
            while(value>9){ length++; value/=10; }
            return length;
    }

// Fonction pour saisir les éléments non-nuls d'une matrice creuse
int remplirMat(matrice_creuse *m, int N, int M) {
    
    int i, j;
    int first_elem; //first_elem sera un drapeau qui nous permettra de déterminer si le premier élément a été saisi ou non
    int saisie;
    int longestlength=1,digitlength=1;

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
                
                digitlength=get_int_len(saisie);
                    if (digitlength > longestlength)
                    {
                        longestlength=digitlength;
                    }
                
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
    return(longestlength);
}
void PrintBorder(int j,int longestlength)  //affiche border du matrice
{
int i,k;

                for (k=0; k <j; k++)
                {
                printf("|--");
                    for (i=0; i<longestlength; i++)
                    {
                         printf("-");
                    }
                }
                printf("|\n");
}

void PrintRow(int num_espaces,int valeur)  //affiche border du matrice
{
int k,split_espaces;
                    
                    split_espaces=num_espaces/2;
                    for ( k = 0; k<split_espaces; k++){
                        printf(" ");
                    }

                    printf("%d",valeur);             
                    
                    for ( k = split_espaces; k<= num_espaces; k++){
                        printf(" ");
                    }
}





// Fonction pour afficher une matrice creuse
void afficherMat(matrice_creuse m, int longest_chiffre) {

    int i,j;
    
    for (i=0; i<m.Nlignes; i++) {
        
        element *pointeur = m.tableauLignes[i]; //pour chaque ligne on assigne un pointeur de type élément 
        PrintBorder(m.Ncolonnes,longest_chiffre);
        for (j=0; j<m.Ncolonnes; j++ ) {
            printf("| ");
            if ((pointeur != NULL ) && (pointeur->colonne == j)) { //si la ligne n'est pas vide et que le pointeur est à la bonne colonne
                
                PrintRow((longest_chiffre-get_int_len(pointeur->valeur)),pointeur->valeur);
                pointeur = pointeur->suivant; //on passe à l'élément suivant
            }
            else //si le pointeur n'est pas à la bonne position ou si il est NULL alors l'élément est égal à 0
                                    PrintRow((longest_chiffre-1),0);

        }
        
        printf("|\n");
    }
        PrintBorder(m.Ncolonnes,longest_chiffre);

}

void addMat(matrice_creuse m1, matrice_creuse m2) {
    
    int i,j;
    element *elem, *prec = NULL;
    
    if ((m1.Nlignes != m2.Nlignes) || (m1.Ncolonnes != m2.Ncolonnes))
        printf("Erreur: les deux matrices doivent être de mêmes dimensions");
    else{
        
        for (i=0; i<m1.Nlignes; i++) {
            
            element *pt1 = m1.tableauLignes[i];
            element *pt2 = m2.tableauLignes[i];
            
            if ( ((pt1 == NULL) && (pt2 == NULL)) || (pt2 == NULL) ) //si les 2 lignes ne comportent que des 0 ou si la ligne de m2 ne comporte que des 0
                continue; // on n'a pas besoin de passer à la boucle sur les colonnes, 'continue' ici va passer à l'itération de ligne suivante
            else if (pt1 == NULL)//si la ligne de m1 ne comporte que des 0
                pt1 = pt2;
            
            for (j=0; j<m1.Nlignes; j++) {
                
                if (pt2 == NULL) //si l'élément de la 2ème matrice est NULL alors on sort de cette boucle car il n'y'a plus d'élément dans m2
                    break;

                else if (pt1 == NULL) {
                    prec->suivant = pt2;
                    break;
                }
                
                
                if (pt1->colonne == pt2->colonne) { // 1er cas
                    pt1->valeur += pt2->valeur;
                    prec = pt1;
                    pt1 = pt1->suivant;
                    pt2= pt2->suivant;
                }
                
                else if (pt1->colonne < pt2->colonne) { //2ème cas
                    prec = pt1;
                    pt1 = pt1->suivant;
                    
                } else if (pt2->colonne < pt1->colonne) { //3ème cas
                    elem=malloc(sizeof(element)); //on alloue de la mémoire à un nouveau élément dans m1
                    elem->valeur = pt2->valeur;
                    elem->colonne = pt2->colonne;
                    elem->suivant = pt1; //on loue le nouvel élément à pt1 qui sera le suivant
                    
                    if (pt1 == m1.tableauLignes[i]) //si c'est notre premier élément dans m1
                        m1.tableauLignes[i]=elem; //notre nouvel élément devient le premier de la ligne
                    else
                        prec->suivant=elem; //on lie le nouvel élément au précedent
                    
                    prec = elem;
                    pt2 = pt2->suivant;
                }
                
            }
        }
    }
}

//Fonction pour mettre à jour ou ajouter une valeur dans notre matrice
void putValue(matrice_creuse m, int i, int j, int val) {
    
    element *prec = NULL, *tmp = NULL, *elem = m.tableauLignes[i];
    
    if (elem == NULL) {
        tmp = malloc(sizeof(element));
        m.tableauLignes[i] = tmp;
        tmp->suivant = NULL;
        tmp->valeur = val;
        tmp->colonne = j;
    }
    
    else {
        if (elem->colonne == j) //1er cas
            elem->valeur = val;
        
        else if (elem->colonne > j) { //2ème cas
            
            tmp = malloc(sizeof(element));
            m.tableauLignes[i] = tmp;
            tmp->suivant = elem;
            tmp->valeur = val;
            tmp->colonne = j;
        }
        
        else if (elem->colonne < j) { //3ème cas
            
            while ((elem->colonne < j) && (elem->suivant != NULL)) {
                prec = elem;
                elem = elem->suivant;
            }
            if (elem->colonne > j) {
                tmp = malloc(sizeof(element));
                prec->suivant = tmp;
                tmp->suivant = elem;
                tmp->valeur = val;
                tmp->colonne = j;
            }
            else if (elem->colonne == j)
                elem->valeur = val;
            else {
                tmp = malloc(sizeof(element));
                elem->suivant = tmp;
                tmp->suivant = NULL;
                tmp->valeur = val;
                tmp->colonne = j;
            }
        }
    }
}

//Fonction pour déterminer le nb d'octets gagnés
int nombreOctetsGagnes(matrice_creuse m1)
{
    int i, j, somme_elem=m1.Ncolonnes, taille_elem, taille_matrice, nbOctetsGagnes, temp;
    
    for(i=0; i<m1.Nlignes; i++) {
        
        element *elem = m1.tableauLignes[i];
        
        if (elem == NULL) //si la ligne ne contient que des 0
            continue;
      
        temp=0;
        for(j=0; j<m1.Ncolonnes; j++)
        {

            if ((elem != NULL) && (elem->colonne==j)) {
                somme_elem++;
                elem = elem->suivant;
                temp++;
            }
        }
        if(temp>1)
        {
         somme_elem--;
        }
         
       
        
    }
    
    taille_elem = somme_elem*sizeof(element);
    taille_matrice = m1.Nlignes*m1.Ncolonnes*sizeof(int);
    
    nbOctetsGagnes = taille_matrice-taille_elem;
    
    return nbOctetsGagnes;
    
}
void freeMat(matrice_creuse *m)

    {
    int i, j;
    element *pointeur,*tmp;


        for (i=0; i<m->Nlignes;i++){
                pointeur=m->tableauLignes[i];
                tmp=pointeur;
                
                while (pointeur!=NULL){
                            pointeur=tmp->suivant;
                            free(tmp);
                            tmp=pointeur;
                            printf("%d\n",j++);
                }
                            printf("\n");
        
        }   

   }
