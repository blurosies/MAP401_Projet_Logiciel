# Manuel d'exécution du projet

Ce projet implémente des algorithmes de vectorisation d'images (format PBM vers EPS).

## 🏗️ Architecture et Compilation

Nous avons fait le choix architectural de regrouper l'ensemble des fonctionnalités (tâches) dans un **fichier source unique `main.c`**. Cette approche centralisée permet :
* Une meilleure maintenabilité du code.
* Moins de confusion lors de l'exécution (un seul point d'entrée).
* Une compilation simplifiée.

### Instructions de compilation

Pour générer l'exécutable principal `main` :
```bash
make
```
Liste des commandes

Voici la liste des options à votre disposition ainsi que leurs paramètres.
1. Analyse d'image

Obtenir le nombre de segments et de contour(s) d'une image pbm :
Bash

```bash
./main -nb <YOURPATHTO/image.pbm>
```
2. Conversion simple

Obtenir une image eps à partir d'une image pbm :

```bash
./main -eps <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm>
```
3. Simplification par Segments

Simplifie une image pbm en une image eps par des segments avec une simplification de degré d (correspondant à la distance seuil) :

```bash
./main -seg <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>
```
4. Simplification par Courbes de Bézier (Degré 2)

Simplifie une image pbm en une image eps par des courbes de Bézier de degré 2 avec une simplification de degré d (correspondant à la distance seuil) :

```bash
./main -b2 <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>

```
5. Simplification par Courbes de Bézier (Degré 3)

Simplifie une image pbm en une image eps par des courbes de Bézier de degré 3 avec une simplification de degré d (correspondant à la distance seuil) :

```bash
./main -b3 <YOURPATHTO/DossierDeSortie> <YOURPATHTO/image.pbm> <type de fichier (pbm/contours)> <distance seuil> <mode de remplissage(fill/stroke)>
```
Aide

Obtenir la liste des commandes et leurs fonctions :
```bash
./main -aide
```
