# TP4 - Arbres Binaires de Recherche (ABR)

## Description
Ce projet est une implémentation des arbres binaires de recherche (ABR) avec gestion des occurrences des éléments. Il a été développé dans le cadre du module **NF16** et permet de manipuler une liste d'entiers en utilisant la structure d'un ABR.

## Fonctionnalités
- Création d'un arbre binaire de recherche
- Ajout d'un élément avec gestion des occurrences
- Recherche d'un élément
- Affichage des éléments triés en ordre croissant
- Suppression d'une occurrence d'un élément
- Chargement d'un ABR depuis un fichier
- Interface utilisateur interactive

## Structure du projet
Le projet est organisé en plusieurs fichiers :

```
├── main.c        # Programme principal avec l'interface utilisateur
├── tp4.c         # Définition des fonctions principales
├── tp4.h         # Fichier d'en-tête avec les déclarations des structures et fonctions
├── README.md     # Documentation du projet
└── data.txt      # Exemple de fichier d'entrée pour charger un ABR
```

## Compilation et Exécution
### Compilation
Utilisez la commande suivante pour compiler le projet :
```sh
gcc -o tp4 main.c tp4.c -Wall -Wextra
```

### Exécution
Lancez le programme en exécutant :
```sh
./tp4
```

## Utilisation
Le programme propose un menu interactif permettant d'effectuer les opérations suivantes :
1. Créer un ABR à partir d’une série d’entiers saisis par l’utilisateur
2. Créer un ABR à partir d’un fichier texte
3. Afficher tous les éléments de l’ABR
4. Rechercher un élément dans l’ABR
5. Supprimer une occurrence d’un élément de l’ABR
6. Quitter

## Exemple de fichier d'entrée (`data.txt`)
Le fichier d'entrée doit contenir une liste d'entiers séparés par des espaces ou des sauts de ligne, par exemple :
```
5 7 6 5 2 6 6
```

## Auteurs
- **BELAYACHI Ibrahim**
- **BENSALEMNadji**

## Remarque
Toutes les allocations dynamiques doivent être libérées à la fin de l'exécution du programme pour éviter les fuites de mémoire.

