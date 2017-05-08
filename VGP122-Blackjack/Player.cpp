#include "Player.h"

int Player::Bet(int bet)
{
	/*bet > credits ? std::cout << "Please choose again" << std::endl :*/
	if (credits >= bet)
	{
		credits -= bet;
		return bet;
	}
	else
		return 0;
}

int Player::Split(int bet)
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

}
