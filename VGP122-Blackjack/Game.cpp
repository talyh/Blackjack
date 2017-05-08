#include "Common.h"
#include "Instructions.h"
#include "Match.h"

using namespace std;

void ShowOptions();
void GetOption();

Match match;

void main()
{

	
	while (match.GetGameStatus() == Match::notStarted)
	{
		ShowOptions();
		GetOption();
	}
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
	while (option < 1 || option > 3)
	{
		cin >> option;
		switch (option)
		{
			case 1:
			{
				match.StartGame();
				break;
			}
			case 2:
			{
				ShowInstructions();
				break;
			}
			case 3:
			{
				system("exit");
				break;
			}
			default:
			{
				cout << "Option invalid. Please enter (1), (2) or (3)." << endl;
				Common::FlushInput();
				break;
			}
		}
	}
}
