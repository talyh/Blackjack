#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include "GameController.h"
#include "Instructions.h"
#include "Match.h"
#include "Player.h"
#include "Dealer.h"

using namespace std;

void ShowOptions();
void GetOption(Match);

GameController gameController;
// TODO QUESTION why couldn't define inside main?

void main()
{
	Match match = gameController.getMatch();
	Player player = gameController.getPlayer();
	Dealer dealer = gameController.getDealer();
	
	while (match.GetGameStatus() == Match::notStarted)
	{
		ShowOptions();
		GetOption(match);
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

void GetOption(Match match)
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
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
		}
	}
}
