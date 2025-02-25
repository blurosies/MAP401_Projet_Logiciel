#include <stdio.h>
#include "TACHE2/geometrie2d.h"
#include "TACHE3/tache3.h"
#include "TACHE3/liste_chainee.h"
#include "TACHE1/image.h"
#include "sequence_segment.h"

void simplifie_contour(Liste_Point list,double distance){
    Tableau_Point tab_contour = sequence_points_liste_vers_tableau(list);
    Segment seg = creer_segment(tab_contour.tab[0],tab_contour.tab[tab_contour.taille -1]);
    double dmax = 0;
    Point k = tab_contour.tab[0];
    for()


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
    Point current_point;
    for(int i=0;i<L.taille;i++){
        simplifie_contour(L.first->contour,d);
        L.first=L.first->suiv;
    }

}