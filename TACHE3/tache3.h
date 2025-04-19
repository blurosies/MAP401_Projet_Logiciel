#include <stdbool.h>
#include "TACHE1/image.h"
#include "liste_chainee.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef TACHE3_H
#define TACHE3_H


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
Liste_Point contour(Image I,Image M, Point init);

// determine si un point est candidat ou pas
int est_candidat(Point p, Image I);

// retourne une liste de point candidats de l'image
Liste_Point liste_candidats(Image I);

//retourne la liste de tous les contours d'une image
Liste_Contour contour_complet(Image I,bool affichage);

// produit l'image masquée à l'aide de sa liste de points candidats
Image masque(Image I , Liste_Point liste_candidats);

//crée le fichier eps d'une image avec un seul contour
int tracer_EPS(char *mode,Image I,Liste_Point L,char *nom,char *dossier,bool premier_countour,bool dernier_contour,bool simplifier);

//crée le fichier eps d'une image avec plusieur contours
void tracer_EPS_contour_multiple(char *mode,Image I,Liste_Contour L,char *dossier,char *nom,bool simplifier);

#endif