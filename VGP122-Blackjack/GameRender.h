#ifndef GAMERENDER_H
#define GAMERENDER_H

#include "Common.h"
#include "Sprite.h"

class GameRender {
public:	
	static int Initialize(string gameFont, int fontSize);

	static void SetBackground(string backgroundImagePath);

	static void SetMusic(string musicPath);

	static void DrawBackground();

	static void DrawElement(string filename, int xPos, int yPos, int width, int height, Sprite** elementPtr);

	static void DrawElement(Sprite* image, int xPos, int yPos, int width = 0, int height = 0);

	static void PrintText(string text, int xPos, int yPos, int size = 20, SDL_Color color = { 0, 0, 0});

	static void PlaySound(string sfxPath, int loops = 0);

	static void ClearScreen();

	static void Finish();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int AUDIO_RATE = 44100;
	static const Uint16 AUDIO_FORMAT = AUDIO_S16;
	static const int AUDIO_CHANNELS = 2;
	static const int AUDIO_BUFFERS = 2048;

private:
};

#endif

