#include "StartMenu.h"

static void StartMenu::ShowStartMenu(SDL_Renderer* renderer)
{
	menu_background = new Sprite("Images/Pong_MainMenu.bmp", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
	btnStart = new Sprite("Images/Pong_MenuOp1.bmp", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 387, 50, renderer);

	menu_background->draw(renderer);
	btnStart->draw(renderer);

	SDL_RenderPresent(renderer);
}
