#include "TACHE3/tache3.h"
#include "sequence_segment.h"



Liste_Point simplifie_contour(Liste_Point list,int indice_a,int indice_b,double d){
    Liste_Point l= creer_liste_Point_vide();
    Tableau_Point tab_contour = sequence_points_liste_vers_tableau(list);
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
        free(tab_contour.tab);

    }
    else{
        free(tab_contour.tab);
        Liste_Point l1 = simplifie_contour(list,indice_a,k,d);
        Liste_Point l2 = simplifie_contour(list,k,indice_b,d);
        l=concatener_liste_Point(l1,l2);
    }
    return l;


}

int main (int argc,char **argv ){
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
        current_contour->contour=simplifie_contour(current_contour->contour,0,current_contour->contour.taille-1,d);
        supprimer_liste_Point(ancient_contour);
        nb_segments+=current_contour->contour.taille;
        current_contour=current_contour->suiv;
    }
    nb_segments=nb_segments/2;
    printf("Il y a un total de %d segments après simplifcation avec d=%f\n",nb_segments,d);
    tracer_EPS_contour_multiple(argv[4],I,L,argv[1]);
    supprimer_liste_contour(L);
}