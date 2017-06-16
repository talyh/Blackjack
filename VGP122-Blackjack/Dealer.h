#ifndef DEALER_H
#define DEALER_H

#include "Player.h"

class Dealer : public Player
{
public:
	Dealer();

	void DealCard(Card card, Player* currentPlayer, int hand = 0); // to distribute cards to players

	void AdditionalTasksOnReceiveCard() override;

	bool GetHandRisk(); // to get the riskiness of a hand, based on Ace showing

private:
	bool riskyHand; // to indicate whether the dealer is showing an Ace in their first hand,
						// making it risky for the guest

	void DetermineRiskyHand(); // to determine the riskiness of a hand
};

#endif // !DEALER_H

