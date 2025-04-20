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
Liste_Contour contour_depuis_txt(char *file,Image *I){
    FILE *fichier = fopen(file,"r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    I->la_largeur_de_l_image=0;
    I->la_hauteur_de_l_image=0;
    Liste_Contour liste_contours = creer_liste_Contour_vide();
    int nb_contours;
    fscanf(fichier, "%d", &nb_contours);

    for (int i = 0; i < nb_contours; i++) {
        int nb_points;
        fscanf(fichier, "%d", &nb_points);

        Liste_Point contour = creer_liste_Point_vide();
        
        for (int j = 0; j < nb_points; j++) {
            double x, y;
            fscanf(fichier, "%lf %lf", &x, &y);
            Point p = creer_point(x, y);
            contour = ajouter_element_liste_Point(contour, p);
            if(x> I->la_largeur_de_l_image){
                I->la_largeur_de_l_image=x;
            }
            if(y>I->la_hauteur_de_l_image){
                I->la_hauteur_de_l_image=y;
            }
        }

        liste_contours = ajouter_element_liste_Contour(liste_contours, contour);
    }

    fclose(fichier);
    return liste_contours;
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
Liste_Contour contour_complet(Image I,bool affichage){
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
    if(affichage){
        printf("Il y a %d contours et un total de %d segments \n",contours.taille,nb_segments);
    }
    return contours;
}

int tracer_EPS(char *mode,Image I,Liste_Point L,char *nom,char *dossier,bool premier_countour,bool dernier_contour,bool simplifier){
    FILE *f;
    char fichier[512]="";
    FILE *test_dir = NULL;
    char test_file[512];
    snprintf(test_file,sizeof(test_file), "%s/tmp_test_eps",dossier);//On crée un fichier temporaire pour voir si le chemin vers le dossier est bon
    test_dir = fopen(test_file,"w");
    if(test_dir == NULL){
        printf("Erreur : Dossier de sortie invalide ou sans permissions d'écriture :\n");//retourne une erreur si le dossier est inacessible
        printf("  -> Chemin essayé : %s\n", dossier);
        return 1;
    }
    fclose(test_dir);
    remove(test_file);
    
    //On recupere le nom de base du fichier sans le chemin
    char *nom_base = strrchr(nom, '/'); //renvoie la derniere occurence du caractere /
    if(nom_base!=NULL){
        nom_base = nom_base + 1;
    }
    else{
        nom_base = nom;
    }
    // Vérification de l'extension
    char *dot_pos = strrchr(nom_base, '.');
    if (dot_pos == NULL) {
        printf("Erreur : Le fichier d'entree n'a pas d'extension\n");
        return 1;
    }
    int longueur_nom = dot_pos - nom_base;

    if(simplifier){
        snprintf(fichier, sizeof(fichier), "%s/%.*s_segments.eps",dossier,longueur_nom,nom_base);
    }
    else{
        snprintf(fichier, sizeof(fichier), "%s/%.*s.eps",dossier,longueur_nom,nom_base);
    }
    f = fopen(fichier,"a");
    if(f== NULL){
        printf("Erreur : Impossible de créer le fichier EPS :\n");
        printf("  -> Chemin essayé : %s\n", fichier);
        return 1 ;
    }
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
    if(dernier_contour){
        printf("Fichier EPS cree avec succes : %s\n",fichier);
    }
    return 0;
}
void tracer_EPS_contour_multiple(char *mode,Image I,Liste_Contour L,char *dossier,char *nom,bool simplifier){
    Cellule_Liste_Contour *current_contour =L.first;
    int erreur =0;
    for(int i = 0;i<L.taille;i++){
        if(i==0){
            erreur=tracer_EPS(mode,I,L.first->contour,dossier,nom,true,false,simplifier);//Cas premier contour
        }
        else if(i==L.taille-1){
            erreur=tracer_EPS(mode,I,current_contour->contour,dossier,nom,false,true,simplifier);//Cas dernier contour;
        }
        else {
            erreur=tracer_EPS(mode,I,current_contour->contour,dossier,nom,false,false,simplifier);
        }
        if(erreur==1){
            return;
        }
        current_contour=current_contour->suiv;
    }
}