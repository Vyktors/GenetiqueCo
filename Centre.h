#pragma once
#include <vector>
#include <random>
#include "ColorCell.h"
#include "Interface.h"

using namespace std;


template<typename TType>
class Centre
{
public:
	Centre();
	Centre(const Centre<TType>&);
	~Centre();

	Centre<TType>& operator=(const Centre<TType>& copied);

	void GenererNewCell(int);
	void AjouterCell(Noeud<TType>*);
	void AfficherListe();
	Noeud<TType>* FindCellByID(int);
	int FindIndexCellByID(int);
	void SupprimerCell(int);

	vector<Noeud<TType>*> listType;
	int index;

private:
	
	
};
template<typename TType> inline
Centre<TType>::Centre()
{
	index = 0;
}

template<typename TType>
inline Centre<TType>::Centre(const Centre<TType>& copied)
{
	index = copied.index;
	for (size_t i = 0; i < copied.listType.size(); i++)
	{
		listType[i] = copied.listType[i];
	}
}

template<typename TType>
inline Centre<TType>::~Centre()
{
	/*for (size_t i = 0; i < listType.size(); i++)
	{
		delete listType[i];
	}*/
}

template<typename TType>
inline Centre<TType>& Centre<TType>::operator=(const Centre<TType>& copied)
{
	index = copied.index;
	for (size_t i = 0; i < copied.listType.size(); i++)
	{
		listType[i] = copied.listType[i];
	}
	return *this;
}

template<typename TType> inline
void Centre<TType>::GenererNewCell(int _id)
{
	if (listType.size() >= 2) {
		random_device rd;
		uniform_int_distribution<int> dist(0, listType.size() - 1);
		int indexP1; //Index Parent 1
		int indexP2; //Index Parent 2 différent

		do {
			indexP1 = dist(rd);
		} while (listType[indexP1] == nullptr);

		do {
			indexP2 = dist(rd);
		} while (indexP2 == indexP1 || listType[indexP2] == nullptr);

		
		Noeud<TType>* n = new Noeud<TType>((listType[indexP1])->getInfo() + (listType[indexP2])->getInfo());

		n->getInfo().setId(_id);
		

		n->AjouterEnfants(listType[indexP1], listType[indexP2]);

		cout << "Genere nouvelle cellule : [" << *n << "]" << endl;
		listType.push_back(n);					//Ajoute à la fin de la liste
	}
	else {
		cout << "La population n'est pas assez grande" << endl;
	}
}

template<typename TType>
inline void Centre<TType>::AjouterCell(Noeud<TType>* cell)
{
	listType.push_back(cell);
}

template<typename TType> inline
void Centre<TType>::AfficherListe()
{
	for (size_t i = 0; i < listType.size(); i++)
	{
		cout << "Individu " << i << " :" << endl;
		cout << "---------------------------" << endl;
		if (listType[i] != nullptr) {
			listType[i]->AfficherArbo(0);
		}
		else {
			cout << "La Cell n'existe plus" << endl;
		}
		
		cout << endl;
	}
}

template<typename TType>
inline Noeud<TType>* Centre<TType>::FindCellByID(int _id)
{

	for (size_t i = 0; i < listType.size(); i++)
	{
		if (listType[i] != nullptr && listType[i]->getInfo().getId() == _id) {
			return listType[i];
		}
	}
	return nullptr;
}

template<typename TType>
inline int Centre<TType>::FindIndexCellByID(int _id)
{
	for (size_t i = 0; i < listType.size(); i++)
	{
		if (listType[i] != nullptr && listType[i]->getInfo().getId() == _id) {
			return i;
		}
	}
	return -1;
}

template<typename TType>
inline void Centre<TType>::SupprimerCell(int _id)
{
	Noeud<TType>* noeudASupprimer = FindCellByID(_id);
	noeudASupprimer->AjouterEnfants(nullptr, nullptr);

	int indexDuNoeudASupprimer = FindIndexCellByID(_id);
	for (size_t i = 0; i < listType.size(); i++)
	{
		if (indexDuNoeudASupprimer == i) {
			listType[i] = nullptr;
		}
		else if(listType[i] != nullptr) {
			if (!listType[i]->EnfantGaucheNull() && listType[i]->getEnfantGauche().getInfo().getId() == _id) {
				listType[i]->AjouterEnfantGauche(nullptr);
			}
			if (!listType[i]->EnfantDroiteNull() && listType[i]->getEnfantDroite().getInfo().getId() == _id) {
				listType[i]->AjouterEnfantDroite(nullptr);
			}
		}
	}
	

	

	//delete noeudASupprimer;
}

