#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "geometrie2d.h"


Point creer_point(double abs , double ord){
    Point p={abs,ord}; 
    return p;
}


Vecteur creer_vecteur(double abs , double ord){
    Vecteur v={abs,ord}; 
    return v;
}

Vecteur creer_vecteur_bip(Point a , Point b){
    Vecteur v={b.abs-a.abs,b.ord-a.ord}; 
    return v;
}

Point somme_point(Point a, Point b){
    return creer_point(a.abs+b.abs , a.ord+b.ord);
}

Vecteur somme_vecteur(Vecteur u, Vecteur v){
    return creer_vecteur(u.abs+v.abs , u.ord+v.ord);
}

Point mult_reel_p(Point a, double d){
    return creer_point(d*a.abs,d*a.ord);
}

Vecteur mult_reel_v(Vecteur u, double d){
    return creer_vecteur(d*u.abs,d*u.ord);
}

double produit_scalaire(Vecteur u , Vecteur v){
    return u.abs*v.abs+u.ord*v.ord;
}

double norme_vect(Vecteur u){
    return sqrt((u.abs)*(u.abs)+(u.ord)*(u.ord));
}

double dist_points(Point a, Point b){
    return sqrt(pow(a.abs-b.abs,2)+pow(a.ord-b.ord,2));
}