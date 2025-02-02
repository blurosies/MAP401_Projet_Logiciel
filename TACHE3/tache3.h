typedef enum {EST,SUD,OUEST,NORD} Orientation;

// detecte le point initial
Point init_position(Image I);

//modifie l'orientation du robot
Orientation tourner_90_degres(Orientation O);

Orientation tourner_270_degres(Orientation O);

// determine la nouvelle orientation du robot
Orientation gestion_Orientation(Image I,Point current,Orientation O);

// fait le robot avancer selon son orientation
Point avancer(Point current,Orientation O);

// determine le contour de l'image
Liste_Point contour(Image I,Point init);

// determine si un point est candidat ou pas
int est_candidat(Point p, Image I);

// retourne une liste de point candidats de l'image
Liste_Point liste_candidats(Image I);