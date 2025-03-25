#include "liste_chainee.h"

/* creer une cellule de liste avec l'element v 
   renvoie le pointeur sur la cellule de liste creee
   la fonction s'arrete si la creation n'a pas pu se faire */
Cellule_Liste_Point *creer_element_liste_Point(Point v)
{
	Cellule_Liste_Point *el;
	el = (Cellule_Liste_Point *)malloc(sizeof(Cellule_Liste_Point));
	if (el==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	el->point = v;
	el->suiv = NULL;
	return el;
}
/*fonctions pour la liste de contours*/

Cellule_Liste_Contour *creer_element_liste_Contour(Liste_Point v)
{
	Cellule_Liste_Contour *cont;
	cont = malloc(sizeof(Cellule_Liste_Contour));
	if (cont==NULL)
	{
		fprintf(stderr, "creer_element_liste_Point : allocation impossible\n");
		exit(-1);
	}
	cont->contour = v;
	cont->suiv = NULL;
	return cont;
}

Liste_Contour creer_liste_Contour_vide()
{
	Liste_Contour L;
	L.first=NULL;
	L.taille=0;
	return L;
}


Liste_Contour ajouter_element_liste_Contour(Liste_Contour L, Liste_Point e)
{
	Cellule_Liste_Contour *el;
	
	el = creer_element_liste_Contour(e);
	if (L.first==NULL)
	{
		L.first = el;
		el->suiv=NULL;
	}
	else
	{
		el->suiv=L.first;
		L.first=el;
	}
	L.taille++;
	return L;
}

/* creer une liste vide */
Liste_Point creer_liste_Point_vide()
{
	Liste_Point L = {0, NULL, NULL};
	return L;
}

Liste_Point ajouter_element_liste_Point(Liste_Point L, Point e)
{
	Cellule_Liste_Point *el;
	
	el = creer_element_liste_Point(e);
	if (L.taille ==0 )
	{
		L.first = L.last = el;
	}
	else
	{
		L.last->suiv=el;
		L.last = el;
	}
	L.taille++;
	return L;
}

/* supprimer tous les elements de la liste, renvoie la liste L vide */
Liste_Point supprimer_liste_Point(Liste_Point L)
{
	Cellule_Liste_Point *el=L.first;
	
	while (el) 
	{		
		Cellule_Liste_Point *suiv=el->suiv;
		free(el);
		el = suiv;
	}
	L.first = L.last = NULL; L.taille = 0;
	return L;
}
void supprimer_liste_contour(Liste_Contour contours){
	Cellule_Liste_Contour *current_contour=contours.first;
	while(current_contour!=NULL){
		Cellule_Liste_Contour *next= current_contour->suiv;
		current_contour->contour=supprimer_liste_Point(current_contour->contour);
		free(current_contour);
		current_contour=next;
	}
}

/* concatener L2 a la suite de L1, renvoie la liste L1 modifiee */
Liste_Point concatener_liste_Point(Liste_Point L1, Liste_Point L2)
{
	/* cas o� l'une des deux listes est vide */
	if (L1.taille == 0) return L2; 
	if (L2.taille == 0) return L1;
	
	/* les deux listes sont non vides */
	L1.last->suiv = L2.first; /* lien entre L1.last et L2.first */
	L1.last = L2.last;        /* le dernier element de L1 est celui de L2 */
	L1.taille += L2.taille;   /* nouvelle taille pour L1 */
	return L1;
}

/* si la liste est non vide, la fonction supprime le premier element de L 
   si la liste est vide, la fonction ne fait rien 
   la fonction renvoie la liste (eventuellement) modifiee */
Liste_Point supprimer_premier_element_liste_Point(Liste_Point L)
{
	/* cas d'une liste L vide : ne rien faire */
	if (L.taille == 0) return L;
	
	Cellule_Liste_Point *e1=L.first;  /* pointeur vers le premier element  */ 
	Cellule_Liste_Point *e2=e1->suiv; /* pointeur vers le deuxieme element */ 
	
	/* supprimer l'element pointe par e1 */
	free(e1);
	
	/* mettre a jour la structure L */
	L.first = e2;
	if (e2 == NULL)    /* cas d'une liste L avec un seul element */
		L.last = NULL; /* --> la liste L devient une liste vide  */
	L.taille--;
	return L;
}


/* creer une sequence de points sous forme d'un tableau de points 
   a partir de la liste de points L */
Tableau_Point sequence_points_liste_vers_tableau(Liste_Point L)
{
	Tableau_Point T;
	
	/* taille de T = taille de L */
	T.taille = L.taille;
	
	/* allocation dynamique du tableau de Point */
	T.tab = malloc(sizeof(Point) * T.taille);
	if (T.tab == NULL)
	{
		/* allocation impossible : arret du programme avec un message */
		fprintf(stderr, "sequence_points_liste_vers_tableau : ");
		fprintf(stderr, " allocation impossible\n");
		exit(-1);
	}
	
	/* remplir le tableau de points T en parcourant la liste L */
	int k = 0; /* indice de l'element dans T.tab */
	Cellule_Liste_Point *el = L.first; /* pointeur sur l'element dans L */
	while (el) 
	{
		T.tab[k] = el->point;
		k++; /* incrementer k */
		el = el->suiv; /* passer a l'element suivant dans la liste chainee */
	}
	
	return T;
}
Liste_Point tableau_vers_liste_points(Tableau_Point T){
	Liste_Point L=creer_liste_Point_vide();
	for(int i =0;i<T.taille;i++){
		ajouter_element_liste_Point(L,T.tab[i]);
	}
	return L ;
}

/* ecrire le contour L a l'ecran 
   cette fonction montre un exemple de conversion d'une liste de points en
   tableau de points afin de pouvoir par la suite acceder aux elements d'une
   sequence de points par indice */
void ecrire_contour(Liste_Point L)
{
	Tableau_Point TP = sequence_points_liste_vers_tableau(L);
	int k;
	int nP = TP.taille;
	
	printf("Contour avec %d points\n[", nP);
	for (k = 0; k < nP; k++)
	{	
		Point P = TP.tab[k]; /* recuperer le point d'indice k */
		printf(" (%5.1f,%5.1f)", P.abs, P.ord);
	} 
	printf("]\n");
	
	free(TP.tab); /* supprimer le tableau de point TP */
}
void affiche_liste(Liste_Point L){
	Cellule_Liste_Point *current=L.first;
	while (current)
	{
		printf("(x:%f,y:%f)\n",current->point.abs,current->point.ord);
		current=current->suiv;
	}
	
}

void affiche_liste_Contour(Liste_Contour L){
	if(L.first!=NULL){
		Cellule_Liste_Contour *current=L.first;
		while (current)
		{
			affiche_liste(current->contour);
			printf("\n");
			current=current->suiv;
		}
		
	}
}
