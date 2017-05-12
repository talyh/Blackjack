#include "Dealer.h"

Dealer::Dealer() { Player::type = "dealer"; }

void Dealer::DealCard(Card card, Player * currentPlayer, int hand)
{
	currentPlayer->ReceiveCard(card, hand);
}

void Dealer::ReceiveCard(Card card, int hand)
{
	// if it's the dealer's very first card, hide it
	if (empty(hands[0]))
	{
		card.SetFaceUp(false);
	}
	// if there's not yet a hand "row" to store cards, create a new row and mark that hand active
	if (hands.size() <= hand)
	{
		vector<Card> temp;
		hands.push_back(temp);
		Player::handsActive.push_back(true);
	}
	// place new card at the end of the selected row
	hands[hand].push_back(card);
}
