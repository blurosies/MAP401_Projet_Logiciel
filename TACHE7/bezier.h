#include<stdio.h>
#include "TACHE2/geometrie2d.h"

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
Point calcul_ct_2 (int t , Bezier2 b );

Point calcul_ct_3 (int t , Bezier3 b );

// conversion de bezier degré 2 au degré 3
Bezier3 conversion_degre_2_3 (Bezier2 b);