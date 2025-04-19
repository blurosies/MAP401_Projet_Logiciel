#include "bezier.h"

int main(int argc,char **argv){
    if(argc!=7){
        printf("Format du programme ./tache7 <YOURPATHTO/DossierDeSortie> <nom fichier> <type de fichier (pbm/contours)> <type_bezier> <distance seuil> <mode de remplissage(fill/stroke)> \n");
        return 1;
        }
        Liste_Contour L;
        Image I;
        double d = atof(argv[5]);
        I=lire_fichier_image(argv[2]);
        L=contour_complet(I,true);
        free(I.pointeur_vers_le_tableau_de_pixels);
        Cellule_Liste_Contour *current_contour =L.first;
        int nb_segments=0;
        for(int i=0;i<L.taille;i++){
            Liste_Point ancient_contour=current_contour->contour;
            Tableau_Point tab_contour = sequence_points_liste_vers_tableau(current_contour->contour);
            if(atoi(argv[3])==2){
                current_contour->contour=simplification_douglas_peucker_2(tab_contour,0,current_contour->contour.taille-1,d);
                nb_segments+=(current_contour->contour.taille)/3;
                Liste_Point l_trace=creer_liste_Point_vide();
                Cellule_Liste_Point *current_cellule =current_contour->contour.first;
                for(int i=0;i<(current_contour->contour.taille)/3;i++){
                    Bezier2 b2 = creer_b2(current_cellule->point,current_cellule->suiv->point,current_cellule->suiv->suiv->point);
                    Bezier3 b3=conversion_degre_2_3(b2);
                    l_trace=ajoute_bezier3(b3,l_trace);
                    current_cellule=current_cellule->suiv->suiv->suiv;
                }
                current_contour->contour=l_trace;
            }
            else{
                current_contour->contour=simplification_douglas_peucker_3(tab_contour,0,current_contour->contour.taille-1,d);
                nb_segments+=(current_contour->contour.taille)/4;
            }
            supprimer_liste_Point(ancient_contour);
            free(tab_contour.tab);
            current_contour=current_contour->suiv;
        }
        printf("Il y a un total de %d courbes après simplifcation avec d=%f\n",nb_segments,d);
        tracer_EPS_contour_multiple_bezier3(argv[6],I,L,argv[1],argv[2],atoi(argv[3]));
        supprimer_liste_contour(L);
}