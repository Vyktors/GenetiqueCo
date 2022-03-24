#pragma once
#include <iostream>
#include "Noeud.h"

template<typename TType>
class Arbre
{
public :
	Arbre();							//Constructeur
	Arbre(Noeud<TType>&);				//Constructeur avec paramètre
	Arbre(const Arbre<TType>& copied);	//Constructeur par copie TODO
	~Arbre();							//Destructeur TODO

	void Afficher();
	bool estVide();
	Noeud<TType> elementCourant();
	Noeud<TType> elementRacine();

private :
	int hauteur;						//Hauteur de l'arbre
	Noeud<TType>* courant;				//Noeud Courant
	Noeud<TType>* racine;				//Noeud Racine
};

template<typename TType>
inline ostream& operator<<(ostream& flux, Arbre<TType>& arbre)
{
	if (!arbre.estVide()) {
		Noeud<TType> n = arbre.elementCourant();
		flux << n;
		return flux;
	}
}

//Constructeur
template<typename TType>
inline Arbre<TType>::Arbre()
{
	courant = racine = nullptr;
	hauteur = 0;
}

template<typename TType>
inline Arbre<TType>::Arbre(Noeud<TType>& element)
{
	courant = racine = &element;
	hauteur = 1;
}

template<typename TType>
inline Arbre<TType>::Arbre(const Arbre<TType>& copied)
{
}

template<typename TType>
inline Arbre<TType>::~Arbre()
{

}

template<typename TType>
inline void Arbre<TType>::Afficher()
{
	racine->AfficherArbo(0);
}

template<typename TType>
inline bool Arbre<TType>::estVide()
{
	return hauteur == 0;
}

template<typename TType>
Noeud<TType> Arbre<TType>::elementCourant()
{
	return *(this->courant);
}

template<typename TType>
inline Noeud<TType> Arbre<TType>::elementRacine()
{
	return *(this->racine);
}


