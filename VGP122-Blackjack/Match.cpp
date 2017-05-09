#include "Match.h"

int Match::GetGameStatus()
{
	return gameStatus;
}

void Match::StartGame()
{
	system("cls");
	gameStatus = running;
	deck.Shuffle(SHUFFLES);
	PlayRound();
}

void Match::PlayRound()
{
	bets.push_back(0);
	GetBet();
	DealInitialHand();
	cout << "Hand: ";
	player.ViewHands();
	cout << endl;
	GetPlay();

}

Card Match::GetCard() {
	return deck.GetCard();
}

void Match::DealCard(Card card)
{
	player.GetCard(card);
}

void Match::DealInitialHand()
{
	for (size_t i{ 0 }; i < Player::INITIAL_HAND_SIZE; i++)
	{
		DealCard(GetCard());
	}
}

void Match::GetBet()
{
	cout << "Enter the amount you'd like to bet" << endl;

	if (cin >> bets[0])
	{
		Bet(bets[0]);
	}
	else
	{
		cout << "Invalid bet." << endl;
		Common::FlushInput();
		GetBet();
	}
}

void Match::Bet(int credits)
{
	// TODO need to acd credit limit check on Player
	if (player.Bet(credits) > 0)
	{
		bets[0] = credits;
		cout << "Betting " << bets[0] << endl;
	}
	else
	{
		cout << "Insuficient credits." << endl;
		GetBet();
	}
}

void Match::GetPlay()
{
	cout << "Please enter an option" << endl;
}

void Match::Split()
{
	// TODO need to acd credit limit check on Player
	if (player.Split(bets[0]) > 0)
	{
		bets[0] *= 2;
		bets.push_back(bets[0]);
	}
	else
	{
		cout << "Insuficient credits to split. Please choose another play." << endl;
	}
}

void Match::FinishRound()
{
	// resolve payment

	//  delete all items from bets
}

void Match::TEMP_ShowBets()
{
	int i{ 0 };
	for (int bet : bets)
	{
		cout << i++ << ". " << bet << endl;
	}
}

