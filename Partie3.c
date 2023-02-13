#include <stdio.h>
#include <stdlib.h> // Pour le rand()
#include<string.h> // Pour le strlen
#include <time.h> //Pour le time

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

typedef struct bloc_image{
    bool toutnoir ;
    struct bloc_image * fils[4] ;
} bloc_image ;
typedef bloc_image *image ;

//Partie Construit Blanc
image Construit_blanc(){
    return NULL;
}

//Partie Construit Noir
image Construit_noir(){
    image tmp = (image)malloc(sizeof(bloc_image));
    tmp->toutnoir = TRUE;
    tmp->fils[0] = NULL;
    tmp->fils[1] = NULL;
    tmp->fils[2] = NULL;
    tmp->fils[3] = NULL;
    return tmp;

}

//Partie ConstruitCompose
image Construit_composee(image ihg,image ihd,image ibg,image ibd){
    image tmp = (image)malloc(sizeof(bloc_image));
    tmp->toutnoir = FALSE;
    tmp->fils[0] = ihg;
    tmp->fils[1] = ihd;
    tmp->fils[2] = ibg;
    tmp->fils[3] = ibd;
    return tmp;
}

// Partie AffichageSimple
void affichageSimple(image k){
    if(k == NULL){
        printf("B");
    }else if(k->toutnoir){
        printf("N");
    }else{
        printf("+");
        affichageSimple(k->fils[0]);
        affichageSimple(k->fils[1]);
        affichageSimple(k->fils[2]);
        affichageSimple(k->fils[3]);
    }
}
//Partie Affichage Profondeur
void SubaffichageProfondeur(image k,int p){
    if(k == NULL){
        printf("B%d ",p);
    }else if(k->toutnoir){
        printf("N%d ",p);
    }else{
        printf("+%d ",p);
        SubaffichageProfondeur(k->fils[0],p+1);
        SubaffichageProfondeur(k->fils[1],p+1);
        SubaffichageProfondeur(k->fils[2],p+1);
        SubaffichageProfondeur(k->fils[3],p+1);
    }
}
void affichageProfondeur(image k){
    SubaffichageProfondeur(k,0);
}
//Partie EstNoire
bool EstNoire(image k){
    if( k == NULL ) return FALSE;
    else if( k->toutnoir ) return TRUE;
    else{
        return EstNoire (k->fils[0] ) && EstNoire( k->fils[1] ) && EstNoire( k->fils[2] ) && EstNoire( k->fils[3] );;
    }
}

//Partie EstBlanc
bool EstBlanc(image k){
    if( k == NULL ){
            return TRUE;
    }else if( k->toutnoir ){
            return FALSE;
    }else{
        return EstBlanc( k->fils[0] ) && EstBlanc( k->fils[1] ) && EstBlanc( k->fils[2] ) && EstBlanc( k->fils[3] );;
    }
}

//Partie copie
image copie(image k){
    if(k == NULL){
        return NULL;
    }else{
        image tmp = (image)malloc(sizeof(bloc_image));
        tmp->toutnoir = k->toutnoir;
        tmp->fils[0] = copie(k->fils[0]);
        tmp->fils[1] = copie(k->fils[1]);
        tmp->fils[2] = copie(k->fils[2]);
        tmp->fils[3] = copie(k->fils[3]);
        return tmp;
    }
}

//Partie aire

float aire(image k){
    if(k == NULL) return 0;
    else if(k->toutnoir) return 1;
    else{
        return ( aire(k->fils[0]) + aire(k->fils[1]) + aire(k->fils[2]) + aire(k->fils[3]))/4;
    }
}

//Partie Rendmemoire
void Rendmemoire(image *k){
    if( *k == NULL) return;
    else{
        if( (*k)->fils[0] != NULL) Rendmemoire(&(**k).fils[0]);
        if( (*k)->fils[1] != NULL) Rendmemoire(&(**k).fils[1]);
        if( (*k)->fils[2] != NULL) Rendmemoire(&(**k).fils[2]);
        if( (*k)->fils[3] != NULL) Rendmemoire(&(**k).fils[3]);
        free(*k);
    }
}

