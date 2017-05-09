#include "Common.h"
#include "Card.h"

#ifndef DECK_H
#define DECK_H

class Deck {
public:
	Deck();
	
	void Shuffle(size_t shuffles);
	
	const Card GetCard();
	
	void TEMP_ShowDeck();

private:
	std::vector<Card> cards;
};
#endif
