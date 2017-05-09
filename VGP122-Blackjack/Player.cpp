#include "Player.h"

Player::Player() : hands(1), credits{Player::INITIALCREDITS}
{
}

int Player::Bet(int bet)
{
	if (credits >= bet)
	{
		credits -= bet;
		return bet;
	}
	else
		return 0;
}

int Player::Split(int bet)
{
	if (credits >= bet * 2)
	{
		credits -= bet;
		return bet;
	}
	else
	{
		return 0;
	}

}

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
