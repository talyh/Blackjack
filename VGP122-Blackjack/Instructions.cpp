#include <iostream>

// TODO write instructions

void ShowInstructions()
{
	std::system("cls");
	std::cout << "------------------------" << std::endl;
	std::cout << "Instuctions for Blackjack" << std::endl;

	std::cout << "Press any key to return to the main menu" << std::endl;
	char input{};
	if (std::cin >> input)
	{
		return;
	}
}