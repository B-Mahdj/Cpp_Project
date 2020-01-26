#include <iostream>
using namespace std;
#include "Struct.h"
#include <cassert>

const unsigned int D_ASCII = 68;
const unsigned int P_ASCII = 80;
const unsigned int PLUS_ASCII = 43;
const unsigned int C_ASCII = 67;
const unsigned int VINGT = 20;

Tableau2D initialiser(unsigned int nb_colonnes, unsigned int nb_lignes) {
	Tableau2D tab;
	tab.nb_colonnes = nb_colonnes;
	tab.nb_lignes = nb_lignes;
	tab.tableau = new ItemMb * [tab.nb_lignes];
	for (unsigned int i = 0; i < tab.nb_lignes; i++) {
		tab.tableau[i] = new ItemMb[tab.nb_colonnes];
	}
	return tab;
};


void detruire(Tableau2D tab) {
	for (unsigned int i = 0; i < tab.nb_lignes; i++) {
		delete[] tab.tableau[i];
	}
	delete[] tab.tableau;
	for (unsigned int i = 0; i < tab.nb_lignes; ++i) {
		tab.tableau[i] = NULL;
	}
	tab.tableau = NULL;
}

LabyrintheMb initialiser(Tableau2D tab1, Tableau2D tab2) {
	for (unsigned int i = 0; i < tab1.nb_lignes; ++i) {
		for (unsigned int z = 0; z < tab1.nb_colonnes; ++z) {
			cin >> tab1.tableau[i][z];
		}
	}
	for (unsigned int i = 0; i < tab2.nb_lignes; ++i) {
		for (unsigned int z = 0; z < tab2.nb_colonnes; ++z) {
			cin >> tab2.tableau[i][z];
		}
	}
	LabyrintheMb lab;
	lab.tableau1 = tab1;
	lab.tableau2 = tab2;
	return lab;
}

void detruire(LabyrintheMb lab) {
	detruire(lab.tableau1);
	detruire(lab.tableau2);
}

void afficher(LabyrintheMb lab) {
	cout << lab.tableau1.nb_colonnes << " " << lab.tableau1.nb_lignes;
	for (unsigned int i = 0; i < lab.tableau1.nb_lignes; ++i) {
		cout << endl;
		for (unsigned int z = 0; z < lab.tableau1.nb_colonnes; ++z) {
			cout << lab.tableau1.tableau[i][z];
		}
	}

	cout << endl;

	for (unsigned int i = 0; i < lab.tableau2.nb_lignes; ++i) {
		cout << endl;
		for (unsigned int z = 0; z < lab.tableau2.nb_colonnes; ++z) {
			cout << lab.tableau2.tableau[i][z];
		}
	}

	cout << endl;
}

void afficherSp4(LabyrintheMb lab, Liste liste) {
	while (!estVide(liste)) {
		IndexPositionMb tmp = lire(liste, liste.nb);
		supprimer_sommet(liste);
		if (tmp.face == 0) {
			lab.tableau1.tableau[tmp.n_ligne][tmp.n_colonne] = C_ASCII;
		}
		else if (tmp.face == 1) {
			lab.tableau2.tableau[tmp.n_ligne][tmp.n_colonne] = C_ASCII;
		}
	}

	afficher(lab);
}

void initialiser(Pile& p, unsigned int colonnes, unsigned int lignes) {
	p.capacite = colonnes * lignes;
	p.tableau = new IndexPositionMb[colonnes * lignes];
	p.sommet = -1;
}

bool estPleine(const Pile& p) {
	return (p.sommet == (p.capacite - 1));
}

bool estVide(const Pile& p) {
	return (p.sommet == -1);
}

void empiler(Pile& p, const IndexPositionMb it) {
	assert(!estPleine(p));
	p.sommet++;
	p.tableau[p.sommet] = it;
}

void depiler(Pile& p) {
	assert(!estVide(p));
	p.sommet--;
}

IndexPositionMb sommet(const Pile& p) {
	assert(!estVide(p));
	return p.tableau[p.sommet];
}

void detruire(Pile& p) {
	delete[] p.tableau;
	p.tableau = NULL;
}

