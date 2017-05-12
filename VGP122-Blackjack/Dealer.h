#ifndef DEALER_H
#define DEALER_H

#include "Player.h"

class Dealer : public Player
{
public:
	Dealer();

	void DealCard(Card card, Player* currentPlayer);

	virtual void ReceiveCard(Card card, int hand = 0);
};

#endif // !DEALER_H

