#include "bezier.h" 


Bezier2 creer_b2(Point c0 , Point c1 , Point c2){
    Bezier2 B2 = {c0,c1,c2};
    return B2;
}

Bezier3 creer_b3(Point c0 , Point c1 , Point c2 , Point c3){
    Bezier3 B3 = {c0,c1,c2,c3};
    return B3;
}

Point calcul_ct_2 (double t , Bezier2 b ){
    if (t>1 || t<0){
        printf("t doit être entre 0 et 1 \n");
        Point ct=creer_point(0,0);
        return ct;
    }else{
        double abs= (b.c0.abs*(1-t)*(1-t)) + (b.c1.abs*2*t*(1-t)) + (b.c2.abs*t*t);
        double ord= (b.c0.ord*(1-t)*(1-t)) + (b.c1.ord*2*t*(1-t)) + (b.c2.ord*t*t);
        Point Ct=creer_point(abs,ord);
        return Ct;
    }
}


Point calcul_ct_3 (double t , Bezier3 b ){
    if (t>1 || t<0){
        printf("t doit être entre 0 et 1 \n");
        Point ct=creer_point(0,0);
        return ct;
    }else{
        double abs= (b.c0.abs*(1-t)*(1-t)*(1-t)) + (b.c1.abs*3*t*(1-t)*(1-t)) + (b.c2.abs*3*t*t*(1-t)) + (b.c3.abs*t*t*t);
        double ord= (b.c0.ord*(1-t)*(1-t)*(1-t)) + (b.c1.ord*3*t*(1-t)*(1-t)) + (b.c2.ord*3*t*t*(1-t)) + (b.c3.ord*t*t*t);
        Point Ct=creer_point(abs,ord);
        return Ct;
    }
}

Bezier3 conversion_degre_2_3 (Bezier2 b){
    double c1_abs=(b.c0.abs+2*b.c1.abs)/3.0;
    double c1_ord=(b.c0.ord+2*b.c1.ord)/3.0;
    double c2_abs=(b.c2.abs+2*b.c1.abs)/3.0;
    double c2_ord=(b.c2.ord+2*b.c1.ord)/3.0;

    Point c1=creer_point(c1_abs,c1_ord);
    Point c2=creer_point(c2_abs,c2_ord);

    Bezier3 c_converti=creer_b3(b.c0 , c1 , c2 , b.c2);
    return c_converti;
}

Liste_Point ajoute_bezier2 (Bezier2 B , Liste_Point contour){
    contour=ajouter_element_liste_Point(contour,B.c0);
    contour=ajouter_element_liste_Point(contour,B.c1);
    contour=ajouter_element_liste_Point(contour,B.c2);
    return contour;
}

Liste_Point ajoute_bezier3 (Bezier3 B , Liste_Point contour){
    contour=ajouter_element_liste_Point(contour,B.c0);
    contour=ajouter_element_liste_Point(contour,B.c1);
    contour=ajouter_element_liste_Point(contour,B.c2);
    contour=ajouter_element_liste_Point(contour,B.c3);
    return contour;
}

double distance_point_bezier2 (Point p,Bezier2 b,double ti){
    return dist_points(p,calcul_ct_2(ti,b));
}

Liste_Point simplification_douglas_peucker_2(Tableau_Point tab_contour,int j1,int j2,double d){
    if (d<0){
        printf("d doit être positif");
    } else {
        Liste_Point l =creer_liste_Point_vide();
        double n = j2-j1;
        Bezier2 B2= approx_bezier2(tab_contour, j1, j2);
        double dmax = 0;
        int k = j1;
        for(int j=j1+1;j<=j2;j++){
            int i = j-j1;
            double ti=(double)i/(double)n;
            double dj=distance_point_bezier2(tab_contour.tab[j1+i], B2,ti);
            if(dmax <dj) {
                dmax=dj;
                k=j;
            }
        }
        if(dmax <=d){
            l=ajoute_bezier2(B2,l);
        }
        else{
            Liste_Point l1=simplification_douglas_peucker_2(tab_contour,j1,k,d);
            Liste_Point l2=simplification_douglas_peucker_2(tab_contour,k,j2,d);
            l=concatener_liste_Point(l1,l2);
        }
    }
}


Bezier2 approx_bezier2 (Tableau_Point contour , int j1 , int j2){
    Point C0= contour.tab[j1]; //C0 = Pj1
    Point C2= contour.tab[j2]; //C2 = Pj2
    Point C1;
    double n = j2-j1;

    if (n==1){ //le contour est réduit a deux points
        C1= creer_point((C0.abs+C2.abs)/2.0, (C0.ord+C2.ord)/2.0); // C1= (Pj1+Pj2)/2
    } else {
        double alpha=(3*n)/(n*n-1);
        double beta=(1-2*n)/(2*(n+1));
        double somme_abs=0;
        double somme_ord=0;
        for (int i = 1; i < n; i++)
        {
            somme_abs+=contour.tab[i+j1].abs;
            somme_ord+=contour.tab[i+j1].ord;
        }
        double C1_abs= alpha*somme_abs + beta*(C0.abs+C2.abs);
        double C1_ord= alpha*somme_ord + beta*(C0.ord+C2.ord);
        C1=creer_point(C1_abs, C1_ord);
    }
    Bezier2 approx= creer_b2(C0,C1,C2);
    return approx;
}

