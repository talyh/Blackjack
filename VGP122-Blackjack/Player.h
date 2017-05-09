#include "Common.h"
#include "Card.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player();

	int Bet(int bet);	// return bet if the player has sufficient credits to place the bet
						// returns 0 if the player doesn't have sufficient credits

	int Split(int bet);	// return bet if the player has sufficient credits to place the bet
						// returns 0 if the player doesn't have sufficient credits

	void GetCard(Card card, int hand = 0);

	void ViewHands();

	static const int INITIALCREDITS = 500;

private:
	vector<vector<Card>> hands;
	int credits;
};

#endif