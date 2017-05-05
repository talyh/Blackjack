#include <iostream>
#include <array>
#include <string>
#include <iomanip>
#include <vector>
#include <random>
#include "GameManager.h"
#include "Instructions.h"

using namespace std;

void ShowOptions();
void GetOption();

GameManager match; // TODO QUESTION which access level this should have?

void main()
{
		while (match.GetGameStatus() == GameManager::notStarted)
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
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
		}
	}
}
