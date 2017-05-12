#include "Human.h"

Human::Human() : credits{ Human::INITIAL_CREDITS } { Player::TEMPname = 'h'; }

int Human::GetCredits()
{
	return credits;
}

bool Human::ValidateBet(unsigned int bet, unsigned int multiplier)
{
	if (credits >= bet * multiplier)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Human::Split()
{
	Player::ReceiveCard(hands[0][1], 1);
	Player::hands[0].pop_back();
}