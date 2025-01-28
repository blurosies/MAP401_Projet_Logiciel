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
    printf("cc(x:%f,y:%f)\n\n",round(current->point.abs*100),current->point.ord);
    fprintf(f,"%%! PS−Adobe −3.0 EPSF−3.0\n%%%%BoundingBox : %d %d %d %d\n",0,0,I.la_largeur_de_l_image,I.la_hauteur_de_l_image);
    fprintf(f,"%f %f moveto\n",round(current->point.abs*100)/100,round(current->point.ord*100)/100);
    current=current->suiv;
    for(int i =0;i<10;i++)
    {
        fprintf(f,"%f %f lineto\n",current->point.abs,current->point.ord);
        current=current->suiv;
    }
    fprintf(f,"showpage\n");
    
}

int main(int argc , char ** argv){
    if(argc != 2 ){
        printf("Format du programme ./tache3 <nom fichier>\n");
        return 0;
    }
    Liste_Point L;
    Image I;
    I=lire_fichier_image(argv[1]);
    Point init=init_position(I);
    L=contour(I,init);
    printf("Le nombre de segment est %d\n",L.taille-1);
    affiche_liste(L);
    tracer_EPS("fill",I,L,argv[1]);
}