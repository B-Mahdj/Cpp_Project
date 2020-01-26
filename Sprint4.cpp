/*Cartouche du programme
Nom : Source du projet SDA sur le ruban de Mobius
Auteur : Mahdjoubi Bilal & Ganderatz Florian
Date de création : 23/12/2019
*/

#include <iostream>
#include "Struct.h"
using namespace std;

int main() {
	Tableau2D tableau1, tableau2;
	unsigned int nb_colonnes, nb_lignes;
	cin >> nb_colonnes;
	cin >> nb_lignes;
	tableau1 = initialiser(nb_colonnes, nb_lignes);
	tableau2 = initialiser(nb_colonnes, nb_lignes);

	LabyrintheMb labyrinthe;
	labyrinthe = initialiser(tableau1, tableau2);
	Liste liste;
	initialiser(liste, labyrinthe);
	missionDragonSp4(labyrinthe, liste);
	afficherSp4(labyrinthe, liste);
	detruire(labyrinthe);
	detruire(liste);
}

