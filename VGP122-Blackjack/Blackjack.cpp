// TODO move action methods to Player
// TODO review PlayRound for shortness improvements
// TODO review dynamic memory allocation cleanup
// TODO review protection levels

#include "Common.h"
#include "Instructions.h"
#include "Match.h"

using namespace std;

void ShowOptions();
void GetOption();

Match match;

int main(int argc, char** argv)
{
	/** Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cerr << "Unable to init SDL: " << SDL_GetError() << endl;
		return 1;
	}
	// Close SDL at program end
	atexit(SDL_Quit);
	
	srand(static_cast<unsigned int>(time(0)));
	
	while (match.GetGameStatus() == Match::notStarted)
	{
		system("cls");
		ShowOptions();
		GetOption();
	}

	return 0;
}

void ShowOptions() 
{
	cout << "----------------------------------------------" << endl;
	cout << "Choose an option below" << endl;
	cout << "1. Play game" << endl;
	cout << "2. See instructions" << endl;
	cout << "3. Quit" << endl;
	cout << "----------------------------------------------" << endl;
}

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
