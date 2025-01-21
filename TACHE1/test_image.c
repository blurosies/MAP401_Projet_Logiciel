#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"

void test_image(char* nom_fichier){
	Image img=lire_fichier_image(nom_fichier);
	ecrire_image(img);
	Image neg=negatif_image(img);
	ecrire_image(neg);
}

int main(int argc , char* argv[]){
	if (argc!=2){
		printf("uilisation: ./main <Path/Nom_Fichier>\n");
	}else{
	test_image(argv[1]); // on suppose que le nom du terrain est correcte
	}
	return 1;
}