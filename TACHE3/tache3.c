#include "TACHE1/image.h"
#include "TACHE2/geometrie2d.h"
#include "tache3.h"
#include <stdio.h>

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

void contour(Image I,Point init){
    Point current ={init.abs-1,init.ord-1};
    printf("%f %f\n",current.abs,current.ord);
    Orientation O=EST;
    BOOL boucle = TRUE;
    while (boucle)
    {
        current=avancer(current,O);
        printf("%f %f\n",current.abs,current.ord);
        O = gestion_Orientation(I,current,O);
        if( (current.abs==init.abs-1 && current.ord==init.ord-1) && O==EST){
            boucle=FALSE;
        }
    }
}

int main(){
    Image I;
    I=lire_fichier_image("TACHE3/tete.pbm");
    Point init=init_position(I);
    contour(I,init);
}