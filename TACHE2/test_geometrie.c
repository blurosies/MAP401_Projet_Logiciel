#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geometrie2d.h"

int main(int argc , char*argv[]){
    Point a=creer_point(4,5);
    Point b= creer_point(2,4);
    Vecteur u= creer_vecteur(6,9);
    Vecteur v= creer_vecteur_bip(a,b);

    Point somme_p=somme_point(a,b);
    Vecteur somme_v=somme_vecteur(u,v);
    Point multipli_p=mult_reel_p(a,4);
    Vecteur multipli_v=mult_reel_v(u,4);


    printf("Point a: %f %f\n",a.abs , a.ord);
    printf("Point b: %f %f\n",b.abs,b.ord);
    printf("Vecteur u: %f %f\n",u.abs,u.ord);
    printf("Vecteur v: %f %f\n",v.abs,v.ord);
    printf("Somme de a et b: %f %f\n",somme_p.abs,somme_p.ord);
    printf("Somme de u et v: %f %f\n" ,somme_v.abs,somme_v.ord);
    printf("Multiplier a par 4: %f %f\n",multipli_p.abs,multipli_p.ord);
    printf("Multiplier u par 4: %f %f\n",multipli_v.abs,multipli_v.ord);
    printf("Produit scalaire de u et v: %f\n",produit_scalaire(u,v));
    printf("Norme de u: %f\n",norme_vect(u));
    printf("Distance entre a et b: %f\n",dist_points(a,b));

}