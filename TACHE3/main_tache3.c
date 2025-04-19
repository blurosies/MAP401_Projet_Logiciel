#include "tache3.h"

int main(int argc , char ** argv){
    if(argc != 4 ){
        printf("Format du programme ./tache3 <dossier de sortie> <nom fichier> <mode de remplissage(stroke/fill) \n");
        return 0;
    }
    Liste_Contour L;
    Image I;
    I=lire_fichier_image(argv[1]);
    L=contour_complet(I,true);
    if(L.taille==1){ //Cas ou l'image a un seul contour
        tracer_EPS(argv[3],I,L.first->contour,argv[1],argv[2],true,true,false);
    }
    else{ // Cas ou l'image a plusieur contours
    tracer_EPS_contour_multiple(argv[3],I,L,argv[1],argv[2],false);
    }
}