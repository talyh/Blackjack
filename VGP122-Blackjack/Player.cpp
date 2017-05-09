#include "Player.h"

Player::Player() : hands(Player::INITIAL_HANDS) {}

void Player::GetCard(Card card, int hand)
{
	hands[hand].push_back(card);
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
