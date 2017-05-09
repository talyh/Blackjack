#include "Human.h"

Human::Human() : credits{ Human::INITIAL_CREDITS } { Player::TEMPname = 'h'; }

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

int Human::Split(int bet)
{
	if (credits >= bet * 2)
	{
		credits -= bet;
		return bet;
	}
	else
	{
		return 0;
	}

	static const int INITIAL_CREDITS{ 500 };
}
