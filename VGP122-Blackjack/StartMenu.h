#ifndef STARTMENU_H
#define STARTMENU_H

#include "Definitions.h"

class StartMenu
{
public:
	static void ShowStartMenu(SDL_Renderer* renderer);

private:
	Sprite*			menu_background = NULL;
	Sprite*			btnStart = NULL;
};
#endif // !STARTMENU_H

