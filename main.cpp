
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "Noeud.h"
#include "Arbre.h"
#include "IndividuColor.h"

using namespace std;

int main() {

	cout << "Bienvenue au centre scientifique de genetique! " << endl;

	Noeud<int> n1(1);
	Noeud<int> n2(2);
	Noeud<int> n3(3);
	n3.AjouterEnfants(n1, n2);
	
	Noeud<int> n4(4);
	n4.AjouterEnfants(n3, n2);
	


	Arbre<int> a(n4);

	IndividuColor i(0);

	Noeud<IndividuColor> ni0 = i;


	cout << n4;
	n4.AfficherArbo(3);
	

	//a.Afficher();
	

}