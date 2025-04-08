#include "bezier.h"

int main(int argc,char **argv){
    // Liste_Point L=creer_liste_Point_vide();
    // Point p1={0,0};
    // Point p2={1,0};
    // Point p3={1,1};
    // Point p4={1,2};
    // Point p5={2,2};
    // Point p6={3,2};
    // Point p7={3,3};
    // Point p8={4,3};
    // Point p9={5,3};
    // L=ajouter_element_liste_Point(L,p1);
    // L=ajouter_element_liste_Point(L,p2);
    // L=ajouter_element_liste_Point(L,p3);
    // L=ajouter_element_liste_Point(L,p4);
    // L=ajouter_element_liste_Point(L,p5);
    // L=ajouter_element_liste_Point(L,p6);
    // L=ajouter_element_liste_Point(L,p7);
    // L=ajouter_element_liste_Point(L,p8);
    // L=ajouter_element_liste_Point(L,p9);
    // Tableau_Point tableau = sequence_points_liste_vers_tableau(L);
    // Bezier3 b =approx_bezier3(tableau,0,8);
    // printf("c0:%f %f c1:%f %f c2:%f %f c3:%f %f",b.c0.abs,b.c0.ord,b.c1.abs,b.c1.ord,b.c2.abs,b.c2.ord,b.c3.abs,b.c3.ord);
    // simplification_douglas_peucker_3(tableau,0,8,1);
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
            current_contour->contour=simplification_douglas_peucker_3(tab_contour,0,current_contour->contour.taille-1,d);
            supprimer_liste_Point(ancient_contour);
            free(tab_contour.tab);
            nb_segments+=current_contour->contour.taille;
            current_contour=current_contour->suiv;
        }
        nb_segments=nb_segments/4;
        printf("Il y a un total de %d courbes après simplifcation avec d=%f\n",nb_segments,d);
        affiche_liste_Contour(L);
        tracer_EPS_contour_multiple_bezier3(argv[4],I,L,argv[1]);
        supprimer_liste_contour(L);

}