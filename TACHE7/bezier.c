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
        
    }
}


Point calcul_ct_3 (int t , Bezier3 b );