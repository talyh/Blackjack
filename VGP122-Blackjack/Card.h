#include "Common.h"

#ifndef CARD_H
#define CARD_H

const array<string, 13> FACES{ "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
const array<string, 4> SUITS{ "Hearts", "Diamonds", "Clubs", "Spades" };

class Card
{
public:
	void SetFace(string face);
	void SetSuit(string suit);
	void SetFaceValue(string face);

	string GetFace();
	string GetSuit();
	int GetFaceValue();

	void ViewCard();

private:
	string face;
	string suit;
	int faceValue;
};

#endif




