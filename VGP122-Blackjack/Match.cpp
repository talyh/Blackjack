#include "Match.h"

Match::Match() : gameStatus{ notStarted } 
{ 
	// assign players to the players vector pointer
	players[0] = &dealer; 
	players[1] = &player;
	
	// create space in the bets vector to store the first bet
	bets.push_back(0);
}

int Match::GetGameStatus()
{
	return gameStatus;
}

void Match::StartGame()
{
	system("cls");
	gameStatus = running;

	// shuflle deck
	deck.Shuffle(SHUFFLES);

	// play
	// TODO - add loop
	cout << "----------------------------------------------" << endl;
	cout << "                   Welcome !                  " << endl;
	cout << "----------------------------------------------" << endl;
	PlayRound();
}

void Match::PlayRound()
{
	beginningRound = true;
	finishedRound = false;
	
	GetBet();
	cout << "You have $" << roundCredits << " left" << endl;
	cout << "----------------------------------------------" << endl;
	
	DealInitialHands();
	cout << "-------------------------" << endl;
	cout << "Dealer's Hand: " << endl;
	dealer.ViewHands();
	CalculatePlayerScore(&dealer);
	cout << "-------------------------" << endl;
	cout << "Your Hand: " << endl;
	player.ViewHands();
	CalculatePlayerScore(&player);
	cout << "Points: " << player.GetHandScore() << endl;
	cout << "-------------------------" << endl;
	
	if (risky)
	{
		OfferInsurance();
		OfferSurrender();
	}
	if (CheckPlayerCards(&dealer, &beginningRound) == 2 || CheckPlayerCards(&player, &beginningRound) == 2)
	{
		FinishRound();
	}
	else
	{
		// TODO include active hand verification
		while (!finishedRound)
		{
			GetPlay(beginningRound, splitable);
		}
	}
	cout << "----------------------------------------------" << endl;	
}

Card Match::DrawCard() {
	return deck.GetCard();
}

void Match::DealInitialHands()
{
	for (size_t i{ 0 }; i < players.size(); i++)
	{
		for (size_t j{ 0 }; j < players[i]->INITIAL_HAND_SIZE; j++)
		{
			dealer.DealCard(DrawCard(), players[i]);
		}
	}

	// if either one of the dealer's cards is an A, the player may surrender or take insurance
	risky = (/*dealer.GetSingleHand(0)[0].GetFace() == "A" ||*/ dealer.GetSingleHand(0)[1].GetFace() == "A");
	// if the two first cards in the player's main hand have the same face, they can be split
	splitable = (player.GetSingleHand(0)[0].GetFace() == player.GetSingleHand(0)[1].GetFace());
}

void Match::GetBet()
{
	cout << "Enter the amount you'd like to bet: $";
	cin >> bets[0];

	if (bets[0] > 0)
	{	
		if (player.ValidateBet(bets[0]))
		{
			roundCredits = player.GetCredits() - bets[0];
			cout << "Betting $" << bets[0] << endl;
		}
		else
		{
			cout << "Insuficient credits." << endl;
			GetBet();
		}
	}
	else
	{
		cout << "Invalid bet." << endl;
		Common::FlushInput();
		GetBet();
	}
}

void Match::OfferInsurance()
{
	cout << "Would you like insurance?" << endl;
}

void Match::OfferSurrender()
{
	cout << "SURRENDER NOW!" << endl;
}

void Match::GetPlay(bool beginningRound, bool splitable)
{
	// get the player's choice of play
	cout << "Please enter an option" << endl;
	if (beginningRound) 
	{
		if (splitable)
		{
			cout << "(P) sPlit" << endl;
		}
		cout << "(D) Double down" << endl;
	}
	cout << "(H) Hit" << endl; 
	cout << "(S) Stay" << endl;

	char option{ };
	
	// direct play to the proper course, ensuring only valid plays are selectable
	while (cin >> option)
	{
		if ((option == 'P' || option == 'p') && beginningRound && splitable)
		{
			cout << "Splitting" << endl;
			Split();
			break;
		}
		else if (option == 'H' || option == 'h')
		{
			cout << "Hitting" << endl;
			Hit(&player);
			break;
		}
		else
		{
			cout << "Option invalid. Please enter a valid play." << endl;
			Common::FlushInput();
		}
	}
}

void Match::Split()
{
	if (player.ValidateBet(bets[0], 2))
	{
		bets.push_back(bets[0]);
		roundCredits = player.GetCredits() - (bets[0] * 2);
		cout << "Now betting $" << bets[0] << " on each hand" << endl;
		player.Split();
	}
	else
	{
		cout << "Insuficient credits to split. Please choose another play." << endl;
		GetPlay(beginningRound, splitable);
	}
}

void Match::Hit(Player* currentPlayer)
{
	dealer.DealCard(DrawCard(), currentPlayer);
	cout << "-------------------------" << endl;
	cout << "Current hand: " << endl;
	player.ViewHands();
	cout << "-------------------------" << endl;
}

void Match::FinishRound()
{
	// resolve payment

	//  delete all items from bets

	// reset hands active

	// reset hands

	// reset handsScore
	 // reset roundCredits

	finishedRound = true;

	cout << "FinishRound" << endl;
	for (Player* currentPlayer : players)
	{
		int i{0};
		for (vector<Card> hand : currentPlayer->GetHands())
		{
			cout << currentPlayer->GetPlayerType() << "'s hand " << ++i << " got " << currentPlayer->GetHandScore(i - 1) << " points" << endl;
		}
	}
}

void Match::CalculatePlayerScore(Player * currentPlayer, int hand)
{
	int handScore{ 0 };
	int handSize = currentPlayer->GetSingleHand(hand).size();

	for (size_t i{ 0 }; i < handSize; i++)
	{
		handScore += currentPlayer->GetCard(hand, i).GetFaceValue();
	}
	
	currentPlayer->SetHandScore(handScore, hand);
}

int Match::CheckPlayerCards(Player* currentPlayer, bool beginningRound, int hand)
{
	// TODO will likely need to refactor

	int handScore = currentPlayer->GetHandScore(hand);
	int handSize = currentPlayer->GetSingleHand(hand).size();

	if (handScore >= 21)
	{
		if (handScore > 21 && !beginningRound)
		{
			return 1;
		}
		else //handScore = 21
		{
			if (handSize = 2) // a Blackjack can only be accomplished by 2 cards
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
		currentPlayer->SetHandStatus(hand, false); // stop that hand from playing any further
	}
	else
	{
		return 0;
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

