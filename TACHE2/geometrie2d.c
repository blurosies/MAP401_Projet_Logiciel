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
Segment creer_segment(Point a , Point b){
    Segment seg={a,b};
    return seg;
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

double distance_point_segment (Point p, Segment seg){
    double dist;
    Vecteur u=creer_vecteur_bip(seg.a, p);
    Vecteur w=creer_vecteur_bip(seg.b, p);
    Vecteur v=creer_vecteur_bip(seg.a, seg.b);
    if(seg.a.abs==seg.b.abs && seg.a.ord==seg.b.ord){ //cas A = B
        Vecteur u= creer_vecteur_bip(p , seg.b); // norme AP = norme BP
        dist=norme_vect(u);
    }
    else {
        double lambda;
        lambda=produit_scalaire(u,v)/produit_scalaire(v,v);
        if (lambda<0){
            dist=norme_vect(u);
        }else if( lambda>=0 && lambda<=1){
                Point Q= {seg.a.abs + lambda*(seg.b.abs-seg.a.abs), seg.a.ord + lambda*(seg.b.ord-seg.a.ord)};
                Vecteur q=creer_vecteur_bip(Q,p);
                dist=norme_vect(q);
        }else{
            dist=norme_vect(w);
        }
    }
    return dist;
}
