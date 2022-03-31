#pragma once
#include <iostream>
#include "Arbre.h"

class Ancetre
{
public:
	Ancetre();
	Ancetre(int _id, int _niveau);
	~Ancetre() {};

	int niveau;
	int id;
};

inline Ancetre::Ancetre()
{
	niveau = 0;
	id = 0;
}

inline Ancetre::Ancetre(int _id, int _niveau)
{
	id = _id;
	niveau = _niveau;
}
