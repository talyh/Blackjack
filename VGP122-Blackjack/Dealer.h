#include "Player.h"

#ifndef DEALER_H
#define DEALER_H

class Dealer : public Player
{
public:
	Dealer()  {Player::TEMPname = 'd'; }

	void DealCard(Card card, Player* currentPlayer);

	virtual void ReceiveCard(Card card, int hand = 0);
};

#endif // !DEALER_H

