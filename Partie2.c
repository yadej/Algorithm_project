#include "Partie2.h"
#include <stdio.h>
#include <stdlib.h>
//Partie ZeroEnDeuxiemePosition
bool ZeroEnDeuxiemePosition(Liste l){
    if(estVide(l))return FALSE;
    else{
        if( suite(l)!=NULL && premier(suite(l))==0)return TRUE;
        else return FALSE;
    }
}
//Partie QueDesZeros
bool QueDesZeros(Liste l){
    if(l == NULL)return TRUE;
    else {
        if(premier(l)!=0)return FALSE;
        else return QueDesZeros(suite(l));
    }
}
//Partie Compte0Initiaux
int Compte0InitiauxRec(Liste l){
    if( l == NULL || premier(l) != 0)return 0;
    else return 1 + Compte0InitiauxRec(suite(l));
}

int Compte0InitiauxIT(Liste l){
    Liste k = l;
    int Total = 0;
    while(k !=NULL && premier(k)==0){
        k = suite(k);
        Total++;
    }
    return Total;
}
//Predeclartion
int Compte0F(Liste l,int n);
void Compte0P(Liste l,int *n);
//Fin Predeclaration
int Compte0InitiauxSF(Liste l){
    return Compte0F(l,0);
}
int Compte0F(Liste l,int n){
    if(l == NULL || premier(l)!=0)return n;
    else return Compte0F(suite(l),n+1);
}
int Compte0InitiauxSP(Liste l){
    int n = 0;
    Compte0P(l,&n);
    return n;
}
void Compte0P(Liste l,int *n){
    if(l != NULL && premier(l)==0){
            *n +=1;
            Compte0P(suite(l),n);
    }
}
//Partie IntersectionTriee
Liste IntersectionTriee(Liste a,Liste b){
    if(a == NULL || b == NULL)return NULL;
    int n1 = premier(a);
    int n2 = premier(b);
    if(n1 == n2)return ajoute(n1,IntersectionTriee(suite(a),suite(b)));
    else if(n1 < n2)return IntersectionTriee(suite(a),b);
    else return IntersectionTriee(a,suite(b));
}

//Partie ElimineKpremiersX
void ElimineKpremiersX(Liste *L,int k,int X){
    if(*L != NULL){
        if(k ==0)return;
        if(X == premier(*L) ){
            depile(L);
            ElimineKpremiersX(L,k-1,X);
        }else{
            ElimineKpremiersX(&(**L).suivant,k,X);
        }
    }
}

//Partie ElimineKderniersX

void EKDX(Liste *a,int *k,int X);
void ElimineKderniersX(Liste *a,int k,int X){
    EKDX(a,&k,X);
}
void EKDX(Liste *L,int *k,int X){
    if(*L!=NULL) {
        EKDX(&(**L).suivant,k,X);
        if( *k>0 && X== premier(*L)){
            depile(L);
            *k-=1;
        }
    }
}
//Partie ListeDeListe Pour Permutation
typedef struct LL
{
    Liste liste;
    struct LL *suivant;
} LL;

typedef LL *ListeDeListe ;

Liste PListe(ListeDeListe L){
    return L->liste;
}
ListeDeListe suiteLDL(ListeDeListe L){
    return L->suivant;
}
ListeDeListe ajouteL(Liste x,ListeDeListe L){
    ListeDeListe tmp = (ListeDeListe) malloc(sizeof(LL)) ;
    tmp->liste = x ;
    tmp->suivant = L;
    return tmp ;
}
void initvoidLDL(ListeDeListe *LL){
    *LL = NULL;
}
void emplileL(Liste L, ListeDeListe *LL){
    *LL = ajouteL(L,*LL);
}
void affiche_LDL(ListeDeListe L){
    ListeDeListe p = L;
    printf("[");
    while(p != NULL){
        affiche_iter(p->liste);
        p = suiteLDL(p);
        printf(",");
    }

    printf("]\n");
}
void depileLDL(ListeDeListe *L){
    VideListe(&(**L).liste);
    ListeDeListe tmp = *L;
    *L = suiteLDL(*L) ;
    free(tmp);
}
void VideListeDeListe(ListeDeListe *L){
    if(*L != NULL){
        if((*L)->liste == NULL){
            ListeDeListe tmp = *L;
            *L = (*L)->suivant;
            free(tmp);
            VideListeDeListe(L);
        }
        depileLDL(L);
        VideListeDeListe(L);
    }
}
//Partie permutation
static int CompteurMalloc = 0;// Pour compter les mallocs
ListeDeListe Permutation(int n);
ListeDeListe ATPTL(int x, ListeDeListe LL);
ListeDeListe concatene(ListeDeListe a,ListeDeListe b);
ListeDeListe ATP(int x, Liste L);
ListeDeListe AETTL(int x, ListeDeListe LL);

ListeDeListe Permutation(int n){
    if(n==0){
        CompteurMalloc++;
        ListeDeListe tmp = (ListeDeListe) malloc(sizeof(LL)) ;
        tmp->liste = NULL;
        tmp->suivant = NULL;
        return tmp;
    }else{
        return ATPTL (n,Permutation(n-1));
    }
}
ListeDeListe ATPTL(int x, ListeDeListe LL){
    if(LL == NULL){
        return NULL;
    }
    else return concatene (ATP(x,PListe(LL)),ATPTL(x,suiteLDL(LL)));
}
ListeDeListe concatene(ListeDeListe a,ListeDeListe b){
    if(a == NULL)return b;
    else{
            CompteurMalloc++;
            return ajouteL(a->liste,concatene(suiteLDL(a),b));
    }
}
ListeDeListe ATP(int x, Liste L){
    if(L == NULL){
        CompteurMalloc++;
        ListeDeListe tmp = (ListeDeListe) malloc(sizeof(LL)) ;
        tmp->liste=ajoute(x,NULL);
        tmp->suivant = NULL;
        return tmp;
    }else{
        CompteurMalloc+= 2;
        return ajouteL(ajoute(x,L), AETTL(premier(L),ATP(x,suite(L))));
    }

}

