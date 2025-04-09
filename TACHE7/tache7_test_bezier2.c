#include "bezier.h"
#include "math.h"

double arrondir_4_decimales(double valeur) {
    return round(valeur * 10000.0) / 10000.0;
}

int main(int argc,char **argv){
    Liste_Point L=creer_liste_Point_vide();
    double abs;
    double ord;
    int n=0;
    printf("Quel cas voulez vous testez? (n=0 pour (l'exemple du cours) n=1 ou n >=2) : ");
    scanf("%d",&n);
    if(n==1){
        printf("abscisse du point P0 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point P0 : ");
        scanf("%lf",&ord);
        Point P0 = creer_point(abs,ord);
        printf("abscisse du point P1 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point P1 : ");
        scanf("%lf",&ord);
        Point P1 = creer_point(abs,ord);

        L=ajouter_element_liste_Point(L,P0);
        L=ajouter_element_liste_Point(L,P1);
        Tableau_Point tableau = sequence_points_liste_vers_tableau(L);
        Bezier2 b = approx_bezier2(tableau,0,1);
        Point C1_attendu;
        C1_attendu.abs=(P0.abs+P1.abs)/2;
        C1_attendu.ord=(P0.ord+P1.ord)/2;
        if(b.c0.abs==P0.abs &&b.c0.ord == P0.ord &&b.c1.abs==C1_attendu.abs && b.c1.ord==C1_attendu.ord && b.c2.abs==P1.abs && b.c2.ord==P1.ord){
            printf("Test OK \n");
        }
        else{
            printf("erreur dans approx_bezier 2 pour n=%d \n",n);
        }
    }
    else if(n>=2){
        printf("abscisse du point Q0 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point Q0 : ");
        scanf("%lf",&ord);
        Point Q0 = creer_point(abs,ord);
        printf("abscisse du point Q1 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point Q1 : ");
        scanf("%lf",&ord);
        Point Q1 = creer_point(abs,ord);
        printf("abscisse du point Q2 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point Q2 : ");
        scanf("%lf",&ord);
        Point Q2 = creer_point(abs,ord);
        Bezier2 b =creer_b2(Q0,Q1,Q2);
        for(int i = 0;i<=n;i++){
            Point Pi=calcul_ct_2((double)i/(double)n,b);
            L=ajouter_element_liste_Point(L,Pi);
        }
        Tableau_Point tableau = sequence_points_liste_vers_tableau(L);
        Bezier2 b_test=approx_bezier2(tableau,0,n);
        if(b_test.c0.abs == Q0.abs && b_test.c0.ord == Q0.ord && arrondir_4_decimales(b_test.c1.abs) ==Q1.abs 
        && arrondir_4_decimales(b_test.c1.ord)==Q1.ord && b_test.c2.abs==Q2.abs && b_test.c2.ord==Q2.ord){
            printf("Test OK pour n=2 \n");
        }
        else{
            printf("Point Q0 :%f %f  Point Q1 :%f %f Point Q2 :%f %f \n",Q0.abs,Q0.ord,Q1.abs,Q1.ord,Q2.abs,Q2.ord);
            printf("Point C0 :%f %f  Point C1 :%f %f Point C2 :%f %f \n",b_test.c0.abs,b_test.c0.ord,b_test.c1.abs,b_test.c1.ord,b_test.c2.abs,b_test.c2.ord);
            printf("Erreur approx bezier pour n=%d \n",n);
        }
    }
    else{
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
    Bezier2 b =approx_bezier2(tableau,0,8);
    printf("c0:%f %f \nc1:%f %f \nc2:%f %f \n ",b.c0.abs,b.c0.ord,b.c1.abs,b.c1.ord,b.c2.abs,b.c2.ord);
    }
}