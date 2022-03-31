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

	//Surcharge
	Noeud<TType>& operator=(const Noeud<TType>& copied);
	bool operator==(const Noeud<TType>&) const;

	//Fonctions
	void AjouterEnfants( Noeud* _enfant1, Noeud* _enfant2);
	void AjouterEnfantGauche( Noeud* _enfant);
	void AjouterEnfantDroite( Noeud* _enfant);
	void AfficherArbo(int);
	bool estFeuille();
	bool EnfantGaucheNull();
	bool EnfantDroiteNull();
	void CompareAncetre(int niveau, Noeud<TType>*);
	int CheckAncetre(int niveau, int niveauFound ,int _id);

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
inline bool Noeud<TType>::operator==(const Noeud<TType>& compared) const
{
	return (getInfo() == compared.getInfo());
	
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

template<typename TType>
void Noeud<TType>::CompareAncetre(int niveau, Noeud<TType>* compared)
{
	if (niveau > 0) {
		TType t = getInfo();

		int comparedNiveau = compared->CheckAncetre(0, 0, t.getId());

		if (comparedNiveau != 0) {
			double diff = abs(comparedNiveau - niveau);
			cout << "Ancêtre commun : ";

			cout << "[" << t << "] à " << diff << " génération de différence " << endl;
		}
	}

	if (!estFeuille()) {

		if (!EnfantGaucheNull()) {
			Noeud<TType> enfant1 = getEnfantGauche();
			enfant1.CompareAncetre(niveau + 1, compared);
		}

		if (!EnfantDroiteNull()) {
			Noeud<TType> enfant2 = getEnfantDroite();
			enfant2.CompareAncetre(niveau + 1, compared);
		}
	}
	else {
	}
}


template<typename TType>
int Noeud<TType>::CheckAncetre(int niveau, int niveauFound, int _id )
{
	TType t = getInfo();

	if (t == _id) {
		niveauFound = niveau;
	}

	if (!estFeuille()) {

		if (!EnfantGaucheNull()) {
			Noeud<TType> enfant1 = getEnfantGauche();
			niveauFound = enfant1.CheckAncetre(niveau + 1, niveauFound, _id );
		}

		if (!EnfantDroiteNull()) {
			Noeud<TType> enfant2 = getEnfantDroite();
			niveauFound = enfant2.CheckAncetre(niveau + 1, niveauFound, _id);
		}
	}
	else {
	}

	return niveauFound;
}


