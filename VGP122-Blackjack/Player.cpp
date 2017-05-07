#include <iostream>
#include "Player.h"

void Player::Bet(int bet)
{
	/*bet > credits ? std::cout << "Please choose again" << std::endl :*/
	match:Bet(bet);
	credits -= bet;
}