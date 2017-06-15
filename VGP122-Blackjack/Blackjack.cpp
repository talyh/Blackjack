#include "Common.h"
#include "Match.h"
#include "GameRender.h"
#include "CollisionDetection.h"

// declare Pointers we'll need
Sprite* btnStart = NULL;
Sprite* btnInstructions = NULL;
Sprite* btnQuit = NULL;

// initialize Event Variables
SDL_Event startMenuEvent;

Match match;

int main(int argc, char** argv)
{
	// start control for game running
	bool gameRunning = true;

	// initialize graphical and visual elements
	GameRender::Initialize(FONT, FONT_SIZE);

	// draw the Start Menu window
	GameRender::SetBackground(BACKGROUND_IMAGE);

	// play music
	GameRender::SetMusic(MUSIC);

	// draw the start menu options
	LoadStartMenu();

	// seed the random
	srand(static_cast<unsigned int>(time(0)));

	// start listening for user interactions
	ListenForGameEvents(&gameRunning);

	// unload graphical and visual elements
	GameRender::Finish();

	return 0;
}

void ListenForGameEvents(bool listening)
{
	while (listening)
	{
		while (SDL_PollEvent(&startMenuEvent))
		{
			switch (startMenuEvent.type)
			{
				// Check if user tries to quit the window
				case SDL_QUIT:
				{
					// Break out of loop to end game
					listening = false;
					break;
				}
				//	Check if the ESC key was pressed
				case SDL_KEYDOWN:
				{
					//	Check if 'ESC' was pressed
					if (startMenuEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					{
						// Break out of loop to end game
						listening = false;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					GameRender::PlaySound(SFX_BUTTON_CLICK);

					if (btnStart && CollisionDetection::isColliding(startMenuEvent.motion.x, startMenuEvent.motion.y, btnStart))
					{
						cout << "Starting Game" << endl;
						match.PlayGame();
					}
					else if (btnInstructions && CollisionDetection::isColliding(startMenuEvent.motion.x, startMenuEvent.motion.y, btnInstructions))
					{
						cout << "Showing Instructions" << endl;
						GameRender::ClearScreen();
						ShowInstructions();
					}
					else if (btnQuit && CollisionDetection::isColliding(startMenuEvent.motion.x, startMenuEvent.motion.y, btnQuit))
					{
						listening = false;
					}
					break;
				}
			}
		}
	}
}

void LoadStartMenu()
{
	GameRender::DrawElement(BTN_PLAY_IMAGE, SCREEN_WIDTH / 2 - START_MENU_BUTTON_SIZE.width / 2
		, 100, START_MENU_BUTTON_SIZE.width, START_MENU_BUTTON_SIZE.height, &btnStart);
	GameRender::DrawElement(BTN_INSTRUCTIONS_IMAGE, SCREEN_WIDTH / 2 - START_MENU_BUTTON_SIZE.width / 2, btnStart->getYPos() + START_MENU_BUTTON_SIZE.height + LINE_HEIGHT, START_MENU_BUTTON_SIZE.width, START_MENU_BUTTON_SIZE.height, &btnInstructions);
	GameRender::DrawElement(BTN_QUIT_IMAGE, SCREEN_WIDTH / 2 - START_MENU_BUTTON_SIZE.width / 2, btnInstructions->getYPos() + START_MENU_BUTTON_SIZE.height + LINE_HEIGHT, START_MENU_BUTTON_SIZE.width, START_MENU_BUTTON_SIZE.height, &btnQuit);
}

void ShowInstructions()
{
	// show text
	//GameRender::PrintText("Instructions for Blackjack", 10, 100, { 211, 204, 188 });
	//GameRender::PrintText("Please visit Wikipedia for rules \nhttps://en.wikipedia.org/wiki/Blackjack", 10, 160, {189, 211, 188});

	// show buttons
	GameRender::DrawElement(btnStart, { SCREEN_WIDTH / 4 - START_MENU_BUTTON_SIZE.width / 2, 400 });
	GameRender::DrawElement(btnQuit, { SCREEN_WIDTH / 4 - START_MENU_BUTTON_SIZE.width / 2, btnStart->getYPos() + START_MENU_BUTTON_SIZE.height + LINE_HEIGHT } );
}


