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
