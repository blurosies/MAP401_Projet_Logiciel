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
    printf("Quel cas voulez vous testez? (n=0 pour (l'exemple du cours) n=1 ou n =2 ou n>=3) : ");
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
        Bezier3 b = approx_bezier3(tableau,0,1);
        Point C1_attendu;
        C1_attendu.abs=(2*P0.abs+P1.abs)/3;
        C1_attendu.ord=(2*P0.ord+P1.ord)/3;
        Point C2_attendu;
        C2_attendu.abs=(P0.abs+2*P1.abs)/3;
        C2_attendu.ord=(P0.ord+2*P1.ord)/3;
        if(b.c0.abs==P0.abs &&b.c0.ord == P0.ord &&b.c1.abs==C1_attendu.abs && b.c1.ord==C1_attendu.ord && b.c2.abs==C2_attendu.abs && b.c2.ord==C2_attendu.ord && b.c3.abs==P1.abs && b.c3.ord==P1.ord){
            printf("Test OK \n");
        }
        else{
            printf("erreur dans approx_bezier 3 pour n=%d \n",n);
        }
    }
    else if(n==2){
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
        printf("abscisse du point P2 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point P2 : ");
        scanf("%lf",&ord);
        Point P2 = creer_point(abs,ord);

        L=ajouter_element_liste_Point(L,P0);
        L=ajouter_element_liste_Point(L,P1);
        L=ajouter_element_liste_Point(L,P2);
        Tableau_Point tableau = sequence_points_liste_vers_tableau(L);
        Bezier3 b = approx_bezier3(tableau,0,2);
        Point C1_attendu;
        C1_attendu.abs=(4*P1.abs-P2.abs)/3;
        C1_attendu.ord=(4*P1.ord-P2.ord)/3;
        Point C2_attendu;
        C2_attendu.abs=(4*P1.abs-P0.abs)/3;
        C2_attendu.ord=(4*P1.ord-P0.ord)/3;
        if(b.c0.abs==P0.abs &&b.c0.ord == P0.ord &&b.c1.abs==C1_attendu.abs && b.c1.ord==C1_attendu.ord && b.c2.abs==C2_attendu.abs && b.c2.ord==C2_attendu.ord && b.c3.abs==P2.abs && b.c3.ord==P2.ord){
            printf("Test OK pour n=2 \n");
        }
        else{
            printf("Point C0_attendu :%f %f  Point  C1_attendu :%f %f Point  C2_attendu:%f %f Point  C3_attendu %f %f\n",P0.abs,P0.ord,C1_attendu.abs,C1_attendu.ord,C2_attendu.abs,C2_attendu.ord,P2.abs,P2.ord);
            printf("Point C0 :%f %f  Point C1 :%f %f Point C2 :%f %f Point C3 %f %f \n",b.c0.abs,b.c0.ord,b.c1.abs,b.c1.ord,b.c2.abs,b.c2.ord,b.c3.abs,b.c3.ord);
            printf("erreur dans approx_bezier 3 pour n=%d \n",n);
        }

    }
    else if(n>=3){
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
        printf("abscisse du point Q3 : ");
        scanf("%lf",&abs);
        printf("ordonnée du point Q3 : ");
        scanf("%lf",&ord);
        Point Q3 = creer_point(abs,ord);
        Bezier3 b =creer_b3(Q0,Q1,Q2,Q3);
        for(int i = 0;i<=n;i++){
            Point Pi=calcul_ct_3((double)i/(double)n,b);
            L=ajouter_element_liste_Point(L,Pi);
        }
        Tableau_Point tableau = sequence_points_liste_vers_tableau(L);
        Bezier3 b_test=approx_bezier3(tableau,0,n);
        if(b_test.c0.abs == Q0.abs && b_test.c0.ord == Q0.ord && arrondir_4_decimales(b_test.c1.abs) ==Q1.abs 
        && arrondir_4_decimales(b_test.c1.ord)==Q1.ord && arrondir_4_decimales(b_test.c2.abs)==Q2.abs && arrondir_4_decimales(b_test.c2.ord)==Q2.ord && b_test.c3.abs==Q3.abs && b_test.c3.ord==Q3.ord){
            printf("Test OK pour n=3\n");
        }
        else{
            printf("Point Q0 :%f %f  Point Q1 :%f %f Point Q2 :%f %f  Point Q3 : %f %f\n",Q0.abs,Q0.ord,Q1.abs,Q1.ord,Q2.abs,Q2.ord,Q3.abs,Q3.ord);
            printf("Point C0 :%f %f  Point C1 :%f %f Point C2 :%f %f  Point C3 : %f %f\n",b_test.c0.abs,b_test.c0.ord,b_test.c1.abs,b_test.c1.ord,b_test.c2.abs,b_test.c2.ord,b_test.c3.abs,b_test.c3.ord);
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
    Bezier3 b =approx_bezier3(tableau,0,8);
    printf("c0:%f %f \nc1:%f %f \nc2:%f %f \nc3:%f %f \n ",b.c0.abs,b.c0.ord,b.c1.abs,b.c1.ord,b.c2.abs,b.c2.ord,b.c3.abs,b.c3.ord);
    }
}