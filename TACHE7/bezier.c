#include "TACHE1/image.h"
#include "liste_chainee.h"
#include "tache3.h"
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "bezier.h" 

Bezier2 creer_b2(Point c0 , Point c1 , Point c2){
    Bezier2 B2 = {c0,c1,c2};
    return B2;
}

Bezier3 creer_b3(Point c0 , Point c1 , Point c2 , Point c3){
    Bezier3 B3 = {c0,c1,c2,c3};
    return B3;
}

Point calcul_ct_2 (int t , Bezier2 b ){
    if (t>1 || t<0){
        printf("t doit être entre 0 et 1 \n");
    }else{
        double abs= (b.c0.abs*(1-t)*(1-t)) + (b.c1.abs*2*t*(1-t)) + (b.c2.abs*t*t);
        double ord= (b.c0.ord*(1-t)*(1-t)) + (b.c1.ord*2*t*(1-t)) + (b.c2.ord*t*t);
        Point Ct=creer_point(abs,ord);
        return Ct;
    }
}


Point calcul_ct_3 (int t , Bezier3 b ){
    if (t>1 || t<0){
        printf("t doit être entre 0 et 1 \n");
    }else{
        double abs= (b.c0.abs*(1-t)*(1-t)*(1-t)) + (b.c1.abs*3*t*(1-t)*(1-t)) + (b.c2.abs*3*t*t*(1-t)) + (b.c3.abs*t*t*t);
        double ord= (b.c0.ord*(1-t)*(1-t)*(1-t)) + (b.c1.ord*3*t*(1-t)*(1-t)) + (b.c2.ord*3*t*t*(1-t)) + (b.c3.ord*t*t*t);
        Point Ct=creer_point(abs,ord);
        return Ct;
    }
}

Bezier3 conversion_degre_2_3 (Bezier2 b){
    double c1_abs=(b.c0.abs+2*b.c1.abs)/3;
    double c1_ord=(b.c0.ord+2*b.c1.ord)/3;
    double c2_abs=(b.c2.abs+2*b.c1.abs)/3;
    double c2_ord=(b.c2.ord+2*b.c1.ord)/3;

    Point c1=creer_point(c1_abs,c1_ord);
    Point c2=creer_point(c2_abs,c2_ord);

    Bezier3 c_converti=creer_b3(b.c0 , c1 , c2 , b.c2);
}

double distance_point_bezier2 (){}

double distance_point_bezier3 (){}

Bezier2 approx_bezier2 (Liste_Point contour){
    
}

Bezier2 approx_bezier3 (Liste_Point contour){}

