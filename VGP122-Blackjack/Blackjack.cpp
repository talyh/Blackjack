#include "Common.h"
#include "Match.h"
#include "GameRender.h"
#include "CollisionDetection.h"

// declare buttons we'll need
Button btnStart
{
	"btnStart",
	{
		SCREEN_WIDTH / 2 - START_MENU_BUTTON_SIZE.width / 2,
		100
	},
	{
		START_MENU_BUTTON_SIZE.width,
		START_MENU_BUTTON_SIZE.height
	},
	BTN_PLAY_IMAGE
};

Button btnInstructions
{
	"btnInstructions",
	{ 0, 0 },
	{
		START_MENU_BUTTON_SIZE.width,
		START_MENU_BUTTON_SIZE.height
	},
	BTN_INSTRUCTIONS_IMAGE
};
Button btnQuit
{
	"btnQuit",
	{0, 0 },
	{
		START_MENU_BUTTON_SIZE.width,
		START_MENU_BUTTON_SIZE.height
	},
	BTN_QUIT_IMAGE
};

// initialize Event Variables
SDL_Event startMenuEvent;

// prototype functions
void LoadStartMenu();
void ListenForGameEvents(bool listening);
void ShowInstructions();
void LoadGameOver();

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

	LoadGameOver();

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
					match.FinishGame();
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
						match.FinishGame();
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					GameRender::PlaySFX(SFX_BUTTON_CLICK);

					if (CollisionDetection::isColliding(startMenuEvent.motion.x, startMenuEvent.motion.y, btnStart.image))
					{
						match.PlayGame();
						listening = false;
						break;
					}
					else if (CollisionDetection::isColliding(startMenuEvent.motion.x, startMenuEvent.motion.y, btnInstructions.image))
					{
						ShowInstructions();
					}
					else if (CollisionDetection::isColliding(startMenuEvent.motion.x, startMenuEvent.motion.y, btnQuit.image))
					{
						listening = false;
						match.FinishGame();
					}
					break;
				}
			}
		}
	}
}

void LoadStartMenu()
{
	GameRender::DrawElement(&btnStart);
	btnInstructions.position = {
		SCREEN_WIDTH / 2 - START_MENU_BUTTON_SIZE.width / 2,
		(btnStart.image)->getYPos() + START_MENU_BUTTON_SIZE.height + LINE_HEIGHT
	};
	GameRender::DrawElement(&btnInstructions);
	btnQuit.position = {
		SCREEN_WIDTH / 2 - START_MENU_BUTTON_SIZE.width / 2,
		(btnInstructions.image)->getYPos() + START_MENU_BUTTON_SIZE.height + LINE_HEIGHT
	};
	GameRender::DrawElement(&btnQuit);
}

void ShowInstructions()
{
	GameRender::ClearScreen();
	
	// show text
	Textbox txtInstructions
	{
		"txtInstructions",
		{ PADDING, 100 },
		{ 0,0 },
		"Instructions for Blackjack \n Please visit Wikipedia for rules \nhttps://en.wikipedia.org/wiki/Blackjack"
	};

	GameRender::PrintText(&txtInstructions);

	// show buttons
	btnStart.position = { SCREEN_WIDTH / 4 - START_MENU_BUTTON_SIZE.width / 2, 400 };
	GameRender::DrawElement(&btnStart);
	btnQuit.position = { SCREEN_WIDTH / 4 - START_MENU_BUTTON_SIZE.width / 2, (btnStart.image)->getYPos() + START_MENU_BUTTON_SIZE.height + LINE_HEIGHT };
	GameRender::DrawElement(&btnQuit);
}

void LoadGameOver()
{
	GameRender::ClearScreen();

	Textbox txtGameOver
	{
		"txtGameOver",
		{ PADDING, 100 },
		{ 0,0 },
		"Thanks for Playing"
	};

	GameRender::PrintText(&txtGameOver);

	Sleep(6000);

	GameRender::Finish();
}

