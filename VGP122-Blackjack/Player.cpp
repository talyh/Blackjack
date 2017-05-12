#include "Player.h"

Player::Player() : hands(Player::INITIAL_HANDS), handsActive(Player::INITIAL_HANDS)
{
	handsActive[0] = true;
}

void Player::ReceiveCard(Card card, int hand)
{
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
			if (hands[i][j].GetFaceUp())
			{
				hands[i][j].ViewCard();
			}
			else
			{
				cout << " << Card is hidden >>" << endl;
			}
		}
	}
}
