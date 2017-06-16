#include "Human.h"

Human::Human() : credits{ Human::INITIAL_CREDITS } { Player::type = "guest"; }

int Human::GetCredits()
{
	return credits;
}

bool Human::ValidateBet(unsigned int bet, unsigned int multiplier)
{
	if (credits >= bet * multiplier)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Human::Split()
{
	Player::ReceiveCard(hands[0][1], 1);
	Player::hands[0].pop_back();
}

void Human::AdjustCredits(int amount)
{
	credits += amount;
}

bool Human::GetSplitable()
{
	DetermineSplitable();
	return splitableHand;
}

void Human::DetermineSplitable()
{
	splitableHand = (hands[0][0]->GetFace() == hands[0][1]->GetFace() && hands[0].size() == 2);
}
