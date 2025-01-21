
typedef struct Point_
{
	double abs,ord;
} Point;

typedef struct Vecteur_
{
	double a,b;
} Vecteur;

// creer un point a partir de deux coordonnées
Point creer_point(double abs , double ord);

// creer un vecteur a partir de deux points
Vecteur creer_vecteur (Point a , Point b);

// somme de deux points
Point somme_point(Point a, Point b);

// somme de deux vecteurs
Vecteur somme_vecteur(Vecteur a, Vecteur b);

// multiplication d'un point par un réel
Point mult_reel_p(Point a, double d);

// multiplication d'un vecteur par un réel
Point mult_reel_v(Point a, double d);

// Produit scalaire de deux vecteur
Vecteur produit_scalaire(Vecteur a , Vecteur b);

// Norme d'un vecteur
double norme_vect(Vecteur a);

// distance entre deux points
double dist_points(Point a, Point b);