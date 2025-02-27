#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geometrie main_tache3 tache6_test tache6


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : TACHE1/image.c TACHE1/image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : TACHE1/test_image.c TACHE1/image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
geometrie2d.o : TACHE2/geometrie2d.c TACHE2/geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<		

test_geometrie.o : TACHE2/test_geometrie.c TACHE2/geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

liste_chainee.o : TACHE3/liste_chainee.c TACHE3/liste_chainee.h TACHE2/geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module liste_chainee"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache3.o : TACHE3/tache3.c TACHE3/tache3.h TACHE1/image.h TACHE2/geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
tache6_test.o : TACHE6/tache6_test.c TACHE2/geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache6_test"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

main_tache3.o : TACHE3/main_tache3.c TACHE3/tache3.c TACHE3/tache3.h TACHE1/image.h TACHE2/geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<	

sequence_segment.o : TACHE6/sequence_segment.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module sequence_segment"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

tache6.o : TACHE6/tache6.c TACHE3/tache3.h TACHE3/liste_chainee.h TACHE1/image.h TACHE6/sequence_segment.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module tache6"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geometrie :test_geometrie.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

main_tache3: main_tache3.o tache3.o image.o geometrie2d.o liste_chainee.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
tache6_test: tache6_test.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@
tache6: tache6.o image.o liste_chainee.o tache3.o geometrie2d.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
