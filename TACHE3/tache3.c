#include "TACHE1/image.h"
#include "liste_chainee.h"
#include "tache3.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

Point init_position(Image I){
    Point current = creer_point(1,1);
    while ((current.ord!=hauteur_image(I))||(current.abs!=largeur_image(I))){
    if((get_pixel_image(I,current.abs,current.ord)==1) && (get_pixel_image(I,current.abs,current.ord-1)==0))
            return current;
    else{
        if(current.abs<largeur_image(I)){
            current.abs+=1;
        }
        else if(current.abs==largeur_image(I)){
            current.abs=1;
            current.ord+=1;
        }
    }
    }
    if((get_pixel_image(I,current.abs,current.ord)==1) && (get_pixel_image(I,current.abs,current.ord+1)==0))
            return current;
    else{
        printf("Pas de point initial");
        current.ord=-1;
        current.abs=-1;
        return current;
    }
}

int est_candidat(Point p, Image I){ //on suppose que le point appartient bien à l'image
    if((get_pixel_image(I,p.abs,p.ord)==1) && (get_pixel_image(I,p.abs,p.ord-1)==0))
        return 1;
    else 
        return 0;
} 

Liste_Point liste_candidats(Image I){
    int j;
    int i;
    Liste_Point l_candidats = creer_liste_Point_vide();
    Point current = creer_point(1,1);
    for (i=1 ; i<=I.la_hauteur_de_l_image ; i++){
		for (j=1 ; j<=I.la_largeur_de_l_image ; j++){
			if(est_candidat(current , I)){
			    ajouter_element_liste_Point(l_candidats,current);
			}
            current.abs++;
        }
    current.ord++;
    }
    return l_candidats;
}

Orientation tourner_90_degres(Orientation O){
    switch (O)
    {
    case EST:
        return NORD;
        break;
    case SUD:
        return EST;
        break;
    case OUEST:
        return SUD;
        break;
    case NORD:
        return OUEST;
        break;
    default:
        break;
    }

}
Orientation tourner_270_degres(Orientation O){
    switch (O)
    {
    case EST:
        return SUD;
        break;
    case SUD:
        return OUEST;
        break;
    case OUEST:
        return NORD;
        break;
    case NORD:
        return EST;
        break;
    default:
        break;
    }

}
Orientation gestion_Orientation(Image I,Point current,Orientation O){
    Point pg;
    Point pd;
    switch (O)
    {
    case EST:
        pg.abs=current.abs+1;
        pg.ord=current.ord;
        pd.abs=current.abs+1;
        pd.ord=current.ord+1;
        break;
    case SUD:
        pg.abs=current.abs+1;
        pg.ord=current.ord+1;
        pd.abs=current.abs;
        pd.ord=current.ord+1;
        break;
    case OUEST:
        pg.abs=current.abs;
        pg.ord=current.ord+1;
        pd.abs=current.abs;
        pd.ord=current.ord;
        break;
    case NORD:
        pg.abs=current.abs;
        pg.ord=current.ord;
        pd.abs=current.abs+1;
        pd.ord=current.ord;
        break;
    default:
        break;
    }
    if(get_pixel_image(I,pg.abs,pg.ord)==1){
        O= tourner_90_degres(O);       
    }
    else if(get_pixel_image(I,pd.abs,pd.ord)==0){
        O= tourner_270_degres(O);
    }
    return O;
}
Point avancer(Point current,Orientation O){
    switch (O)
    {
    case EST:
        current.abs+=1;
        break;
    case SUD:
        current.ord+=1;
        break;
    case OUEST:
        current.abs-=1;
        break;
    case NORD:
        current.ord-=1;
        break;
    default:
        break;
    }
    return current;
}

Liste_Point contour(Image I,Point init){
    Liste_Point L = creer_liste_Point_vide();
    Point current ={init.abs-1,init.ord-1};
    L=ajouter_element_liste_Point(L,current);
    Orientation O=EST;
    BOOL boucle = TRUE;
    while (boucle)
    {
        current=avancer(current,O);
        L=ajouter_element_liste_Point(L,current);
        O = gestion_Orientation(I,current,O);
        if( (current.abs==init.abs-1 && current.ord==init.ord-1) && O==EST){
            boucle=FALSE;
        }
    }
    return L;
}

void tracer_EPS(char *mode,Image I,Liste_Point L,char *nom){
    char fichier[100]="";
    strcat(fichier,nom);
    strcpy(fichier + strlen(fichier)-3,"eps");
    FILE * f = fopen(fichier,"w");
    Cellule_Liste_Point *current = L.first;
    fprintf(f,"%%! PS−Adobe −3.0 EPSF−3.0\n%%%%BoundingBox: %d %d %d %d\n",0,0,I.la_largeur_de_l_image,I.la_hauteur_de_l_image);
    fprintf(f,"0 setlinewidth\n");
    fprintf(f,"%f %f moveto\n",current->point.abs,I.la_hauteur_de_l_image-current->point.ord);
    current=current->suiv;
    printf("%d",L.taille);
    for(int i =0;i<L.taille-1;i++)
    {
        fprintf(f,"%f %f lineto\n",current->point.abs,I.la_hauteur_de_l_image- current->point.ord);
        current=current->suiv;
    }
    fprintf(f,"%s\n",mode);
    fprintf(f,"showpage\n");
    
}

int main(int argc , char ** argv){
    if(argc != 3 ){
        printf("Format du programme ./tache3 <nom fichier> <mode de remplissage(stroke/fill) \n");
        return 0;
    }
    Liste_Point L;
    Liste_Point cand;
    Image I;
    I=lire_fichier_image(argv[1]);
    ecrire_image(I);
    Point init=init_position(I);
    L=contour(I,init);
    affiche_liste(L);
    printf("Le nombre de segment est %d\n",L.taille-1);
    tracer_EPS(argv[2],I,L,argv[1]);
    cand=liste_candidats(I);
    affiche_liste(cand);
}