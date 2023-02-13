#include <stdio.h> // Pour le printf
#include <stdlib.h>
#include "time.h" // Pour le temps

//Exercice exponentielle
float exp1(int n){
    float a = 1;
    float total = 1.00;
    for(float i=1;i<n;i++){
        a = a*i;
        total = total + (1/a);
    }
    return total;
}
//Partie Puissance
//Puissance iterative en float
float puissanceIT(float x,int n){
    float total = 1;
    if(n<0){
        x= 1/x;
        n *=-1;
    }
    for(int i=0;i<n;i++){
        total = total * x;
    }
    return total;
}
//Puissance iterative en double
double puissanceITd(double x,int n){
    double total = 1;
    if(n<0){
        x= 1/x;
        n *=-1;
    }
    for(int i=0;i<n;i++){
        total = total * x;
    }
    return total;
}
//Puissance recursif
//j ai un out of memory si n trop grand
float puissanceRec(float x,int n){
    if(n<0)return puissanceRec(1/x,-n);
    else{
        if(n==0)return 1;
        else return x * puissanceRec(x,n-1);
    }
}
//Puissance en utilisant la parite
float puissance2(float x, int n){
    if(n<0)return puissance2(1/x,-n);
    if(n==0)return 1;
    float y = puissance2(x,n/2);
    if(n%2)return y*y*x;
    else return y*y;
}
//Autre fonction puissance
float puissance2IT(float x,int n){
    if(n<0){
        x = 1/x;
        n = -n;
    }
    float y = x;
    float total = 1.;
    while(n != 0){
        if(n%2==1)total = total * y;
        n =n / 2;
        y = y*y;
    }
    return total;
}
//Puissance en recursif terminal
float puiss(float x,int n,float r);
float puissanceRecTerm(float x,int n){
    if(n < 0)return puiss(1/x,-n,1);
    else return puiss(x,n,1);
}
float puiss(float x,int n,float r){
    if( n== 0)return r;
    else return puiss(x,n-1,x*r);
}
//Puissance en recursif terminal avec complexite logn
float puiss2(float x,int n,float r);
float puissanceRecTerm2(float x,int n){
    if(n < 0)return puiss2(1/x,-n,1);
    else return puiss2(x,n,1);
}
float puiss2(float x,int n,float r){
    if( n== 0)return r;
    else{
        if(n%2==0)return puiss(x*x,n/2,r);
        else return puiss(x*x,n/2,x*r);
    }
}
//Partie sur la fonction Ackermann
int AckermannRec(int M,int N) {
      if(M == 0) return N+1;
      else {
        if(N == 0) return AckermannRec(M-1,1);
        else return AckermannRec(M-1,(AckermannRec(M,N-1)));
      }
}
int Ackermann2(int m,int n){
    if(m==0)return n+1;
    else {
        int r = 1;
        for(int i=0;i<n+1;i++){
            r = Ackermann2(m-1,r);
        }
        return r;
    }
}
//Partie sur la fonction X
/*
Algorithme la fonction X
fontion X(int n): float
    x <- 1.
    Pour i de 0 a n-1 faire:
        x <- x + (1/x)
    rendre x
*/
float Xrec(int n){
    if(n == 0) return 1;
    else{
        float xn= Xrec(n-1);
        return xn + (1/xn);
    }
}
float Xit(int n){
    float x =1;
    for(int i=0;i<n;i++){
        x += (1/x);
    }
    return x;
}

int main()
{   float p1,p2;
    printf( "sizeof( double ) is: %lu octet\n", sizeof( double ));
    printf( "sizeof( long double ) is: %lu octet\n", sizeof(long double ));
    // j ai 8 octet pour les doubles et 16 pour les long doubles
    printf( "sizeof( float ) is: %lu octet\n", sizeof( float  ) );
    printf( "sizeof( long long ) is: %lu octet\n", sizeof( long long ) );
    // j ai 8 octet pour les long long et 4 pour les float et long
    //float p = exp1(15);
    for(int i=0;i<10;i++){
        float p = exp1(i);
        printf("exp1(%d) = %f   ",i,p);
    }
    printf("\n");
    for(int j=1;j<5;j++){
        float a = 1 + puissanceIT(10,-j);
        float b = puissanceIT(10,j);
        printf("a = %f et b = %f \n",a,b);
        p1 = puissanceIT(a,b);
        printf("PuissanceITfloat de a par b = %f \n",p1);
    }
    for(int j=1;j<5;j++){
        double a = 1 + puissanceITd(10,-j);
        double b = puissanceITd(10,j);
        printf("a = %f et b = %f \n",a,b);
        double p1d = puissanceITd(a,b);
        printf("PuissanceITdouble de a par b = %f \n",p1d);
    }
    for(int j=1;j<5;j++){
        float a = 1 + puissanceRec(10,-j);
        float b = puissanceRec(10,j);
        printf("a = %f et b = %f \n",a,b);
        p2 = puissanceRec(a,b);
        printf("PuissanceRec de a par b = %f \n",p2);
    }
    printf("difference entre Prec et Pit = %.10f\n", p2 - p1);
    //Pas de difference Pour moi entre l iterative et le recursif
    for(int j=1;j<5;j++){
        float a = 1 + puissance2(10,-j);
        float b = puissance2(10,j);
        printf("a = %f et b = %f \n",a,b);
        float p3 = puissance2(a,b);
        printf("Puissance2 de a par b = %f \n",p3);
    }
    for(int j=1;j<5;j++){
        float a = 1 + puissance2IT(10,-j);
        float b = puissance2IT(10,j);
        printf("a = %f et b = %f \n",a,b);
        float p4 = puissance2IT(a,b);
        printf("Puissance2IT de a par b = %f \n",p4);
    }

    for(int j=1;j<5;j++){
        float a = 1 + puissanceRecTerm(10,-j);
        float b = puissanceRecTerm(10,j);
        printf("a = %f et b = %f \n",a,b);
        float p5 = puissanceRecTerm(a,b);
        printf("puissanceRecTerm de a par b = %f \n",p5);
    }
    for(int j=1;j<5;j++){
        float a = 1 + puissanceRecTerm2(10,-j);
        float b = puissanceRecTerm2(10,j);
        printf("a = %f et b = %f \n",a,b);
        float p6 = puissanceRecTerm2(a,b);
        printf("puissanceRecTerm2 de a par b = %f \n",p6);
    }
    for(int i=0;i<5;i++){
        int Ack1 = AckermannRec(i,0);
        int Ack2 = Ackermann2(i,0);
        printf("Ackermann(%d,0) = %d\n",i,Ack1);
        printf("Ackermann2(%d,0) = %d\n",i,Ack2);
    }
    for(int k=100;k<101;k++){
        float Xn = Xrec(k);
        float Xk = Xit(k);
        printf("Xrec(%d) = %f\n",k,Xn);
        printf("Xit(%d) = %f\n",k,Xk);
    }

    return 0;
}
