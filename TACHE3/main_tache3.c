#include "tache3.h"

int main(int argc , char ** argv){
    if(argc != 3 ){
        printf("Format du programme ./tache3 <nom fichier> <mode de remplissage(stroke/fill) \n");
        return 0;
    }
    Liste_Contour L;
    Image I;
    I=lire_fichier_image(argv[1]);
    L=contour_complet(I);
    if(L.taille==1){ //Cas ou l'image a un seul contour
        tracer_EPS(argv[2],I,L.first->contour,argv[1],true,true);
    }
    else{ // Cas ou l'image a plusieur contours
    tracer_EPS_contour_multiple(argv[2],I,L,argv[1]);
    }
}