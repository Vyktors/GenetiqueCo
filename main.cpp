/*                 Présentation du Devoir 2                     */
/*--------------------------------------------------------------*/
/* Réalisé par :   Mathieu Victor Guérin                        */
/*									                            */
/* -------------------------------------------------------------*/
/* Date de remise : 1 avril 2022                                */
/*--------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Noeud.h"
#include "ColorCell.h"
#include "Centre.h"
#include "Interface.h"

using namespace std;

Centre<ColorCell>* centreCourant;
Centre<ColorCell> centreColor;
Centre<ColorCell> centreChromo;

void gereChoix(string);
void viderFichier(string nomFichier);
void lireFichierPopulation(string _nomFichier);
void enregistreFichierPopulation(string _nomFichier);
void populerColorCell(string line);
void ajouterColorCell(string);
void comparerAncetre(string);

int main() {

	centreCourant = &centreColor;

	setlocale(LC_CTYPE, "Fr-FR");
	cout << "Bienvenue au centre scientifique de genetique! " << endl;

	while (true) {
		cout << "Voulez vous entrer des transactions " << endl;
		cout << setw(10) << "A  " << "MANUEL" << endl;
		cout << setw(10) << "B  " << "À PARTIR D'UN FICHIER" << endl;
		string choix, instruction;
		cout << "Choix (A ou B) : ";
		getline(cin, choix);

		if (choix == "A") {
			while (true) {
				cout << "Entrez une operation : ";
				getline(cin, instruction);
				if (instruction == "Q" || instruction == "exit") {
					break;
				}
				gereChoix(instruction);
				cout << endl;
			}
		}
		else if (choix == "B") {
			string NomFichier;
			ifstream FicEntree;

			while (true) {
				cout << "Entrez un fichier opération: ";
				getline(cin, NomFichier);
				if (NomFichier == "Q" || NomFichier == "exit") {
					break;
				}
				FicEntree.open(NomFichier, ios::in);
				if (!FicEntree)
				{
					cout << "Erreur de lecture du fichier des operation";
					FicEntree.close();
				}
				else
				{
					centreColor.listType.clear();
					centreColor.index = 0;
					centreChromo.listType.clear();
					centreChromo.index = 0;

					while (!FicEntree.eof())
					{
						getline(FicEntree, instruction);
						gereChoix(instruction);
						cout << endl;
					}
					FicEntree.close();
				}
			}
		}
		else {
			cout << "Choisissez entre A et B!";
		}

	}

	system("pause");

	return 0;
}

// Action que le programme doit faire en fonction des actions du fichier texte des opérations
void gereChoix(string s)
{
	char operation = s.substr(0, s.find(" "))[0];
	s.erase(0, 2);
	switch (operation)
	{
	case 'C': //Créer une population vide de type « TYPE »
		if (s == "COLORCELL") {
			centreCourant = &centreColor;
			cout << "Ajout d'une population vide de type " << s << endl;
		}
		else {
			cout << "Pas trouver de cellule de type '" << s << "' " << endl;
		}
		break;
	case 'A'://Ajoute à la population courante un individu sans parent de type « TYPE » ayant les valeurs « VALEURS »
		if (centreCourant == &centreColor) {
			ajouterColorCell(s);
		}
		else {
			cout << "Pas trouver de cellule de type '" << s << "' " << endl;
		}
		break;
	case 'O'://charge en mémoire la population du fichier « POPULATION ».
		lireFichierPopulation(s);
		break;
	case 'S'://enregistre la population dans le fichier « POPULATION ».
		enregistreFichierPopulation(s);
		break;
	case '+'://Génère « NB » individues à partir de la population courante
		try {
			for (size_t i = 0; i < stoi(s); i++)
			{
				centreCourant->GenererNewCell(++centreCourant->index);
			}
		}
		catch(...) {
			cout << "il faut un nombre!" << endl;
		}
		
		break;
	case '-'://Supprime l’individu X de la population courante. Ses enfants auront maintenant un parent inconnu
		centreCourant->SupprimerCell(stoi(s));
		break;
	case '?'://Trouve un ancêtre commun entre deux individus et l’affiche. Indique également le	nombre de génération qui sépare les deux individus
		comparerAncetre(s);
		break;
	case '$'://Afficher l’arbre génétique complet de l’individu « X », incluant ses caractéristiques.
		centreCourant->FindCellByID(stoi(s))->AfficherArbo(0);
		break;
	case 'X'://Affiche centre courant
		centreCourant->AfficherListe();
		break;
	default:
		cout << "Ceci n'est pas une commande" << endl;
		break;
	}
}

void lireFichierPopulation(string _nomFichier)
{
	ifstream entree;
	entree.open(_nomFichier, ios::in);
	if (entree)
	{
		string type, line;
		int nbr;

		entree >> type;
		entree >> nbr;
		getline(entree, line);
		if (type == "COLORCELL") {
			centreColor.listType.clear();
			centreColor.index = nbr;
			for (size_t i = 0; i < nbr; i++)
			{
				centreCourant = &centreColor;
				getline(entree, line);

				populerColorCell(line);
			}
		}
		else {
			cout << "Pas trouver de cellule de type '" << type << "' " << endl;
		}

	}
	else {
		cout << "pas trouver de fichier avec ce nom " << _nomFichier << endl;
	}
	entree.close();
}

void enregistreFichierPopulation(string _nomFichier)
{
	viderFichier(_nomFichier);

	ofstream sortie;
	sortie.open(_nomFichier, ios::out);
	if (sortie) {
		//Imprimer client
		
		sortie << "COLORCELL" << " " << centreCourant->index << endl;

		string id, p1, p2, r, g, b;

		for (size_t i = 0; i < centreCourant->listType.size(); i++)
		{
			id = to_string(centreCourant->listType[i]->getInfo().getId());
			if(centreCourant->listType[i]->estFeuille()) {
				p1 = "/";
				p2 = "/";
			}
			else {
				p1 = to_string(centreCourant->listType[i]->getEnfantGauche().getInfo().getId());
				p2 = to_string(centreCourant->listType[i]->getEnfantDroite().getInfo().getId());
			}
			r = to_string(centreCourant->listType[i]->getInfo().getRGB(0));
			g = to_string(centreCourant->listType[i]->getInfo().getRGB(1));
			b = to_string(centreCourant->listType[i]->getInfo().getRGB(2));

			sortie << id << " " << p1 << " " << p2 << " " << r << " " << g << " " << b << endl;
		}
	}
	else {
		cout << "pas trouver de fichier avec ce nom " << _nomFichier << endl;
	}
	sortie.close();
}

void populerColorCell(string line)
{
	size_t pos = 0;
	string token, p1, p2;
	int id, r, g, b;

	for (size_t i = 0; i < 6; i++)
	{
		pos = line.find(" ");
		token = line.substr(0, pos);

		switch (i)
		{
		case 0:
			id = stoi(token);
			break;
		case 1:
			p1 = token;
			break;
		case 2:
			p2 = token;
			break;
		case 3:
			r = stoi(token);
			break;
		case 4:
			g = stoi(token);
			break;
		case 5:
			b = stoi(token);
			break;
		default:
			break;
		}
		line.erase(0, pos + 1);
	}

	Noeud<ColorCell>* tempCell = new Noeud<ColorCell>(ColorCell(id, r, g, b));

	if (p1 == "/" && p2 == "/") {
		tempCell->AjouterEnfants(nullptr, nullptr);
	}
	else if (p1 == "/") {
		tempCell->AjouterEnfants(nullptr, centreColor.FindCellByID(stoi(p2)));
	}
	else if (p2 == "/") {
		tempCell->AjouterEnfants(centreColor.FindCellByID(stoi(p1)), nullptr);
	}
	else {
		tempCell->AjouterEnfants(centreColor.FindCellByID(stoi(p1)), centreColor.FindCellByID(stoi(p2)));
	}

	centreColor.AjouterCell(tempCell);
}


void ajouterColorCell(string line) {
	size_t pos = 0;
	string type, token, p1, p2;
	int r, g, b;

	for (size_t i = 0; i < 4; i++)
	{
		pos = line.find(" ");
		token = line.substr(0, pos);

		switch (i)
		{
		case 0:
			type = token;
			break;
		case 1:
			r = stoi(token);
			break;
		case 2:
			g = stoi(token);
			break;
		case 3:
			b = stoi(token);
			break;
		default:
			break;
		}
		line.erase(0, pos + 1);
	}

	Noeud<ColorCell>* tempCell = new Noeud<ColorCell>(ColorCell(++centreColor.index, r, g, b));
	cout << setw(30) << "Ajout d'une cellule COLORCELL [" << *tempCell << "]" << endl;
	centreColor.AjouterCell(tempCell);
}


void viderFichier(string nomFichier) {
	std::ofstream ofs;
	ofs.open("nomFichier", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
}

void comparerAncetre(string line) {
	size_t pos = 0;
	string token;
	int id1, id2;

	for (size_t i = 0; i < 2; i++)
	{
		pos = line.find(" ");
		token = line.substr(0, pos);

		switch (i)
		{
		case 0:
			id1 = stoi(token);
			break;
		case 1:
			id2 = stoi(token);
			break;
		default:
			break;
		}
		line.erase(0, pos + 1);
	}

	int index1 = centreCourant->FindIndexCellByID(id1);
	int index2 = centreCourant->FindIndexCellByID(id2);

	if (centreCourant->listType[index1] != nullptr && centreCourant->listType[index2] != nullptr) {
		centreCourant->listType[index1]->CompareAncetre(0, centreCourant->listType[index2]);
	}
	
}