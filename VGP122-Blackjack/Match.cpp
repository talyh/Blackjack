#include "Match.h"

Match::Match() : gameStatus{ notStarted } 
{ 
	players[0] = &dealer; players[1] = &player;
}

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
	cout << "----------------------------------------------" << endl;
	cout << "                   Welcome !                  " << endl;
	cout << "----------------------------------------------" << endl;
	bets.push_back(0);
	GetBet();
	cout << "You have $" << player.GetCredits() << " left" << endl;
	cout << "----------------------------------------------" << endl;
	DealInitialHands();
	cout << "Dealer's Hand: " << endl;
	dealer.ViewHands();
	CheckPoints(&dealer);
	cout << "-------------------------" << endl;
	cout << "Your Hand: " << endl;
	player.ViewHands();
	CheckPoints(&player);
	cout << "----------------------------------------------" << endl;
	//GetPlay();
}

Card Match::GetCard() {
	return deck.GetCard();
}

void Match::DealCard(Card card, Player* currentPlayer)
{
	currentPlayer->ReceiveCard(card);
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
	cout << "Enter the amount you'd like to bet: $";

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
		cout << "Betting $" << bets[0] << endl;
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
	int option{ 0 };
	while (cin >> option)
	{
		switch (option)
		{
		case 1:
			break;
		default:
			cout << "Option invalid. Please enter (1), (2) or (3)." << endl;
			Common::FlushInput();
			break;
		}
	}
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

void Match::CheckPoints(Player* currentPlayer, int hand)
{
	// TODO conaider refactor for step-by-step deal cards
	int handScore{ 0 };
	int handSize = currentPlayer->GetSingleHand(hand).size();

	for (size_t i{ 0 }; i < handSize; i++)
	{
		handScore += currentPlayer->GetCard(hand, i).GetFaceValue();
	}

	cout << "Points: " << handScore << endl;

	// TODO will likely need to refactor

	if (handScore >= 21)
	{
		if (handScore > 21)
		{
			cout << "Busted" << endl;
		}
		else //handScore = 21
		{
			if (handSize = 2) // a Blackjack can only be accomplished by 2 cards
			{
				cout << "Blackjack" << endl;
			}
			else
			{
				cout << "You got 21!" << endl;
			}
		}
		currentPlayer->SetHandStatus(hand, false); // stop that hand from playing any further
	}
	else
	{
		cout << "Keep Playing" << endl;
	}
}

void Match::TEMP_ShowBets()
{
	int i{ 0 };
	for (int bet : bets)
	{
		cout << i++ << ". " << bet << endl;
	}
}