ListeDeListe AETTL(int x, ListeDeListe LL){
    if(LL == NULL){
        return NULL;
    }else {
        CompteurMalloc+= 2;
        return ajouteL(ajoute(x,LL->liste),AETTL(x,LL->suivant));
    }
}
//Partie File

typedef Liste *File;

void initFile(File *F){
    *F = NULL;
}
File ajouteF(int x,File F){

    File tmp = (File)malloc(sizeof(Liste));
    if(!tmp)return NULL;
    (*tmp) = (Liste)malloc(sizeof(Bloc));
    (*tmp)->nombre = x;
    if(F == NULL){
        (*tmp)->suivant = *tmp;
        return tmp;
    }else{
        (*tmp)->suivant = (*F)->suivant;
        (**F).suivant = *tmp;
        return tmp;
    }
}
void ajouteFile(int x,File *F){

    *F = ajouteF(x,*F);

}
int enleveFile(File *F){
    if(*F == NULL)return -1;
    if((**F)->suivant == **F){
        int k = (**F)->nombre;
        depile(*F);
        *F = NULL;
        return k;
    }else{
        Liste tmp = (***F).suivant;
        int k = tmp->nombre;
        (**F)->suivant = tmp->suivant;
        depile(&tmp);
        return k;
    }
}
void afficheFile(File F){
    if(F == NULL){
            printf("[]\n");
            return;
    }
    Liste k = *F;
    k = k->suivant;

    printf("[");
    while(k != *F){
         printf("%d ", premier(k));
         k = k->suivant;
    }
    printf("%d ", premier(k));
    printf("]\n");
}
void depileFile(File *F){
    while(*F != NULL){
        enleveFile(F);
    }
}

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n",
                           longueur_rec(l),
                           longueur_iter(l)
               ) ;
}

int main(int argc, char** argv)
{

    Liste l ;
    Liste k ;
    Liste m ;
    Liste n ;

        initVide (&l) ;
        initVide (&k) ;
        initVide (&m) ;
        initVide (&n) ;

          poup(l) ;

             empile(4, &l) ;
        for(int i =2;i<9;i++){
            empile(i, &k) ;
            empile(11-i, &m) ;
            empile(9-i,&n) ;
        }
        printf("Liste m \n");
        poup(m);
        printf("Liste n \n");
        poup(n);
        printf("Liste l \n");
        poup(l);
        if(!ZeroEnDeuxiemePosition(l))printf("Pas de zero en deuxieme position Pour l \n");
        if(!QueDesZeros(k))printf("Autre que zero dans la liste \n");
         printf("Liste k \n");
          poup(k) ;
             empile(5, &l) ;
             empile(0, &l) ;
             empile(6, &l) ;
             empile(5, &l) ;
             empile(7, &l) ;
             empile(0, &l) ;
             empile(5, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;
          for(int i =2;i<9;i++){
            empile(0, &l) ;
        }
        printf("Liste l \n");
          poup(l) ;

          int A = Compte0InitiauxIT(l);
          int B = Compte0InitiauxRec(l);
          int C = Compte0InitiauxSF(l);
          int D = Compte0InitiauxSP(l);

          printf("Nbr de 0 initiaux %d Par Iterative \n",A);
          printf("Nbr de 0 initiaux %d Par Recursion \n",B);
          printf("Nbr de 0 initiaux %d Par Sous fonction \n",C);
          printf("Nbr de 0 initiaux %d Par Sous Procedure \n",D);
             ElimineKpremiersX(&l,3,5);
             ElimineKpremiersX(&l,2,4);
        printf("Liste l \n");
          poup(l) ;
             ElimineKpremiersX(&l,3,0);
             ElimineKderniersX(&l,3,0);
          printf("Liste l \n");
          poup(l) ;
             ElimineKderniersX(&l,3,9);
             ElimineKderniersX(&l,3,10);
          printf("Liste l \n");
          poup(l) ;
          printf("Intersection trie de la liste m et n\n");
          Liste j = IntersectionTriee(m,n);
          poup(j) ;
    VideListe(&l);
    VideListe(&k);
    VideListe(&m);
    VideListe(&n);
    VideListe(&j);
    ListeDeListe a = Permutation(3);
    printf("Nombre de Malloc %d \n",CompteurMalloc);
    //Il ya beacoup de malloc donc beaucoup despace memoire consomme alors que la liste n est pas tres grande
    //Pour reduire les malloc on pourrait faire des copie de liste + ajouter un element a la n ieme place
    affiche_LDL(a);
    //VideListeDeListe(&a); // pb de depile quand permutation est au dessus de 2
    File L1;
    initFile(&L1);
    printf("J initialise la File ");
    afficheFile(L1);
    for(int i = 1; i<8;i++){
        ajouteFile(i,&L1);
        printf("J empile %d  ",i);
        afficheFile(L1);
        //int to = sortir(0,&L1);
        //printf("%d  ",to);

    }
    for(int i =0;i<3; i++){
        int to = enleveFile(&L1);
        printf("Je depile %d ",to);
        afficheFile(L1);
    }
    printf("Je depile toute la File ");
    depileFile(&L1);
    afficheFile(L1);
    return 0;
}

