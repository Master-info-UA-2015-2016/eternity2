# Eternity2

Application graphique développée avec les librairies Qt 5.5 ayant pour but
de supporter le projet à effectuer au cours de l'option **Résolutions de
problèmes**" suivie en 1ère année de Master à l'Université d'Angers.

- - -

Projet collaboratif à l'initiative de :
 * [Ugo Rayer](https://github.com/Seymour49) -  Abandon

Contributeurs :
* [Florian David](https://github.com/Flodavid)
* [Jerôme Fourmond](https://github.com/jfourmond)
* [Antoine Garnier](https://github.com/Ascris)

- - -

## Présentation du projet

Le projet a pour but de mettre en place différents algorithmes de recherche
de solutions approchées à plusieurs instances de puzzle eternity et de comparer
leurs efficacités.
Afin de mieux cerner la typologie d'un puzzle eternity, nous développons cette
interface graphique permettant de charger une instance d'un puzzle mais également
de charger/sauvegarder une configuration.
De plus, un système permettant de construire sa propre configuration après chargement
d'une instance est à l'étude.

A terme, cette application devra permettre, à partir d'une instance chargée, de
choisir l'algorithme à utiliser afin d'effectuer la recherche de la solution approchée
tout en affichant à l'écran la solution optimale courante et l'évolution de l'éxecution
de l'algorithme.

##	Les algorithmes

### La recherche locale

En se basant sur les détails manuscrits du fichier [recherche_locale.txt](https://github.com/flodavid/eternity2/blob/master/recherche_locale.txt), la recherche locale du programme se déroule ainsi :
	* Une Configuration initiale est créée aléatoirement (aléatoirement signifiant que les pièces de coins et de bordures sont tout de même placés de façon à respecter leurs contraintes, aucune adjacence n'est pour l'instant travaillée)
	* Le critère d'arrêt est ici le nombre d'évaluation de voisins depuis que la dernière meilleure solution a été rencontrée
	* La fonction d'évaluation retourne le nombre d'erreurs de la Configuration, il faut donc minimiser cette dernière
	* La fonction de voisinage correspond à la *création* d'un voisin en pivotant une pièce _aléatoire_ _aléatoirement_.

## TO DO
* ~~(Modélisation)~~
* ~~(Interface graphique)~~
* Implémentation des algorithmes
