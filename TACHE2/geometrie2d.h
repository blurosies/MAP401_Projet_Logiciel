
typedef struct Point_
{
	double abs,ord;
} Point;

typedef struct Vecteur_
{
	double abs,ord;
} Vecteur;

typedef struct Segment_
{
	Point a;
	Point b;
}Segment;

// creer un point a partir de deux coordonnées
Point creer_point(double abs , double ord);

// creer un vect a coordonnées
Vecteur creer_vecteur(double abs, double ord);

// creer un vecteur a partir de deux points
Vecteur creer_vecteur_bip (Point a , Point b);

// creer un segment a partir de deux points
Segment creer_segment (Point a,Point b);

// somme de deux points
Point somme_point(Point a, Point b);

// somme de deux vecteurs
Vecteur somme_vecteur(Vecteur u, Vecteur v);

// multiplication d'un point par un réel
Point mult_reel_p(Point a, double d);

// multiplication d'un vecteur par un réel
Vecteur mult_reel_v(Vecteur u, double d);

// Produit scalaire de deux vecteur
double produit_scalaire(Vecteur u , Vecteur v);

// Norme d'un vecteur
double norme_vect(Vecteur u);

// distance entre deux points
double dist_points(Point a, Point b);

// calculer la distance point segment
double distance_point_segment (Point a, Segment seg);