//Partie Lecture
image SousLecture(char a[], int *k){
    while( strlen(a) > *k ){
        if(a[*k]=='+'){
            (*k) = *k + 1;
            image ihg = SousLecture(a,k);
            image ihd = SousLecture(a,k);
            image ibg = SousLecture(a,k);
            image ibd = SousLecture(a,k);
             return Construit_composee(
                                       ihg,
                                       ihd,
                                       ibg,
                                       ibd
                                       );
        }else if(a[*k]=='B'){
            *k = *k + 1;
             return Construit_blanc();
        }else if(a[*k]=='N'){
            *k = *k + 1;
             return Construit_noir();
        }else{
            *k = *k + 1;
        }
    }
    //Si il n y a pas assez de char je suppose que cela retourne que des blanc
    return Construit_blanc();
}
image Lecture(){
    char b[1000];
    printf("\nEntrer une image = ");
    scanf("%s", b);
    int n = 0;
    return SousLecture(b,&n);
}

//Partie CompteSousImagesGrises
void SousA(image k, int *n,float *a);
int CompteSousImagesGrises(image k){
    int n = 0;
    float a= 0;
    SousA(k,&n,&a);
    return n;
}
void SousA(image k, int *n,float *a){
    if(k == NULL){
        *n = 0;
        *a = 0;
    }else if(k->toutnoir){
        *n = 0;
        *a = 1;
    }else{
        float e,b,c,d = 0;
        int c1,c2,c3,c4 = 0;
        SousA(k->fils[0],&c1,&e);
        SousA(k->fils[1],&c2,&b);
        SousA(k->fils[2],&c3,&c);
        SousA(k->fils[3],&c4,&d);
        *a = ( e + b + c + d )/4;
        *n = c1 + c2 + c3 + c4;
        if(*a  > (1.0f/3.0f) && *a < (2.0f/3.0f)){
            *n = *n + 1;
        }
    }
}


//Partie Negatif
void Negatif(image *k){
    if( *k == NULL ) *k = Construit_noir();
    else if( (*k)->toutnoir ){
            Rendmemoire(k);
            *k = Construit_blanc();
    }else {
            Negatif( &(*k)->fils[0] );
            Negatif( &(*k)->fils[1] );
            Negatif( &(*k)->fils[2] );
            Negatif( &(*k)->fils[3] );
    }
}

//Partie UnionNoire
bool UnionNoire(image a,image b){
    if(a == NULL){
        if(b == NULL){
            return FALSE;
        }else{
            return EstNoire(b);
        }
    }else{
        if(b == NULL){
                return EstNoire(a);
        }else{
            return EstNoire(a) || EstNoire(b) ||(UnionNoire(a->fils[0],b->fils[0]) && UnionNoire(a->fils[1],b->fils[1]) && UnionNoire(a->fils[2],b->fils[2]) && UnionNoire(a->fils[3],b->fils[3]));
        }
    }
}

//Partie Intersection
void Intersection(image *a,image b){
    if(*a==NULL) return;
    else{
        if(b == NULL){
            Rendmemoire(a);
            *a = NULL;
        }else{
            if((*a)->toutnoir){
                Rendmemoire(a);
                *a = copie(b);
            }else if(!b->toutnoir){
                Intersection(&(*a)->fils[0],b->fils[0]);
                Intersection(&(*a)->fils[1],b->fils[1]);
                Intersection(&(*a)->fils[2],b->fils[2]);
                Intersection(&(*a)->fils[3],b->fils[3]);
                if( (*a)->fils[0]== NULL && (*a)->fils[1]== NULL && (*a)->fils[2]== NULL && (*a)->fils[3]== NULL && !(*a)->toutnoir ){
                    Rendmemoire(a);
                    *a = NULL;
                }
            }
        }
    }
}

