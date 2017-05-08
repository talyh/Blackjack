#include "Common.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	explicit Player() : credits{ 500 } {}

	int Bet(int bet);	// return bet if the player has sufficient credits to place the bet
						// returns 0 if the player doesn't have sufficient credits

	int Split(int bet);	// return bet if the player has sufficient credits to place the bet
						// returns 0 if the player doesn't have sufficient credits

private:
	std::vector<int> hands;
	int credits;
};

#endif