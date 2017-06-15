#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "Common.h"
#include "Sprite.h"
#include "Card.h"

using namespace std;

class GameRender {
public:	
	struct Component
	{
		string name { "" };
		SDL_Texture* texture { nullptr };
		Position position { 0, 0 };
	};
	
	static int Initialize(string gameFont, int fontSize);

	static void SetBackground(string backgroundImagePath);

	static void SetMusic(string musicPath);

	static void DrawBackground();

	static void DrawElement(string filename, int xPos, int yPos, int width, int height, Sprite** elementPtr, string saveName = "");

	static void DrawElement(Sprite* image, Position position);

	static void DrawElement(Component* c);

	static void DrawElement(Button* button);

	static void DrawElement(Card* card, Position position);

	//static void PrintText(Textbox* textbox, SDL_Surface** surface, SDL_Texture** texture);

	static void PrintText(Textbox* textbox, bool save = false);

	static void PlaySound(string sfxPath, int loops = 0);

	static void ClearScreen(bool keepSavedItems = false);

	static void SaveComponent(string name, SDL_Texture* texture, Position position);

	static void Finish();

	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 720;

	static const int AUDIO_RATE = 44100;
	static const Uint16 AUDIO_FORMAT = AUDIO_S16;
	static const int AUDIO_CHANNELS = 2;
	static const int AUDIO_BUFFERS = 2048;

	static SDL_Window* window; // the window for the project
	static SDL_Renderer* renderer; // the renderer to use in that window
	static Sprite* background;

	static TTF_Font* font; // the font we'll use throughout the game

	static Mix_Music* music; // the music listener to be used throughout the game
};

#endif

