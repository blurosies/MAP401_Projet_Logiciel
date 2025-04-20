#include "TACHE3/tache3.h"
#include "TACHE6/tache6.h"
#include "TACHE7/bezier.h"

int main(int argc , char ** argv){
    if(argc<=1 || strcmp(argv[1],"-aide")==0){
        printf("Bienvenue dans le Projet De MAP401 \n\n"
            "Voici les listes des options à votre disposition ainsi que leurs parametres : \n"
            "Obtenir le nombre de segments et de contour(s) d'une image pbm : \n"
            "           ./main -nb <YOURPATHTO/image.pbm> \n\n"
            "Obtenir une image eps à partir d'une image pbm : \n"
            "           ./main -eps <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> \n\n"
            "Simplifie une image pbm en une image eps par des segments avec une simplification de degré d correspond a la distance seuil : \n"
            "           ./main -seg <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>\n\n"
            "Simplifie une image pbm en une image eps par des courbes de bézier de degré2 avec une simplification de degré d correspond à la distance seuil : \n"
            "           ./main -b2  <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>\n\n"
            "Simplifie une image pbm en une image eps par des courbes de bézier de degré3 avec une simplification de degré d correspond à la distance seuil : \n"
            "           ./main -b3  <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>\n\n"
            "Obtenir la liste des commandes et leurs fonctions\n"
            "           ./main -aide \n");
        }
    else if(strcmp(argv[1],"-nb")==0 ){
        if(argc!=3){
        printf("Vous avez choisi le parametre -nb qui correspond l'affichage du nombre de segments et de contour(s) de votre image.\n"
            "Merci de respecter le format suivant : \n"
            "                     ./main -nb <YOURPATHTO/image.pbm> \n\n");
        }
        else{
            Liste_Contour L;
            Image I;
            I=lire_fichier_image(argv[2]);
            L=contour_complet(I,true);
            supprimer_liste_contour(L);
        }
    }
    else if(strcmp(argv[1],"-seg")==0 ){
        if(argc!=7){
        printf("Vous avez choisi le parametre -eps qui correspond a la simplification d'une image pbm en une image eps par des segments avec une simplification de degré d correspondant à la distance seuil : \n"
            "Merci de respecter le format suivant : \n"
            "           ./main -seg <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>\n\n");
        }
        else{
            Liste_Contour L;
            Image I;
            double d = atof(argv[5]);
            if(strcmp(argv[4],"contours")==0){
                L=contour_depuis_txt(argv[3],&I);
            }
            else{
                I=lire_fichier_image(argv[3]);
                L=contour_complet(I,true);
                free(I.pointeur_vers_le_tableau_de_pixels);
            }
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
    tracer_EPS_contour_multiple(argv[6],I,L,argv[3],argv[2],true);
    supprimer_liste_contour(L);

        }
    }
    else if(strcmp(argv[1],"-b2")==0 || strcmp(argv[1],"-b3")==0){
        if(argc!=7){
            if(strcmp(argv[1],"-b2")==0){
                printf("Vous avez choisi le parametre -b2 qui Simplifie une image pbm en une image eps par des courbes de bézier de degré2 avec une simplification de degré d correspond à la distance seuil : \n"
                "Merci de respecter le format suivant : \n"
            "           ./main -b2  <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>\n\n");
            }
            else if(strcmp(argv[1],"-b3")==0){
                printf("Vous avez choisi le parametre -b3 qui Simplifie une image pbm en une image eps par des courbes de bézier de degré3 avec une simplification de degré d correspond à la distance seuil : \n"
                    "Merci de respecter le format suivant : \n"
                "           ./main -b3  <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>\n\n");
            }
            }
            Liste_Contour L;
            Image I;
            double d = atof(argv[5]);
            if(strcmp(argv[4],"contours")==0){
                L=contour_depuis_txt(argv[3],&I);
            }
            else{
                I=lire_fichier_image(argv[3]);
                L=contour_complet(I,true);
                free(I.pointeur_vers_le_tableau_de_pixels);
            }
            Cellule_Liste_Contour *current_contour =L.first;
            int nb_segments=0;
            for(int i=0;i<L.taille;i++){
                Liste_Point ancient_contour=current_contour->contour;
                Tableau_Point tab_contour = sequence_points_liste_vers_tableau(current_contour->contour);
                if(strcmp(argv[1],"-b2")==0){
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
            if(strcmp(argv[1],"-b2")==0){
                tracer_EPS_contour_multiple_bezier3(argv[6],I,L,argv[2],argv[3],2);
            }
            else{
                tracer_EPS_contour_multiple_bezier3(argv[6],I,L,argv[2],argv[3],3); 
            }
            supprimer_liste_contour(L);
    }
    else if(strcmp(argv[1],"-eps")==0 ){
        if(argc!=5){
        printf("Vous avez choisi le parametre -eps qui correspond à la création d'une image eps a partir d'une image pbm \n"
            "Merci de respecter le format suivant : \n"
            "           ./main -eps <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <mode de remplissage(fill/stroke)> n\n");
        }
        else{
            Liste_Contour L;
            Image I;
            I=lire_fichier_image(argv[3]);
            L=contour_complet(I,false);
            tracer_EPS_contour_multiple(argv[4],I,L,argv[3],argv[2],false);
            supprimer_liste_contour(L);
        }
    }
    else{
        printf("Commande inconnue. Pour voir la liste de commandes executez : \n./main -aide \n");
    }
    return 0;
}