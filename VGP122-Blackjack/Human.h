#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player
{
public:
	Human();

	int GetCredits();

	bool ValidateBet(unsigned int bet, unsigned int multiplier = 1);	// validates the player has enough credits to place the bet, considering a multiplier if needed

	void Split();

	static const int INITIAL_CREDITS{ 500 };

private:
	int credits;
};

#endif // !PLAYER_H