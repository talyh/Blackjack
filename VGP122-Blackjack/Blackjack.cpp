#include "Common.h"
#include "Match.h"
#include "GameRender.h"
#include "CollisionDetection.h"

using namespace std;

// initialize Event Variables
SDL_Event event;

// initialize timer variables
int				deltaT = 75;	// defines delay in time for updating game loop
int				updatedTime = 0;	// used to determine if frame rate interval has elapsed

// declare Pointers we'll need
Sprite* btnStart = NULL;
Sprite* btnInstructions = NULL;
Sprite* btnQuit = NULL;

// define layout variables
struct ButtonSize
{
	int width;
	int heigth;
};
const ButtonSize START_MENU_BUTTON { 383, 78 };

// protoype functions
void ListenForGameEvents(bool listening);
void LoadStartMenu();
void ShowInstructions();

// define constants
// visual
const string BACKGROUND_IMAGE = "imgs/background.png";
const string BTN_PLAY_IMAGE = "imgs/btnPlay.png";
const string BTN_INSTRUCTIONS_IMAGE = "imgs/btnInstructions.png";
const string BTN_QUIT_IMAGE = "imgs/btnQuit.png";
// audio
const string MUSIC = "snds/music.mid";
const string SFX_BUTTON_CLICK = "snds/jump.wav";
const string SFX_START = "snds/";
const string SFX_BET = "sdns/";
const string SFX_HIT = "sdns/";
const string SFX_STAY = "sdns/";
const string SFX_SPLIT = "sdns/";
const string SFX_DOUBLE_DOWN = "sdns/";
const string SFX_RECEIVE_BET = "sdns/";
const string SFX_PAY_BET = "sdns/";
const string SFX_GAME_OVER = "sdns/";
// font
const string FONT = "fnts/amer_typewriter.ttf";
const int FONT_SIZE = 32;

/*

void GetOption()
{
	int option{ 0 };
	do
	{
		cin >> option;
		switch (option)
		{
			case 1:
				match.PlayGame(); // Play Game
				break;
			case 2:
				ShowInstructions(); // Show instructions
				break;
			case 3:
				exit(1); // Quit
				break;
			default:
				cout << "Option invalid. Please enter (1), (2) or (3)." << endl;
				Common::FlushInput(); // Clear input to allow loop to rerun
				break;
		}
	} while (option < 1 || option > 3);
}
*/

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
		if (SDL_GetTicks() - updatedTime >= deltaT)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
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
						if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						{
							// Break out of loop to end game
							listening = false;
						}
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						GameRender::PlaySound(SFX_BUTTON_CLICK);

						if (btnStart && CollisionDetection::isColliding(event.motion.x, event.motion.y, btnStart))
						{
							cout << "Starting Game" << endl;
						}
						else if (btnInstructions && CollisionDetection::isColliding(event.motion.x, event.motion.y, btnInstructions))
						{
							cout << "Showing Instructions" << endl;
							GameRender::ClearScreen();
							ShowInstructions();
						}
						else if (btnQuit && CollisionDetection::isColliding(event.motion.x, event.motion.y, btnQuit))
						{
							listening = false;
						}
						break;
					}
				}
			}

			// update time
			updatedTime = SDL_GetTicks();
		}
	}
}

void LoadStartMenu()
{
	GameRender::DrawElement(BTN_PLAY_IMAGE, 170, 100, START_MENU_BUTTON.width, START_MENU_BUTTON.heigth, &btnStart);
	GameRender::DrawElement(BTN_INSTRUCTIONS_IMAGE, 170, 198, START_MENU_BUTTON.width, START_MENU_BUTTON.heigth, &btnInstructions);
	GameRender::DrawElement(BTN_QUIT_IMAGE, 170, 296, START_MENU_BUTTON.width, START_MENU_BUTTON.heigth, &btnQuit);
}

void ShowInstructions()
{
	// show text
	GameRender::PrintText("Instructions for Blackjack", 10, 100, 20, { 211, 204, 188 });
	GameRender::PrintText("Please visit Wikipedia for rules \nhttps://en.wikipedia.org/wiki/Blackjack", 10, 160, 20, {189, 211, 188});

	// show buttons
	GameRender::DrawElement(btnStart, 100, 400);
	GameRender::DrawElement(btnQuit, 100, 400 + START_MENU_BUTTON.heigth + 20);
}


