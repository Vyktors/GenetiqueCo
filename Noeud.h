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
	Noeud(const Noeud<TType>&);
	~Noeud();

	Noeud<TType>& operator=(const Noeud<TType>& copied);

	//Fonctions
	void AjouterEnfants( Noeud* _enfant1, Noeud* _enfant2);
	void AjouterEnfantGauche( Noeud* _enfant);
	void AjouterEnfantDroite( Noeud* _enfant);
	void AfficherArbo(int);
	bool estFeuille();
	bool EnfantGaucheNull();
	bool EnfantDroiteNull();

	//Accesseurs
	Noeud<TType>& getEnfantGauche();
	Noeud<TType>& getEnfantDroite();
	TType& getInfo();


private:
	TType info;
	Noeud<TType>* enfantGauche;
	Noeud<TType>* enfantDroite;
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
	enfantDroite = enfantGauche = nullptr;
}

template<typename TType> inline
Noeud<TType>::Noeud(const TType& _info) {
	enfantDroite = enfantGauche = nullptr;
	info = _info;
}

template<typename TType>
inline Noeud<TType>::Noeud(const Noeud<TType>& copied)
{
	this->enfantDroite = copied.enfantDroite;
	this->enfantGauche = copied.enfantGauche;
	this->info = copied.info;
}

template<typename TType> inline
Noeud<TType>::~Noeud() {
	//TODO
}

template<typename TType>
inline Noeud<TType>& Noeud<TType>::operator=(const Noeud<TType>& copied)
{
	this->enfantDroite = copied.enfantDroite;
	this->enfantGauche = copied.enfantGauche;
	this->info = copied.info;
	return *this;
}

template<typename TType>
inline void Noeud<TType>::AjouterEnfants( Noeud* _enfant1,  Noeud* _enfant2)
{
	AjouterEnfantGauche(_enfant1);
	AjouterEnfantDroite(_enfant2);
}

template<typename TType>
inline void Noeud<TType>::AjouterEnfantGauche( Noeud* _enfant)
{
	this->enfantGauche = _enfant;
}

template<typename TType>
inline void Noeud<TType>::AjouterEnfantDroite( Noeud* _enfant)
{
	this->enfantDroite = _enfant;
}

template<typename TType>
inline void Noeud<TType>::AfficherArbo(int index)
{
	Interface::spacing(index);
	TType t = getInfo();
	cout << t << endl;

	if (!estFeuille()) {
		
		if (!EnfantGaucheNull()) {
			Noeud<TType> enfant1 = getEnfantGauche();
			Interface::spacing(index + 1);
			enfant1.AfficherArbo(index + 1);
		}
		
		if (!EnfantDroiteNull()) {
			Noeud<TType> enfant2 = getEnfantDroite();
			Interface::spacing(index + 1);
			enfant2.AfficherArbo(index + 1);
		}
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
inline bool Noeud<TType>::EnfantGaucheNull()
{
	return (enfantGauche == nullptr);
}

template<typename TType>
inline bool Noeud<TType>::EnfantDroiteNull()
{
	return (enfantDroite == nullptr);
}



template<typename TType>
 Noeud<TType>& Noeud<TType>::getEnfantGauche()
{
	return *(this->enfantGauche);	
}

template<typename TType>
 Noeud<TType>& Noeud<TType>::getEnfantDroite()
{
	return *(this->enfantDroite);
}

template<typename TType>
 TType& Noeud<TType>::getInfo()
{
	return this->info;
}


