#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "Position.h"
#include "Size.h"
#include "Sprite.h"

using namespace std;

struct Button
{
	string name { "" };
	Position position { 0, 0 };
	Size size { 0, 0 };
	string src { "" };
	Sprite* image { nullptr };
	string sfxSrc { "" };
	Size tooltipSize { 0, 0 };
	string tooltipSrc { "" };
	Sprite* tooltip { nullptr };
};

#endif // !BUTTON_H
