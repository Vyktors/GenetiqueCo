#include "ColorCell.h"

ColorCell::ColorCell()
{
	id = -1;
}

ColorCell::ColorCell(int _id)
{
	id = _id;
}

ColorCell::ColorCell(int _id, int _r, int _g, int _b)
{
	id = _id;
	rgb[0] = _r;
	rgb[1] = _g;
	rgb[2] = _b;
}

ColorCell::ColorCell(const ColorCell& copied)
{
	id = copied.id;
	rgb[0] = copied.rgb[0];
	rgb[1] = copied.rgb[1];
	rgb[2] = copied.rgb[2];
}

ColorCell& ColorCell::operator=(const ColorCell& copied)
{
	id = copied.id;
	rgb[0] = copied.rgb[0];
	rgb[1] = copied.rgb[1];
	rgb[2] = copied.rgb[2];
	return *this;
}

bool ColorCell::operator==(const ColorCell& compared) const
{
	
	return id == compared.id;
}

int ColorCell::getId()
{
 	return id;
}

int * ColorCell::getRGB()
{
	return rgb;
}

int ColorCell::getRGB(int i)
{
	return rgb[i];
}

void ColorCell::setId(int _id)
{
	id = _id;
}



