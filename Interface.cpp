#include "Interface.h"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

void Interface::spacing(int n)
{
	for (size_t i = 0; i < n; i++)
	{
		cout << "-";
	}
}

void Interface::endl()
{
	cout << endl;
}

void Interface::seperationLine()
{
	cout << "---------------------------" << endl;
}


