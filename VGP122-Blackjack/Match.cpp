#include "Match.h"

Match::Match() : gameStatus{ notStarted } { 
	/*cout << "dealer address: " << &dealer << endl;
	
	Dealer* dealers[2];
	
	dealers[0] = &dealer;
	cout << "dealers[0] address: " << &dealers << endl;

	Dealer* dealerPtr = &dealer;
	cout << "dealerPtr address: " << dealerPtr << endl;

	dealers[0] = dealerPtr;
	cout << "dealers[0] address: " << &dealers << endl;*/


	
	players[0] = &dealer; players[1] = &player; }

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
	DealInitialHands();
	cout << "Dealer's Hand: " << endl;
	dealer.ViewHands();
	cout << "Your Hand: " << endl;
	player.ViewHands();
	cout << endl;
	GetPlay();
}

Card Match::GetCard() {
	return deck.GetCard();
}

void Match::DealCard(Card card, Player* currentPlayer)
{
	currentPlayer->GetCard(card);
}

void Match::DealInitialHands()
{
	for (size_t i{ 0 }; i < players.size(); i++)
	{
		for (size_t j{ 0 }; j < players[i]->INITIAL_HAND_SIZE; j++)
		{
			DealCard(GetCard(), players[i]);
		}
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

