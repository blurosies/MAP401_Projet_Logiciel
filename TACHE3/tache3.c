#include "tache3.h"

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
			    l_candidats=ajouter_element_liste_Point(l_candidats,current);
			}
            current.abs++;
        }
        current.abs=1;
        current.ord++;
    }
    return l_candidats;
}

Image masque(Image I , Liste_Point liste_candidats){
    Image M=creer_image(I.la_largeur_de_l_image,I.la_hauteur_de_l_image);
    Cellule_Liste_Point *current=liste_candidats.first;
    for (int i=1 ; i<=liste_candidats.taille ; i++){
        set_pixel_image(M , current->point.abs ,current->point.ord , 1);
        current=current->suiv;
    }
    supprimer_liste_Point(liste_candidats);
    return M;
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

Liste_Point contour(Image I,Image M, Point init){
    Liste_Point L = creer_liste_Point_vide();
    Point current ={init.abs-1,init.ord-1};
    L=ajouter_element_liste_Point(L,current);
    Orientation O=EST;
    BOOL boucle = TRUE;
    if (O==EST && get_pixel_image(M,current.abs+1,current.ord+1)==1)
        set_pixel_image(M,current.abs+1,current.ord+1,0);
    while (boucle)
    {
        if (O==EST&& get_pixel_image(M,current.abs+1,current.ord+1)==1){
            set_pixel_image(M,current.abs+1,current.ord+1,0);
        }
        current=avancer(current,O);
        L=ajouter_element_liste_Point(L,current);
        O = gestion_Orientation(I,current,O);
        if( (current.abs==init.abs-1 && current.ord==init.ord-1) && O==EST){
            boucle=FALSE;
        }
    }
    return L;
}
Liste_Contour contour_complet(Image I){
    int nb_segments=0;
    Liste_Contour contours=creer_liste_Contour_vide();
    Liste_Point cand=liste_candidats(I);
    Image M=masque(I,cand); //cherche la lise des points candidats rt génère l'image masquéé M
    Liste_Point cont;
    while(image_blanche(M)==0){
        Point init= init_position(M);
        cont=contour(I,M,init);
        contours=ajouter_element_liste_Contour(contours,cont);
    }
    free(M.pointeur_vers_le_tableau_de_pixels);
    Cellule_Liste_Contour *current_contour =contours.first;
    for(int i =0;i<contours.taille;i++){
        nb_segments+=current_contour->contour.taille-1;
        current_contour=current_contour->suiv;
    }
    printf("Il y a %d contours et un total de %d segments \n",contours.taille,nb_segments);
    return contours;
}

void tracer_EPS(char *mode,Image I,Liste_Point L,char *nom,bool premier_countour,bool dernier_contour){
    FILE *f;
    char fichier[256]="";
    char *slash_pos = strrchr(nom,'/');
    sprintf(fichier,"%.*s/Fichier_eps/%.*seps",(int)(slash_pos -nom),nom,(int)(strlen(nom) - (slash_pos -nom)-4),slash_pos +1);
    Cellule_Liste_Point *current = L.first;
    if(premier_countour){
        f = fopen(fichier,"w");
        fprintf(f,"%%!PS-Adobe-3.0 EPSF-3.0\n%%%%BoundingBox: %d %d %d %d\n",0,0,I.la_largeur_de_l_image,I.la_hauteur_de_l_image);
        fprintf(f,"0 setlinewidth\n");
    }
    else{
         f = fopen(fichier,"a");
    }
    fprintf(f,"%f %f moveto\n",current->point.abs,I.la_hauteur_de_l_image-current->point.ord);
    current=current->suiv;
    for(int i =0;i<L.taille-1;i++)
    {
        fprintf(f,"%f %f lineto\n",current->point.abs,I.la_hauteur_de_l_image- current->point.ord);
        current=current->suiv;
    }
    if(dernier_contour){
        fprintf(f,"%s\n",mode);
        fprintf(f,"showpage\n");
    }
    fclose(f);
}
void tracer_EPS_contour_multiple(char *mode,Image I,Liste_Contour L,char *nom){
    Cellule_Liste_Contour *current_contour =L.first;
    for(int i = 0;i<L.taille;i++){
        if(i==0){
            tracer_EPS(mode,I,L.first->contour,nom,true,false);//Cas premier contour
        }
        else if(i==L.taille-1){
            tracer_EPS(mode,I,current_contour->contour,nom,false,true);//Cas dernier contour;
        }
        else {
            tracer_EPS(mode,I,current_contour->contour,nom,false,false);
        }
        current_contour=current_contour->suiv;
    }
}
