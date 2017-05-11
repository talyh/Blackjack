#include "Player.h"

Player::Player() : hands(Player::INITIAL_HANDS), handsActive(Player::INITIAL_HANDS)
{
	handsActive[0] = true;
}

void Player::ReceiveCard(Card card, int hand)
{
	hands[hand].push_back(card);
}

Card Player::GetCard(int hand, int position)
{
	return hands[hand][position];
}

vector<Card> Player::GetSingleHand(int hand)
{
	return hands[hand];
}

vector<vector<Card>> Player::GetHands()
{
	return hands;
}

bool Player::GetHandStatus(int hand)
{
	return handsActive[hand];
}

void Player::SetHandStatus(int hand, bool handActive)
{
	this->handsActive[hand] = handActive;
}

void Player::ViewHands()
{
	for (size_t i{ 0 }; i < hands.size(); i++)
	{
		for (size_t j{0}; j < hands[i].size(); j++)
		{
			hands[i][j].ViewCard();
		}
	}
}
