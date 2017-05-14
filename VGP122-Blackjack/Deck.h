#ifndef DECK_H
#define DECK_H

#include "Common.h"
#include "Card.h"

class Deck {
public:
	Deck();

	void Shuffle(size_t shuffles);

	const Card GetCard();

	int GetDeckSize();


private:
	vector<Card> cards;
};
#endif
