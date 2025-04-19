#include "TACHE3/tache3.h"
#include "sequence_segment.h"

Liste_Point simplifie_contour(Tableau_Point tab_contour,int indice_a,int indice_b,double d){
    Liste_Point l= creer_liste_Point_vide();
    Segment seg = creer_segment(tab_contour.tab[indice_a],tab_contour.tab[indice_b]);
    double dmax = 0;
    int k = indice_a;
    for(int j= indice_a +1;j<=indice_b;j++){
        double dj = distance_point_segment(tab_contour.tab[j],seg);
        if(dmax<dj)
        {
            dmax = dj;
            k =j;
        }
    }
    if(dmax<=d){
        l=ajouter_element_liste_Point(l,tab_contour.tab[indice_a]);
        l=ajouter_element_liste_Point(l,tab_contour.tab[indice_b]);

    }
    else{
        Liste_Point l1 = simplifie_contour(tab_contour,indice_a,k,d);
        Liste_Point l2 = simplifie_contour(tab_contour,k,indice_b,d);
        l=concatener_liste_Point(l1,l2);
    }
    return l;

}
