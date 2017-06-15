#include "Player.h"

Player::Player() : hands(Player::INITIAL_HANDS), handsActive(Player::INITIAL_HANDS), handsScore(Player::INITIAL_HANDS)
{
	handsActive[0] = true;
	handsScore[0] = 0;
}

void Player::ReceiveCard(Card* card, int hand)
{
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

void Player::Stay(int hand)
{
	SetHandStatus(hand, false);
}

Card* Player::GetCard(int hand, int position)
{
	return &hands[hand][position];
}

vector<Card> Player::GetSingleHand(int hand)
{
	return hands[hand];
}

vector<vector<Card>> Player::GetHands()
{
	return hands;
}

vector<bool> Player::GetHandsStatus()
{
	return handsActive;
}

int Player::GetHandScore(int hand)
{
	return handsScore[hand];
}

void Player::SetHandStatus(int hand, bool handStatus)
{
	handsActive[hand] = handStatus;
}

void Player::SetHandScore(int score, int hand)
{
	handsScore[hand] = score;
}

void Player::ViewSingleHand(int hand, bool showHandNumber)
{
	int i{ 0 };
		cout << "--------- Hand " << (showHandNumber ? to_string(hand + 1) + " " : "--") << "--------" << endl;
		for (Card card : hands[hand])
		{
			if (card.GetFaceUp())
			{
				card.ViewCard();
			}
			else
			{
				cout << "<< Card is hidden >>" << endl;
			}
		}
}

void Player::FinishRound()
{
	for (vector<Card> hand : hands)
	{
		for (Card card : hand)
		{
			card.DeleteImage();
		}
	}
	hands = *(new vector<vector<Card>>(1));
	handsActive = *(new vector<bool>(1));
	handsActive[0] = true;
	handsScore = *(new vector<int>(1));
}

void Player::ShowHiddenCards()
{
	for (size_t i{ 0 }; i < hands.size(); i++)
	{
		for (size_t j{ 0 }; j < hands[i].size(); j++)
		{
			if (!hands[i][j].GetFaceUp())
			{
				hands[i][j].Flip();
			}
		}
	}
}
