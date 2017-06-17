#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <string>
#include "Position.h"
#include "Size.h"

using namespace std;

struct Textbox
{
	string name{ "" };
	Position position{ 0, 0 };
	Size size{ 0, 0 };
	string value{ "" };
};

#endif // !TEXTBOX_H