// Partie Affichage 2k pixels
 int power(int x,unsigned int n){
    int p = 1;
    for(int i =0;i<n;i++){
        p = p * x;
    }
    return p;
}
void SubAffPixel(image a, int profondeur,int pos ,int nb,int k);
void Affichage2Pixel(image a, int profondeur){
    int n = 0;
    int nb = power(2,profondeur);
    int k = power(4,profondeur);
    while( n < k ){
        SubAffPixel(a , profondeur, n , nb , k/2);
        n++;
        if( n % nb == 0 )printf("\n");
    }

}
void SubAffPixel(image a, int profondeur,int pos ,int nb,int k){
    if( profondeur == 0 ){
        if( EstBlanc(a) ){
                printf(".");
        }
        else if( EstNoire(a) ){
                printf("8");
        }
        else{
                printf("-");
        }
    }else{
        if( a == NULL ){
            printf(".");

        }else if( a->toutnoir ){
            printf("8");
        }else{
            int newI;
            if( pos < k ){
                if( pos% nb < nb/2 ){
                    newI = 0;
                }else{
                    newI = 1;

                    pos = pos - nb/2;
                }
            }else{
                if( pos%nb < nb/2 ){
                    newI = 2;
                    pos = pos - k;
                }else{
                    newI = 3;
                    pos = pos - k - nb/2;
                }
            }
            //Calcul de la nouvelle position
            unsigned int newpos = (pos - (pos%nb))/ 2 + (pos%nb);
            SubAffPixel( a->fils[newI],profondeur-1,newpos,nb/2, k/4 );
        }
    }
}

