#include "Dealer.h"

Dealer::Dealer() { Player::type = "dealer"; }

void Dealer::DealCard(Card* card, Player* currentPlayer, int hand)
{
	currentPlayer->ReceiveCard(card, hand);
}

void Dealer::AdditionalTasksOnReceiveCard()
{
	// if it's the dealer's very first card, hide it
	if (hands[0].size() == 1)
	{
		hands[0][0]->Flip();
	}
}

bool Dealer::GetHandRisk()
{
	DetermineRiskyHand();
	return riskyHand;
}

void Dealer::DetermineRiskyHand()
{
	for (Card* c : hands[0])
	{
		// if the dealer has an Ace showing, their hand is risky
		riskyHand = (c->GetFace() == "A" && c->GetFaceUp() == true);
	}
}

