#include <stdlib.h>
#include "tp3.h"

 int get_int_len(int value)
    {
        int length=1;
            while(value>9){ length++; value/=10; }
            return length;
    }

element * newelement(element * suivant, int col,int valeur)
    {
        element *pointeur;
        pointeur=malloc(sizeof(element));
        if (pointeur == NULL )
                         {
                              fprintf(stderr,"Allocation impossible \n");
                              exit(EXIT_FAILURE);
                         }
        pointeur->colonne=col;
        pointeur->valeur=valeur;
        pointeur->suivant =suivant;
        return  pointeur;
    }

// Fonction pour saisir les éléments non-nuls d'une matrice creuse
int remplirMat(matrice_creuse *m, int N, int M) {
    
    int i, j;
    int first_elem; //first_elem sera un drapeau qui nous permettra de déterminer si le premier élément a été saisi ou non
    int saisie;
    int longestlength=1,digitlength=1;

    element *elem, *temp = NULL;
    
    m->tableauLignes = malloc(N*sizeof(liste_lignes)); //on alloue de la mémoire aux N lignes
    if ( m->tableauLignes == NULL )
    {
         fprintf(stderr,"Allocation impossible \n");
         exit(EXIT_FAILURE);
    }
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
                        printf("longest length = %d\n",longestlength);
                    }
             
                elem=newelement(NULL,j,saisie);//on alloue de la mémoire à l'élément qui est non nul
                 //on ne sait pas si notre élément sera le dernier élément de la liste donc on initialise toujours elem->suivant à NUL
                
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
            
             if ( (pt2 == NULL) )
                continue; // on n'a pas besoin de passer à la boucle sur les colonnes, 'continue' ici va passer à l'itération de ligne suivante
            else if (pt1 == NULL) {//si la ligne de m1 ne comporte que des 0
                m1.tableauLignes[i] = pt2;
                continue;
            }
            
            
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
                    
                    elem=newelement(pt1,pt1->colonne,pt1->valeur);
                     //on alloue de la mémoire à un nouveau élément dans m1
                    //on loue le nouvel élément à pt1 qui sera le suivant
                    
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

//Fonction pour afficher une valeur d'une ligne et colonne données
int getValue(matrice_creuse m, int i, int j) {
    
    element *elem = m.tableauLignes[i];
    
    if ( (elem == NULL) || ((elem->colonne < j) && (elem->suivant == NULL)) || (elem->colonne > j) ) //les cas pour lesquels l'élement que l'on veut retourner est égal à 0
        return 0;
    
    else {
        if (elem->colonne < j)
            while ( (elem->colonne < j) && (elem->suivant != NULL))
                elem = elem->suivant;
        if (elem->colonne == j)
            return elem->valeur;
        else
            return 0;
    }
}

//Fonction pour mettre à jour ou ajouter une valeur dans notre matrice
void putValue(matrice_creuse m, int i, int j, int val) {
    
    element *prec = NULL, *tmp = NULL, *elem = m.tableauLignes[i];
    
    if (elem == NULL) {
        tmp=newelement(NULL,j,val);
        m.tableauLignes[i] = tmp;
        
    }
    
    else {
        if (elem->colonne == j) //1er cas
            elem->valeur = val;
        
        else if (elem->colonne > j) { //2ème cas
            
            tmp=newelement(elem,j,val);
            
            m.tableauLignes[i] = tmp;
            
        }
        
        else if (elem->colonne < j) { //3ème cas
            
            while ((elem->colonne < j) && (elem->suivant != NULL)) {
                prec = elem;
                elem = elem->suivant;
            }
            if (elem->colonne > j) {
                tmp=newelement(elem,j,val);
                prec->suivant = tmp;
                
            }
            else if (elem->colonne == j)
                elem->valeur = val;
            else {
                tmp=newelement(NULL,j,val);
                
                elem->suivant = tmp;
                
            }
        }
    }
}

//Fonction pour déterminer le nb d'octets gagnés
int nombreOctetsGagnes(matrice_creuse m1)
{
    int i, j, somme_elem=m1.Nlignes, taille_elem, taille_matrice, nbOctetsGagnes, temp;
    
    for(i=0; i<m1.Nlignes; i++) {
        
        element *elem = m1.tableauLignes[i];
        
        if (elem == NULL) //si la ligne ne contient que des 0
            continue;
        somme_elem--;                           
        while(elem != NULL){                    
                somme_elem++;                   
                elem = elem->suivant;          
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

                if(m->tableauLignes[i]==NULL){                              
                        free(m->tableauLignes[i]);
                        printf("NULL colonne %d\n",j++);
                }
                else {
                        tmp=pointeur->suivant;
                        while (pointeur!=NULL){
                            pointeur=tmp->suivant;
                            free(tmp);
                            tmp=pointeur;
                            printf("%d\n",j++);
                        }
                            printf("Free colonne \n");
                            free(m->tableauLignes[i]);
                }
        }   


  }
