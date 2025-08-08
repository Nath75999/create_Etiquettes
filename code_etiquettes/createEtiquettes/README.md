# Préparateur d'étiquettes à partir d'une base de données CSV

Ce programme crée des images (.png) à partir d'une base de données (.csv) contenant au maximum 21 étiquettes pour impression. Les images seront stockées dans un dossier result. Il est possible que des images temporaires soient créées à la racine de ce projet. Elles sont inutiles et peuvent être supprimées.

## Fonctionnalités

- Lit un fichier CSV source.
- Crée une image PNG vide.
- Lit maximum 21 lignes du fichier CSV.
- Rajoute maximum 21 id et 21 noms du fichier CSV dans l'image.
- Et recommence jusqu'à ce que le fichier CSV soit vide.

## Utilisation

### Compilation (pas nécessaire si un fichier nommé CREATE_ETIQUETTES existe déjà à la racine du projet)
make clean; make

### Execution
./CREATE_ETIQUETTES

### NOTE IMPORTANTE:
Les caractères non compris dans la table ascii de base (pas d'accents ou de caractères spéciaux) ont été remplacé par '_'.
