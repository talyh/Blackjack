#include "Player.h"

#ifndef DEALER_H
#define DEALER_H

class Dealer : public Player
{
public:
	Dealer()  {Player::TEMPname = 'd'; }
};

#endif // !DEALER_H

