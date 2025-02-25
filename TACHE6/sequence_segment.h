#include "TACHE2/geometrie2d.h"

typedef struct Cellule_Liste_Segment
{
	Segment seg;   
	struct Cellule_Liste_Contour_* suiv; 

} Cellule_Liste_Segment;

typedef struct Liste_Segment
{
	unsigned int taille;
	Cellule_Liste_Segment *first; /* pointeur sur le premier element de la liste */

} Liste_Segment;
