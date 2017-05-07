#include <iostream>
#include <random>
#include "Deck.h"

void Deck::Shuffle(size_t shuffles)
{
	/*std::cout << "deck size:" << cards.size() << std::endl;
	std::cout << "Shuffling" << std::endl;*/

	for (size_t i{ 0 }; i < shuffles; i++)
	{
		int temp1 = rand() % 52;
		int temp2 = rand() % 52;

		cards[temp1] = temp2;
		cards.at(temp2) = temp1;
	}
}

const int Deck::GetCard()
{	
	int selected = cards[0];
	cards.erase(cards.begin() + 0);
	return selected;
}

// TODO Remove at the end
void Deck::TEMP_ShowDeck()
{
	int i{ 0 };
	for (int card : cards)
	{
		std::cout << i++ << ". " << card << std::endl;
	}
}
