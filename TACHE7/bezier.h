#include "TACHE3/tache3.h"
#include <math.h>

typedef struct Bezier2_
{
    Point c0,c1,c2;
} Bezier2;

typedef struct Bezier3_
{
    Point c0, c1, c2, c3;
} Bezier3;


// creation d'une bezier 2 ou 3 à partir de points de controles
Bezier2 creer_b2(Point c0 , Point c1 , Point c2);

Bezier3 creer_b3(Point c0 , Point c1 , Point c2 , Point c3);

// calculer le point c(t) d'une bézier de degré 2 ou 3
Point calcul_ct_2 (double t , Bezier2 b );

Point calcul_ct_3 (double t , Bezier3 b );


// conversion de bezier degré 2 au degré 3
Bezier3 conversion_degre_2_3 (Bezier2 b);

// Distance entre un point P et une courbe de bézier de degré 2
double distance_point_bezier2 (Point p,Bezier2 b,double ti);

// Distance entre un point P et une courbe de bézier de degré 3
double distance_point_bezier3(Point p,Bezier3 b,double ti);

// approximation d'une partie du contour en une courbe de bézier de degré deux
Bezier2 approx_bezier2 (Tableau_Point contour,int j1,int j2);

// approximation d'une partie du contour en une courbe de bézier de degré trois
Bezier3 approx_bezier3 (Tableau_Point tab_contour,int indice_a,int indice_b);

// algo douglas pecker degre 2
Liste_Point simplification_douglas_peucker_2(Tableau_Point tab_contour,int j1,int j2,double d);

// algo douglas pecker degre 3
Liste_Point simplification_douglas_peucker_3(Tableau_Point tab_contour,int j1,int j2,double d);

// ajoute  une bezier 2 a une liste de points
Liste_Point ajoute_bezier2 (Bezier2 B , Liste_Point contour);

// ajoute  une bezier 3 a une liste de points
Liste_Point ajoute_bezier3 (Bezier3 B , Liste_Point contour);

// Fonctions pour exporter les images en fichier eps pour les courbes de Bézier 2 et 3

void tracer_EPS_bezier3(char *mode,Image I,Liste_Point L,char *nom,bool premier_countour,bool dernier_contour,int type_bezier);
    
void tracer_EPS_contour_multiple_bezier3(char *mode,Image I,Liste_Contour L,char *nom,int type_bezier);