#include "Common.h"
#include "Card.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player();

	void GetCard(Card card, int hand = 0);

	void ViewHands();

	static const int INITIAL_HANDS{ 1 };
	static const int INITIAL_HAND_SIZE{ 2 };
private:
	vector<vector<Card>> hands;
};

#endif