// Partie Alea
void Test(int Ta[],int Tc[],int posT,int abs,int col,int *newpos,bool *B){
    int k = posT-1;
    while( k >= 0 ){
        if( Tc[k] > col ){
            k -= 1;
        }else if( Tc[k] == col ){
            if( Ta[k] > abs ){
                k -= 1;
            }else{
                break;
            }
        }else{
            break;
        }
    }
    *newpos = k+1;
    if(  Tc[k] == col && Ta[k] == abs ){
        *B = FALSE;
    }else{
        *B = TRUE;
    }
}
void bouge(int Ta[],int Tc[],int posT,int newpos,int abs,int col){
    while( posT>newpos ){
        Ta[posT] = Ta[posT-1];
        Tc[posT] = Tc[posT-1];
        posT--;
    }
    Ta[newpos] = abs;
    Tc[newpos] = col;
}
void Noirci(image *F,int profondeur,int abs,int col,int mid){
        if( profondeur ==0 ){
            *F = Construit_noir();
        }else{
            int newI;
            if( abs < mid ){
                if(col < mid){
                    newI = 0;
                }else{
                    newI = 2;
                    col -= mid;
                }
            }else{
                if( col < mid ){
                    newI = 1;
                    abs -= mid;
                }else{
                    newI = 3;
                    abs -= mid;
                    col -= mid;
                }
            }
            if(*F == NULL){
            *F = (image)malloc(sizeof(bloc_image));
            (*F)->toutnoir = FALSE;
            (*F)->fils[0] = Construit_blanc();
            (*F)->fils[1] = Construit_blanc();
            (*F)->fils[2] = Construit_blanc();
            (*F)->fils[3] = Construit_blanc();
            }
            Noirci( &(*F)->fils[newI],profondeur-1,abs,col,mid/2 );
        }
}
image Alea(int k,int n){
    int p = power(2,k);
    if( k < 16 && n >= p * p ) return Construit_noir();
    bool TTNOIR = TRUE;
    if( k < 16 && n > p*p/2 ){
        TTNOIR = FALSE;
        n =  p*p -n ;
    }
    int Ta[n];
    int Tc[n];
    int abs,col;
    int newpos;
    bool diff;
    Ta[0] = rand() % p;
    Tc[0] = rand() % p;
    int pos = 1;
    while( pos < n ){
        abs = rand() % p;
        col = rand() % p;
        Test(Ta,Tc,pos,abs,col,&newpos,&diff);
        if( diff ){
            bouge(Ta,Tc,pos,newpos,abs,col);
            pos++;
        }
    }
    image B = Construit_blanc();
    if( TTNOIR ){
        for(int i = 0; i<n;i++){
            Noirci(&B,k,Ta[i],Tc[i],p/2);
        }
    }else{
        int i = 0;
        for(int c = 0; c < p;c++){
            for(int a = 0; a < p;a++){
                if( a == Ta[i] && c == Tc[i] ){
                    i++;
                }else{
                    Noirci(&B,k,a,c,p/2);
                }
            }
        }


    }
    return B;
}
int main(){
    srand( time( NULL ) );
    image Blanc = Construit_composee(Construit_blanc(),Construit_blanc(),Construit_blanc(),Construit_composee(Construit_blanc(),Construit_blanc(),Construit_blanc(),Construit_blanc()));
    image Noir = Construit_noir();
    if(EstBlanc(Blanc))printf("Blanc est blanc \n");
    if(EstNoire(Noir))printf("Noir est noire \n");
    image b = Construit_composee(Construit_blanc(),Construit_noir(),Construit_blanc(),Construit_noir());
    image c = copie(b);
    image d = Construit_composee(b,Construit_noir(),c,Construit_noir());
    image e = copie(d);
    Negatif(&e);
    int k = 0;
    int kk = 0;
    image u = SousLecture("+ B N + N +BNBB B +NBBB + N +BNBB B +NNBB",&k);
    image TestAire = SousLecture("+NBN+NBNB",&kk);
    if(UnionNoire(c,u))printf("Pourquoi Pas\n");
    affichageSimple(d);
    printf(" = d \n");
    affichageSimple(e);
    printf("  = negatif(d) \n");
    affichageSimple(u);
    printf(" = u \n");
    affichageProfondeur(d);
    printf(" = d \n");
    affichageProfondeur(e);
    printf(" = negatif(d)\n");
    affichageProfondeur(u);
    printf(" = u \n");
    float k1 = aire(d);
    float k2 = aire(e);
    float k3 = aire(u);
    float k4 = aire(TestAire);
    printf("aire d: %f\naire negatif(d): %f\naire u: %f \naire TestAire: %f \n",k1,k2,k3,k4);
    int SIG1 = CompteSousImagesGrises(d);
    int SIG2 = CompteSousImagesGrises(e);
    int SIG3 = CompteSousImagesGrises(u);
    printf("Nb de SousImageGrise d : %d\nNb de SousImageGrise negatif(d): %d\nNb de SousImageGrise u: %d \n",SIG1,SIG2,SIG3);
    int a1 = 0;
    int a2 = 0;
    int a3 = 0;
    int a4 = 0;
    image p1 = SousLecture("+ +NBNB +BNNB B +NNBB",&a1);
    image p2 = SousLecture("+ N +NBNNN +NBNB",&a2);
    image u1 = SousLecture("+ +NBNB +BNNB B +NNBB",&a3);
    image u2 = SousLecture("+ N +NBNN N +NBNB",&a4);
    affichageSimple(u1);
    printf("  = u1 \n");
    affichageSimple(u2);
    printf(" = u2\n");
    if(!UnionNoire(u1,u2))printf("u1 et u2 ne sont pas noire combine\n");
    affichageSimple(p1);
    printf(" = p1 \n");
    affichageSimple(p2);
    printf(" = p2 \n");
    int a5 = 0;
    image p3 = SousLecture(" + N +BBNB B +N+NNB+NBNN BN",&a5);
    affichageProfondeur(p3);
    printf(" = p3 \n");
    Affichage2Pixel(p3,3);
    Intersection(&p1,p2);
    affichageSimple(p1);
    printf(" = Inter(p1,p2)\n");
    affichageProfondeur(p1);
    printf("\n");
    Rendmemoire(&Blanc);
    Rendmemoire(&Noir);
    Rendmemoire(&d);
    Rendmemoire(&e);
    Rendmemoire(&u);
    Rendmemoire(&p1);
    Rendmemoire(&p2);
    Rendmemoire(&p3);
    Rendmemoire(&u1);
    Rendmemoire(&u2);
    image Alea1 = Alea(4,16);
    affichageSimple(Alea1);
    printf(" = Alea1 \n");
    Affichage2Pixel(Alea1,4);
    Rendmemoire(&Alea1);
    image g = Lecture();
    affichageSimple(g);
    printf("\n");
    Affichage2Pixel(g,3);
    Rendmemoire(&g);

    return 0;
}
