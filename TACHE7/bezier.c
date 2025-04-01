#include "bezier.h" 


Bezier2 creer_b2(Point c0 , Point c1 , Point c2){
    Bezier2 B2 = {c0,c1,c2};
    return B2;
}

Bezier3 creer_b3(Point c0 , Point c1 , Point c2 , Point c3){
    Bezier3 B3 = {c0,c1,c2,c3};
    return B3;
}

Point calcul_ct_2 (int t , Bezier2 b ){
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


Point calcul_ct_3 (int t , Bezier3 b ){
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
Liste_Point simplification_douglas_peucker_2(Tableau_Point tab_contour,int j1,int j2,double d){

}

double distance_point_bezier2 (){}

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

Liste_Point simplification_douglas_peucker_bezier3(Tableau_Point tab_contour,int j1,int j2,double d){
    Liste_Point l =creer_liste_Point_vide();
    double n =j2-j1;
    Bezier3 b =approx_bezier3(tab_contour,j1,j2);
    double dmax=0;
    int k = j1;
    for(int j=j1+1;j<=j2;j++){
        double i = j-j1;
        double ti=i/n;
        double dj=distance_point_bezier3(tab_contour.tab[j],b,ti);
        if(dmax <dj) {
            dmax=dj;
            k=j;
        }
    }
    if(dmax <=d){
        ajoute_bezier3(b,l);
    }
    else{
        Liste_Point l1=simplification_douglas_peucker_bezier3(tab_contour,j1,k,d);
        Liste_Point l2=simplification_douglas_peucker_bezier3(tab_contour,k,j2,d);
        l=concatener_liste_Point(l1,l2);
    }
    return l;
}


double distance_point_bezier3 (Point p,Bezier3 b,double ti){
    return dist_points(p,calcul_ct_3(ti,b));
}

Bezier3 approx_bezier3 (Tableau_Point tab_contour,int j1,int j2){
    Bezier3 b;
    double n =j2-j1;
    if(n==1 || n==2){
        Bezier2 b2=approx_bezier2(tab_contour,j1,j2);
        b =conversion_degre_2_3(b2);
    }
    else {
        Point c0=tab_contour.tab[j1];
        Point c3=tab_contour.tab[j2];
        double alpha=(-15*pow(n,3)+5*pow(n,2)+2*n+4)/(3*(n+2)*(3*pow(n,2)+1));
        double beta=(10*pow(n,3)-15*pow(n,2)+n+2)/(3*(n+2)*(3*pow(n,2)+1));
        double lambda=(70*n)/(3*(pow(n,2)-1)*(pow(n,2)-4)*(3*pow(n,2)+1));
        Point c1;
        double somme_abs=0;
        double somme_ord=0;
        for(int i=1;i<n;i++){
            somme_abs+=(6*pow(i,4)-8*n*pow(i,3)+6*pow(i,2)-4*n*i+pow(n,4)-pow(n,2))*tab_contour.tab[j1+i].abs;
            somme_ord+=(6*pow(i,4)-8*n*pow(i,3)+6*pow(i,2)-4*n*i+pow(n,4)-pow(n,2))*tab_contour.tab[j1+i].ord;
        }
        printf("%f\n",somme_abs);
        printf("%f\n",somme_ord);
        c1.abs=alpha*c0.abs+lambda*somme_abs+beta*c3.abs;
        c1.ord=alpha*c0.ord+lambda*somme_ord+beta*c3.ord;
        Point c2;
        somme_abs=0;
        somme_ord=0;
        for(int i=1;i<n;i++){
            somme_abs+=(6*pow(n-i,4)-8*n*pow(n-i,3)+6*pow(n-i,2)-4*n*(n-i)+pow(n,4)-pow(n,2))*tab_contour.tab[j1+i].abs;
            somme_ord+=(6*pow(n-i,4)-8*n*pow(n-i,3)+6*pow(n-i,2)-4*n*(n-i)+pow(n,4)-pow(n,2))*tab_contour.tab[j1+i].ord;
        }
        printf("%f\n",somme_abs);
        printf("%f\n",somme_ord);
        c2.abs=beta*c0.abs+lambda*somme_abs+alpha*c3.abs;
        c2.ord=beta*c0.ord+lambda*somme_ord+alpha*c3.ord;
        b=creer_b3(c0,c1,c2,c3);
    }
    return b;
}
