#include "Interface.h"
#include <iostream>

using namespace std;

void Interface::spacing(int n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << "-";
	}
}
