#include "tache6.c"
#include "TACHE3/tache3.h"
#include "sequence_segment.h"
int main (int argc,char **argv ){
    if(argc!=6){
    printf("Format du programme ./tache3 <dossie de sortie> <nom fichier> <type de fichier (pbm/contours) distance seuil mode de remplissage(fill/stroke) \n");
    return 1;
    }
    Liste_Contour L;
    Image I;
    double d = atof(argv[4]);
    I=lire_fichier_image(argv[2]);
    L=contour_complet(I,true);
    free(I.pointeur_vers_le_tableau_de_pixels);
    Cellule_Liste_Contour *current_contour =L.first;
    int nb_segments=0;
    for(int i=0;i<L.taille;i++){
        Liste_Point ancient_contour=current_contour->contour;
        Tableau_Point tab_contour = sequence_points_liste_vers_tableau(current_contour->contour);
        current_contour->contour=simplifie_contour(tab_contour,0,current_contour->contour.taille-1,d);
        supprimer_liste_Point(ancient_contour);
        free(tab_contour.tab);
        nb_segments+=current_contour->contour.taille;
        current_contour=current_contour->suiv;
    }
    nb_segments=nb_segments/2;
    printf("Il y a un total de %d segments après simplifcation avec d=%f\n",nb_segments,d);
    tracer_EPS_contour_multiple(argv[5],I,L,argv[1],argv[2],true);
    supprimer_liste_contour(L);
}