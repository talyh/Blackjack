#include "Player.h"

#ifndef HUMAN_H
#define HUMAN_H

class Human : public Player
{
public:
	Human();

	int GetCredits();

	int Bet(int bet);	// return bet if the player has sufficient credits to place the bet
						// returns 0 if the player doesn't have sufficient credits

	bool DoubleBet(int bet);	// checks whether the player has enough credits to double the bet for a Split or a DoubleDown

	static const int INITIAL_CREDITS{ 500 };

private:
	int credits;
};

#endif // !PLAYER_H