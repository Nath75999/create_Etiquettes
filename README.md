# GENERATEUR D'ETIQUETTES A PARTIR D'UNE BASE DE DONNEES EN FORMAT CSV
Ce projet permet, à partir d'une base de données exportée d'un logiciel de tri des jeux d'une ludothèque, créer
des images PNG contenant des étiquettes avec un logo (commun à toutes les étiquettes), l'id et le nom de jeu dans la base.
Ce projet est décomposé en deux parties, selon les besoin dépendant de la base de données exportée.

## SI LA SEPARATION DU FICHIER CSV EST '|' (CAS 1)
Il faut utiliser le code du dossier formateBDD pour modifier la base de données afin de pouvoir créer les étiquettes ensuite.

## DANS TOUS LES CAS (CAS 2)
Il faut utiliser le code du dossier createEtiquettes pour générer les images contenant chacune 21 étiquettes maximum.

### INSTRUCTIONS
Toutes les instructions nécessaires à l'éxecution du projet sont données dans les fichier README.md, situés dans les dossiers correspondants.
Il faut soit (cas 1) effectuer les instructions dans le dossier formateBDD puis les instructions dans le dossier createEtiquettes 
ou (cas 2) uniquement effectuer les instructions dans le dossier createEtiquettes.

### NOTE IMPORTANTE:
Les caractères non compris dans la table ascii de base (pas d'accents ou de caractères spéciaux) ont été remplacé par '_'.
