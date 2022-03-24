#pragma once
#include "Arbre.h"

class IndividuColor
{
public:
	IndividuColor();
	IndividuColor(int);
	~IndividuColor() {};

	friend ostream& operator<<(ostream& flux, IndividuColor& individu);

	int getId();

private:
	int id;
	Arbre<IndividuColor> famille;
	int rgb[3] = {};
};


inline ostream& operator<<(ostream& flux, IndividuColor& individu)
{
	flux << individu.getId();
	return flux;
}