bool trouver_objet_lab(IndexPositionMb pos, LabyrintheMb lab, 
	unsigned int objet) {
	if (pos.face == 0) {
		if (lab.tableau1.tableau[pos.n_ligne][pos.n_colonne] == objet) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (pos.face == 1) {
		if (lab.tableau2.tableau[pos.n_ligne][pos.n_colonne] == objet) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

Carre initialiser(IndexPositionMb pos, LabyrintheMb lab) {
	Carre Car;
	for (unsigned int i = 0; i < NB_CASES_CARRE; ++i) {
		Car.cases[i] = pos;
	}
	Car.cases[1].n_colonne--;
	Car.cases[2].n_colonne--;
	Car.cases[2].n_ligne++;
	Car.cases[3].n_ligne++;
	Car.cases[4].n_colonne++;
	Car.cases[4].n_ligne++;
	Car.cases[5].n_colonne++;
	Car.cases[6].n_colonne++;
	Car.cases[6].n_ligne--;
	Car.cases[7].n_ligne--;
	Car.cases[8].n_colonne--;
	Car.cases[8].n_ligne--;
	if (Car.cases[0].n_colonne == 0) {
		Car.cases[1].n_colonne = lab.tableau1.nb_colonnes - 1;
		Car.cases[2].n_colonne = lab.tableau1.nb_colonnes - 1;
		Car.cases[8].n_colonne = lab.tableau1.nb_colonnes - 1;
		if (Car.cases[0].face == 0) {
			Car.cases[1].face = 1;
			Car.cases[2].face = 1;
			Car.cases[8].face = 1;
		}
		else {
			Car.cases[1].face = 0;
			Car.cases[2].face = 0;
			Car.cases[8].face = 0;
		}
	}
	if (Car.cases[0].n_colonne == lab.tableau1.nb_colonnes - 1) {
		Car.cases[4].n_colonne = 0;
		Car.cases[5].n_colonne = 0;
		Car.cases[6].n_colonne = 0;
		if (Car.cases[0].face == 0) {
			Car.cases[4].face = 1;
			Car.cases[5].face = 1;
			Car.cases[6].face = 1;
		}
		else {
			Car.cases[4].face = 0;
			Car.cases[5].face = 0;
			Car.cases[6].face = 0;
		}
	}
	return Car;
}

void initialiser(Liste& l, LabyrintheMb lab){
	l.nb = -1;
	l.tab = new IndexPositionMb[lab.tableau1.nb_colonnes * 
		lab.tableau1.nb_lignes];
}

void detruire(Liste& l) {
	delete[]l.tab;
}

IndexPositionMb lire(Liste& l, unsigned int pos) {
	return l.tab[pos];
}

void ecrire_sommet(Liste& l, const IndexPositionMb it){
	l.nb++;
	l.tab[l.nb] = it;
}

void supprimer_sommet(Liste& l) {
	l.nb--;
}

bool estVide(Liste& l) {
	if (l.nb < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

bool estConnexe(IndexPositionMb pos_file, IndexPositionMb pos, 
	LabyrintheMb lab) {
	Carre Car = initialiser(pos_file, lab);
	for (unsigned int i = 1; i < NB_CASES_CARRE; ++i) {
		if (pos.face == Car.cases[i].face && 
			pos.n_colonne == Car.cases[i].n_colonne&&
			pos.n_ligne == Car.cases[i].n_ligne) {
			return 1;
		}
	}
	return 0;
}

bool case_visitee(Liste l,IndexPositionMb pos) {
	for (int i = l.nb; i >= 0; --i) {
		if (pos.face == l.tab[i].face &&
			pos.n_ligne == l.tab[i].n_ligne &&
			pos.n_colonne == l.tab[i].n_colonne) {
			return 1;
		}
	}
	return 0;
}

IndexPositionMb trouver_dragon(LabyrintheMb lab) {
	IndexPositionMb pos;
	for (unsigned int i = 0; i < lab.tableau1.nb_lignes; ++i) {
		for (unsigned int z = 0; z < lab.tableau1.nb_colonnes; ++z) {
			if (lab.tableau1.tableau[i][z] == D_ASCII) {
				pos.n_ligne = i;
				pos.n_colonne = z;
				pos.face = 0;
			}
		}
	}
	for (unsigned int i = 0; i < lab.tableau2.nb_lignes; ++i) {
		for (unsigned int z = 0; z < lab.tableau2.nb_colonnes; ++z) {
			if (lab.tableau2.tableau[i][z] == D_ASCII) {
				pos.n_ligne = i;
				pos.n_colonne = z;
				pos.face = 1;
			}
		}
	}
	return pos;
}

void missionDragonSp4(LabyrintheMb lab, Liste& L) {
	Pile p;
	initialiser(p, lab.tableau1.nb_colonnes, lab.tableau1.nb_lignes);
	assert(estVide(p));
	IndexPositionMb pos = trouver_dragon(lab);
	empiler(p, pos);

	Liste liste_cases_visitee;
	initialiser(liste_cases_visitee, lab);
	unsigned int a = 0;
	while (!estVide(p) && !trouver_objet_lab(pos, lab, P_ASCII) && a<VINGT) {
		++a;
		pos = sommet(p);
		depiler(p);
		while (!estVide(L) && !estConnexe(L.tab[L.nb], pos, lab)) {
			supprimer_sommet(L);
		}
		ecrire_sommet(L, pos);
		if (!trouver_objet_lab(pos, lab, P_ASCII)) {
			ecrire_sommet(liste_cases_visitee, pos);
			Carre Car = initialiser(pos, lab);
			for (unsigned int i = 1; i < NB_CASES_CARRE; ++i) {
				if (Car.cases[i].n_colonne >= 0 && Car.cases[i].n_ligne >= 0) {
					if ((trouver_objet_lab(Car.cases[i], lab, PLUS_ASCII) ||
						trouver_objet_lab(Car.cases[i], lab, P_ASCII)) && 
						!case_visitee(liste_cases_visitee,Car.cases[i])) {
						empiler(p, Car.cases[i]);
					}
				}
			}
		}
	}
	detruire(p);
}

