#include "TACHE3/tache3.h"
#include "sequence_segment.h"



Liste_Point simplifie_contour(Liste_Point list,Point a,Point b,double d){
    Liste_Point l= creer_liste_Point_vide();
    Tableau_Point tab_contour = sequence_points_liste_vers_tableau(list);
    Segment seg = creer_segment(a,b);
    double dmax = 0;
    Point k = a;
    for(int i =0;i<tab_contour.taille;i++){
        double dj = distance_point_segment(k,seg);
        if(dmax<dj)
        {
            dmax = dj;
            k = tab_contour.tab[i+1];
        }
    }
    if(dmax<=d){
        l=tableau_vers_liste_points(tab_contour);

    }
    else{
        Liste_Point l1 = simplifie_contour(list,a,k,d);
        Liste_Point l2 = simplifie_contour(list,k,b,d);
        l=concatener_liste_Point(l1,l2);
    }
    return l;


}

int main (int argc,char **argv ){
    if(argc!=4){
    printf("Format du programme ./tache3 <nom fichier> <type de fichier (pbm/contours) distance seuil \n");
    return 1;
    }
    Liste_Contour L;
    Image I;
    double d = atof(argv[3]);
    I=lire_fichier_image(argv[1]);
    L=contour_complet(I);
    affiche_liste_Contour(L);
    for(int i=0;i<L.taille;i++){
        L.first->contour=simplifie_contour(L.first->contour,L.first->contour.first->point,L.first->contour.last->point,d);
        L.first=L.first->suiv;
    }
    affiche_liste_Contour(L);
}