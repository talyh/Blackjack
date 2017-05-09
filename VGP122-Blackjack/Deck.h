#include "Common.h"
#include "Card.h"

#ifndef DECK_H
#define DECK_H

class Deck {
public:
	Deck() :
		cards(52)
	{
		for (size_t i{0}; i < cards.size(); i++)
		{
			cards[i].face = (Card::FACES)(i % 13);
			cards[i].suit = (Card::SUITS)(i / 13);
			cards[i].SetFaceValue(cards[i].face);
		}
	}
	
	void Shuffle(size_t shuffles);
	
	const Card GetCard();
	
	void TEMP_ShowDeck();

private:
	std::vector<Card> cards;
};
#endif
