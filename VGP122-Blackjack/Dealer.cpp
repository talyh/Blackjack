#include "Dealer.h"

Dealer::Dealer() { Player::type = "dealer"; }

void Dealer::DealCard(Card* card, Player* currentPlayer, int hand)
{
	currentPlayer->ReceiveCard(card, hand);
}

void Dealer::ReceiveCard(Card* card, int hand)
{
	// if it's the dealer's very first card, hide it
	if (empty(hands[0]))
	{
		card->Flip();
	}

	// if there's not yet a hand "row" to store cards, create a new row and mark that hand active
	if (hands.size() <= hand)
	{
		vector<Card> temp;
		hands.push_back(temp);
		Player::handsActive.push_back(true);
		Player::handsScore.push_back(0);
	}
	// place new card at the end of the selected row
	hands[hand].push_back(*card);
}

bool Dealer::GetHandRisk()
{
	DetermineRiskyHand();
	return riskyHand;
}

void Dealer::DetermineRiskyHand()
{
	for (Card c : hands[0])
	{
		// if the dealer has an Ace showing, their hand is risky
		riskyHand = (c.GetFace() == "A" && c.GetFaceUp() == true);
	}
}


