#include "Human.h"

Human::Human() : credits{ Human::INITIAL_CREDITS } { Player::TEMPname = 'h'; }

int Human::GetCredits()
{
	return credits;
}

int Human::Bet(int bet)
{
	if (credits >= bet)
	{
		credits -= bet;
		return bet;
	}
	else
		return 0;
}

bool Human::DoubleBet(int bet)
{
	if (credits >= bet * 2)
	{
		credits -= bet;
		return true;
	}
	else
	{
		return false;
	}

	static const int INITIAL_CREDITS{ 500 };
}
