#include <stdio.h>
#include "TACHE2/geometrie2d.h"
#include "stdlib.h"

int main(int argc , char ** argv) {
    double abs ;
    double ord ;
    printf("abscisse du point P : ");
    scanf("%lf",&abs);
    printf("ordonnée du point P : ");
    scanf("%lf",&ord);
    Point P = creer_point(abs,ord);
    printf("abscisse du point A : ");
    scanf("%lf",&abs);
    printf("ordonnée du point A : ");
    scanf("%lf",&ord);
    Point A = creer_point(abs,ord);
    printf("abscisse du point B : ");
    scanf("%lf",&abs);
    printf("ordonnée du point B : ");
    scanf("%lf",&ord);
    Point B = creer_point(abs,ord);
    Segment seg_ab =creer_segment(A,B);
    double distance =distance_point_segment(P,seg_ab);
    printf("La distance entre le point P est le segment est de %f\n",distance);
}