Liste_Point simplification_douglas_peucker_3(Tableau_Point tab_contour,int j1,int j2,double d){
    Liste_Point l =creer_liste_Point_vide();
    int n =j2-j1;
    Bezier3 b =approx_bezier3(tab_contour,j1,j2);
    double dmax=0;
    int k = j1;
    for(int j=j1+1;j<=j2;j++){
        int i = j-j1;
        double ti=(double)i/(double)n;
        double dj=distance_point_bezier3(tab_contour.tab[j1+i],b,ti);
        if(dmax <dj) {
            dmax=dj;
            k=j;
        }
    }
    if(dmax <=d){
        l=ajoute_bezier3(b,l);
    }
    else{
        Liste_Point l1=simplification_douglas_peucker_3(tab_contour,j1,k,d);
        Liste_Point l2=simplification_douglas_peucker_3(tab_contour,k,j2,d);
        l=concatener_liste_Point(l1,l2);
    }
    return l;
}

double distance_point_bezier3(Point p,Bezier3 b,double ti){
    return dist_points(p,calcul_ct_3(ti,b));
}

Bezier3 approx_bezier3 (Tableau_Point tab_contour,int j1,int j2){
    Bezier3 b;
    int n =j2-j1;
    double d_n=(double) n ;
    if(n==1 || n==2){
        Bezier2 b2=approx_bezier2(tab_contour,j1,j2);
        b =conversion_degre_2_3(b2);
    }
    else {
        Point c0=tab_contour.tab[j1];
        Point c3=tab_contour.tab[j2];
        double alpha=((-15)*pow(d_n,3)+5*pow(d_n,2)+2*n+4)/(3*(d_n+2)*(3*pow(d_n,2)+1));
        double beta=(10*pow(d_n,3)-(15*pow(d_n,2))+d_n+2)/(3*(d_n+2)*(3*pow(d_n,2)+1));
        double lambda=(70*d_n)/(3*(pow(d_n,2)-1)*(pow(d_n,2)-4)*(3*pow(d_n,2)+1));
        Point c1;
        double somme_abs=0;
        double somme_ord=0;
        for(int i=1;i<n;i++){
            double d_i= (double) i ;
            somme_abs+=(6*pow(d_i,4)-8*d_n*pow(d_i,3)+6*pow(d_i,2)-4*d_n*d_i+pow(d_n,4)-pow(d_n,2))*tab_contour.tab[j1+i].abs;
            somme_ord+=(6*pow(d_i,4)-8*d_n*pow(d_i,3)+6*pow(d_i,2)-4*d_n*d_i+pow(d_n,4)-pow(d_n,2))*tab_contour.tab[j1+i].ord;
        }
        c1.abs=alpha*c0.abs+lambda*somme_abs+beta*c3.abs;
        c1.ord=alpha*c0.ord+lambda*somme_ord+beta*c3.ord;
        Point c2;
        somme_abs=0;
        somme_ord=0;
        for(int i=1;i<n;i++){
            double d_i= (double) i ;
            somme_abs+=(6*pow(d_n-d_i,4)-8*d_n*pow(d_n-d_i,3)+6*pow(d_n-d_i,2)-4*d_n*(d_n-d_i)+pow(d_n,4)-pow(d_n,2))*tab_contour.tab[j1+i].abs;
            somme_ord+=(6*pow(d_n-d_i,4)-8*d_n*pow(d_n-d_i,3)+6*pow(d_n-d_i,2)-4*d_n*(d_n-d_i)+pow(d_n,4)-pow(d_n,2))*tab_contour.tab[j1+i].ord;
        }
        c2.abs=beta*c0.abs+lambda*somme_abs+alpha*c3.abs;
        c2.ord=beta*c0.ord+lambda*somme_ord+alpha*c3.ord;
        b=creer_b3(c0,c1,c2,c3);
    }
    return b;
}

void tracer_EPS_bezier3(char *mode,Image I,Liste_Point L,char *nom,bool premier_countour,bool dernier_contour){
    FILE *f;
    char fichier[256]="";
    char *slash_pos = strrchr(nom,'/');
    sprintf(fichier,"%.*s/Fichier_eps/%.*s_bezier3.eps",(int)(slash_pos -nom),nom,(int)(strlen(nom) - (slash_pos -nom)-4),slash_pos +1);
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
    for(int i =0;i<(L.taille)/4;i++)
    {
        
        fprintf(f,"%f %f %f %f %f %f curveto\n",current->suiv->point.abs,I.la_hauteur_de_l_image-current->suiv->point.ord,current->suiv->suiv->point.abs,I.la_hauteur_de_l_image-current->suiv->suiv->point.ord,current->suiv->suiv->suiv->point.abs,I.la_hauteur_de_l_image-current->suiv->suiv->suiv->point.ord);
        current=current->suiv->suiv->suiv->suiv;
    }
    if(dernier_contour){
        fprintf(f,"%s\n",mode);
        fprintf(f,"showpage\n");
    }
    fclose(f);
}
void tracer_EPS_contour_multiple_bezier3(char *mode,Image I,Liste_Contour L,char *nom){
    Cellule_Liste_Contour *current_contour =L.first;
    for(int i = 0;i<L.taille;i++){
        if(i==0){
            tracer_EPS_bezier3(mode,I,L.first->contour,nom,true,false);//Cas premier contour
        }
        else if(i==L.taille-1){
            tracer_EPS_bezier3(mode,I,current_contour->contour,nom,false,true);//Cas dernier contour;
        }
        else {
            tracer_EPS_bezier3(mode,I,current_contour->contour,nom,false,false);
        }
        current_contour=current_contour->suiv;
    }
}