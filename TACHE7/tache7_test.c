#include "bezier.h"

int main(int argc,char **argv){
    Liste_Point L=creer_liste_Point_vide();
    Point p1={0,0};
    Point p2={1,0};
    Point p3={1,1};
    Point p4={1,2};
    Point p5={2,2};
    Point p6={3,2};
    Point p7={3,3};
    Point p8={4,3};
    Point p9={5,3};
    L=ajouter_element_liste_Point(L,p1);
    L=ajouter_element_liste_Point(L,p2);
    L=ajouter_element_liste_Point(L,p3);
    L=ajouter_element_liste_Point(L,p4);
    L=ajouter_element_liste_Point(L,p5);
    L=ajouter_element_liste_Point(L,p6);
    L=ajouter_element_liste_Point(L,p7);
    L=ajouter_element_liste_Point(L,p8);
    L=ajouter_element_liste_Point(L,p9);
    Tableau_Point tableau = sequence_points_liste_vers_tableau(L);
    Bezier3 b =approx_bezier3(tableau,0,8);
    printf("c0:%f %f c1:%f %f c2:%f %f c3:%f %f",b.c0.abs,b.c0.ord,b.c1.abs,b.c1.ord,b.c2.abs,b.c2.ord,b.c3.abs,b.c3.ord);
}