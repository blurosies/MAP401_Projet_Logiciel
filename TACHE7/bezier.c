#include "TACHE1/image.h"
#include "liste_chainee.h"
#include "tache3.h"
#include <math.h>
#include "bezier.h" 
#include "sequence_segment.h"

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

Liste_Point simplification_douglas_peucker(Tableau_Point tab_contour,int indice_a,int indice_b,double d){

}

Bezier2 approx_bezier2 (Tableau_Point contour,int j1,int j2){
    
}

Bezier3 approx_bezier3 (Tableau_Point tab_contour,int indice_a,int indice_b){
    int n =indice_b-indice_a;
    if(n==1 || n==2){
        Bezier2 b2=approx_bezier2(tab_contour,indice_a,indice_b);
        Bezier3 b =conversion_degre_2_3(b2);
    }
    else if (n>=3){
        Point c0=tab_contour.tab[indice_a];
        Point c3=tab_contour.tab[indice_b];
        int alpha=(-15*pow(n,3)+5*pow(n,2)+2*n+4)/(3*(n+2)*(3*pow(n,2)+1));
        int beta=(10*pow(n,3)-15*pow(n,2)+n+2)/3*(n+2)*(3*pow(n,2)+1);
    }
    }


int main(int argc,char **argv){
    if(argc!=5){
        printf("Format du programme ./tache3 <nom fichier> <type de fichier (pbm/contours) distance seuil mode de remplissage(fill/stroke) \n");
        return 1;
        }
        Liste_Contour L;
        Image I;
        double d = atof(argv[3]);
        I=lire_fichier_image(argv[1]);
        L=contour_complet(I);
        free(I.pointeur_vers_le_tableau_de_pixels);
        Cellule_Liste_Contour *current_contour =L.first;
        int nb_segments=0;
        for(int i=0;i<L.taille;i++){
            Liste_Point ancient_contour=current_contour->contour;
            Tableau_Point tab_contour = sequence_points_liste_vers_tableau(current_contour->contour);
            current_contour->contour=simplification_douglas_peucker(tab_contour,0,current_contour->contour.taille-1,d);
            supprimer_liste_Point(ancient_contour);
            free(tab_contour.tab);
            nb_segments+=current_contour->contour.taille;
            current_contour=current_contour->suiv;
        }
        nb_segments=nb_segments/2;
        printf("Il y a un total de %d segments après simplifcation avec d=%f\n",nb_segments,d);
        tracer_EPS_contour_multiple(argv[4],I,L,argv[1]);
        supprimer_liste_contour(L);
}