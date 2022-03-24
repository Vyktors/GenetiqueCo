#pragma once
#include <list>
#include "IndividuColor.h"

using namespace std;

class Centre
{
public:
	Centre();
	~Centre();
private:
	int index;
	list<IndividuColor> listIndividu;
};

