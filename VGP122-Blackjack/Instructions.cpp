#include "Instructions.h"

// TODO write instructions

void ShowInstructions()
{
	system("cls");
	cout << "------------------------------------" << endl;
	cout << "Instuctions for Blackjack" << endl;
	cout << "------------------------------------" << endl;
	cout << "PLease visit Wikipedia for rules" << endl;
	cout << "https://en.wikipedia.org/wiki/Blackjack" << endl;
	cout << "------------------------------------" << endl;
	cout << "Press any key to return to the main menu" << endl;
	char input{};
	if (cin >> input)
	{
		return;
	}
}