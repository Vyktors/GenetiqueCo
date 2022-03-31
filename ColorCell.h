#pragma once
#include <iostream>
#include "Arbre.h"

class ColorCell
{
public:
	ColorCell();
	ColorCell(int);
	ColorCell(int _id, int _r, int _g, int _b);
	ColorCell(const ColorCell&);
	~ColorCell() {};
	friend ostream& operator<<(ostream& flux, ColorCell& individu);

	int Moyenne(int n1, int n2) { return ((n1 + n2) / 2); };
	int getId();
	int* getRGB();
	int getRGB(int);
	void setId(int);
	
	friend ColorCell operator+(const ColorCell&, const ColorCell&);
	
	ColorCell& operator=(const ColorCell& copied);

private:
	int id;
	int rgb[3] = {0, 0, 0};
};


inline ColorCell operator+(const ColorCell& c1, const ColorCell& c2)
{
	int r = (c1.rgb[0] + c2.rgb[0])/ 2;
	int g = (c1.rgb[1] + c2.rgb[1])/ 2;
	int b = (c1.rgb[2] + c2.rgb[2])/ 2;


	return ColorCell(-1, r, g, b);
}

inline ostream& operator<<(ostream& flux, ColorCell& individu)
{

	flux << individu.getId() << " : [" << individu.getRGB(0) << "," << individu.getRGB(1) << "," << individu.getRGB(2) << "]";
	return flux;
}