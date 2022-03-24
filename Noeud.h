#pragma once
#include <iostream>
#include "Interface.h"

using namespace std;

template<typename TType>

class Noeud {
public:
	//Constructeurs
	Noeud();
	Noeud(const TType& _info);
	~Noeud();

	Noeud<TType>& operator=(const Noeud<TType>& copied);

	//Fonctions
	void AjouterEnfants(Noeud& _enfant1, Noeud& _enfant2);
	void AjouterEnfantGauche( Noeud& _enfant);
	void AjouterEnfantDroite( Noeud& _enfant);
	void AfficherArbo(int);
	bool estFeuille();

	//Accesseurs
	Noeud<TType> getEnfantGauche();
	Noeud<TType> getEnfantDroite();
	TType getInfo();


private:
	TType info;
	Noeud<TType>* enfantGauche;
	Noeud<TType>* enfantDroite;
	Noeud<TType>* parent;
};

template<typename TType>
inline ostream& operator<<(ostream& flux, Noeud<TType>& element)
{
	TType info = element.getInfo();
	flux << info << endl;
	return flux;
}

template<typename TType> inline
Noeud<TType>::Noeud() {
	enfantDroite = enfantGauche = parent = nullptr;
}

template<typename TType> inline
Noeud<TType>::Noeud(const TType& _info) {
	enfantDroite = enfantGauche = parent = nullptr;
	info = _info;
}

template<typename TType> inline
Noeud<TType>::~Noeud() {

}

template<typename TType>
inline Noeud<TType>& Noeud<TType>::operator=(const Noeud<TType>& copied)
{
	enfantDroite = copied.enfantDroite;
	enfantGauche = copied.enfantGauche;
	parent = copied.parent;
	info = copied.info;
}

template<typename TType>
inline void Noeud<TType>::AjouterEnfants(Noeud& _enfant1, Noeud& _enfant2)
{
	AjouterEnfantGauche(_enfant1);
	AjouterEnfantDroite(_enfant2);
}

template<typename TType>
inline void Noeud<TType>::AjouterEnfantGauche(Noeud& _enfant)
{
	this->enfantGauche = &_enfant;
}

template<typename TType>
inline void Noeud<TType>::AjouterEnfantDroite(Noeud& _enfant)
{
	this->enfantDroite = &_enfant;
}

template<typename TType>
inline void Noeud<TType>::AfficherArbo(int index)
{
	Interface::spacing(index);
	cout << getInfo() << endl;

	if (!estFeuille()) {
		Noeud<TType> nGauche = getEnfantGauche();
		Noeud<TType> nDroite = getEnfantDroite();

		Interface::spacing(index);
		nGauche.AfficherArbo(index + 1);

		Interface::spacing(index);
		nDroite.AfficherArbo(index + 1);
	}
	else {
	}

}



template<typename TType>
inline bool Noeud<TType>::estFeuille()
{
	return (enfantDroite == nullptr && enfantGauche == nullptr);
}

template<typename TType>
inline Noeud<TType> Noeud<TType>::getEnfantGauche()
{
	return *(this->enfantGauche);
}

template<typename TType>
inline Noeud<TType> Noeud<TType>::getEnfantDroite()
{
	return *(this->enfantDroite);
}

template<typename TType>
inline TType Noeud<TType>::getInfo()
{
	return this->info;
}

