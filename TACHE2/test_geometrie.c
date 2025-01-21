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


    printf("%f %f\n",a.abs , a.ord);
    printf("%f %f\n",b.abs,b.ord);
    printf("%f %f\n",u.abs,u.ord);
    printf("%f %f\n",v.abs,v.ord);
    printf("%f %f\n",somme_p.abs,somme_p.ord);
    printf("%f %f\n" ,somme_v.abs,somme_v.ord);
    printf("%f %f\n",multipli_p.abs,multipli_p.ord);
    printf("%f %f\n",multipli_v.abs,multipli_v.ord);
    printf("%f\n",produit_scalaire(u,v));
    printf("%f\n",norme_vect(u));
    printf("%f\n",dist_points(a,b));



}