# Formatteur CSV — Remplacement de barres verticales par des virgules

Ce programme en C transforme un fichier CSV dans lequel les champs sont séparés par une ou plusieurs barres verticales (`|`) en un fichier CSV standard où les séparateurs sont des virgules (`,`).

## Fonctionnalités

- Lit un fichier CSV source.
- Remplace toute séquence continue d’un ou plusieurs caractères `|` par une seule virgule `,`.
- Écrit le résultat dans un fichier de sortie.
- Convertit un fichier CSV séparé par des '|' en un fichier CSV classique, séparé par des ','

## Utilisation

### Compilation (pas nécessaire si un fichier nommé CREATE_ETIQUETTES existe déjà à la racine du projet)

make clean; make

### Execution
./FORMATE_BDD fichier_entree.csv fichier_sortie.csv
