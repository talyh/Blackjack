#include "Match.h"

// TODO BUG dealer's hand A, A, 10 evaluated to 22 (should've been 12)

Match::Match() : gameStatus{ notStarted } 
{ 
	// assign players to the players vector pointer
	players[0] = &dealer; 
	players[1] = &player;

	// point the deck to the current deck in use
	deck = &currentDeck;

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
	deck->Shuffle(SHUFFLES);

	cout << "----------------------------------------------" << endl;
	cout << "                   Welcome !                  " << endl;
	cout << "----------------------------------------------" << endl;
	
	// game runs while player has creddits
	// if cards run out, a new deck is used
	while (player.GetCredits() > 0)
	{
		PlayRound();
	}
	FinishGame();
}

void Match::PlayRound()
{
	beginningRound = true;
	finishedRound = false;

	cout << "----------------- New Round ------------------" << endl;
	cout << "You currently have $" << player.GetCredits() << endl;
	GetBet();
	cout << "You have $" << roundCredits << " left" << endl;
	cout << "----------------------------------------------" << endl;
	
	DealInitialHands();

	// if either one of the dealer's cards is an A, the player may surrender or take insurance
	risky = (dealer.GetSingleHand(0)[1].GetFace() == "A");
	// if the two first cards in the player's main hand have the same face, they can be split
	splitable = (player.GetSingleHand(0)[0].GetFace() == player.GetSingleHand(0)[1].GetFace());

	// show cards
	cout << "House: " << endl;
	ViewPlayerGame(&dealer, false);
	cout << "You: " << endl;
	ViewPlayerGame(&player);
	
	// if dealer has A showing
	if (risky)
	{
		OfferSurrender();
	}	
	// if any of the players got a natural blackjack, jump to Finish Round
	if (CheckPlayerCards(&dealer, &beginningRound) == 2 || CheckPlayerCards(&player, &beginningRound) == 2)
	{
		FinishRound();
	}	
	// if not, play as usual
	else
	{
		// player's turn
		cout << "---------------- Your Turn ------------------" << endl;
		
		if (!finishedRound)
		{
			bool all21{ true };
			bool allBusted{ true };
			LetPlayerPlay(&all21, &allBusted);


			if (!all21 && !allBusted)
			{
				// house's turn
				cout << "-------------- House Turn ------------------" << endl;
				LetHousePlay();
			}

			// finish round
			FinishRound();
		}
	}
	cout << "----------------------------------------------" << endl;	
}

Card Match::DrawCard() {
	if (deck->GetDeckSize() < 1)
	{
		// create new deck
		deck = new Deck();
		// shuflle deck
		deck->Shuffle(SHUFFLES);
	}
	return deck->GetCard();
}

void Match::DealInitialHands()
{
	for (size_t i{ 0 }; i < players.size(); i++)
	{
		for (size_t j{ 0 }; j < players[i]->INITIAL_HAND_SIZE; j++)
		{
			dealer.DealCard(DrawCard(), players[i]);
		}
		CalculatePlayerScore(players[i]);
	}
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

void Match::OfferSurrender()
{
	cout << "Dealer has an A. Do you wish to surrender? (Y / N)" << endl;
	char option{};

	while (cin >> option)
	{
		if (option == 'Y' || option == 'y')
		{
			FinishRound(true);
			return;
		}
		else if (option == 'N' || option == 'n')
		{
			ApplyInsurance();
			return;
		}
		else
		{
			cout << "Option invalid. Please enter a valid choice." << endl;
			Common::FlushInput();
		}
	}
}

void Match::ApplyInsurance()
{
	if (player.ValidateBet(bets[0], 1.5))
	{
		insuranceApplied = true;
		insuranceValue = (int)round(bets[0] / 2);
		cout << "Insurance automatically applied to your bet. Additional " << bets[0] / 2 << " colleted." << endl;
		cout << "If dealer has a Blackjack, you'll get " << bets[0] << " back." << endl;
	}
}

void Match::LetPlayerPlay(bool* all21, bool* allBusted)
{
	bool stillPlaying = true;
	
	// play all hands
	while (stillPlaying)
	{
		int i{ 0 };
		for (bool handActive : player.GetHandsStatus())
		{
			stillPlaying = (handActive && stillPlaying);
			if (handActive)
			{
				GetPlay(&beginningRound, &splitable, i);
			}
			i++;
		}
	}

	// check if any of the player's hand still has a wiinning chance	
	int i{ 0 };
	for (vector<Card> hand : player.GetHands())
	{
		int handResult = CheckPlayerCards(&player, false, i);
		bool handWon = (handResult == 2 || handResult == 3);
		*all21 = (all21 && handWon);
		bool handBusted = (handResult == 1);
		*allBusted = (allBusted && handBusted);
		i++;
	}
}

void Match::LetHousePlay()
{
	dealerPlayed = true;
	dealer.GetCard(0, 0)->Flip();
	dealer.ViewSingleHand();
	/*if (dealer.GetHandScore() <= 17)
	{*/
		while (dealer.GetHandScore() < 17)
		{
			Hit(&dealer);
		}
	//}
}

void Match::GetPlay(bool* beginningRound, bool* splitable, int hand)
{
	// get the player's choice of play
	cout << "Please enter an option" << (player.GetHands().size() > 1 ? " for Hand " + to_string(hand + 1) + ":" : ":") << endl;
	if (*beginningRound) 
	{
		if (*splitable)
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
		if ((option == 'P' || option == 'p') && *beginningRound && *splitable)
		{
			Split();
			break;
		}
		else if ((option == 'D' || option == 'd') && *beginningRound)
		{
			DoubleDown();
			break;
		}
		else if (option == 'H' || option == 'h')
		{
			Hit(&player, hand);
			break;
		}
		else if (option == 'S' || option == 's')
		{
			player.Stay(hand);
			break;
		}
		else
		{
			cout << "Option invalid. Please enter a valid play." << endl;
			Common::FlushInput();
		}
	}
	*beginningRound = false;
}

void Match::Hit(Player* currentPlayer, int hand)
{
	dealer.DealCard(DrawCard(), currentPlayer, hand);
	CalculatePlayerScore(currentPlayer, hand);
	ViewPlayerGame(currentPlayer, true, hand);
	CheckPlayerCards(currentPlayer, false, hand);
}

void Match::Split()
{
	if (player.ValidateBet(bets[0], 4))
	{
		bets[0] *= 2;
		bets.push_back(bets[0]);
		roundCredits = player.GetCredits() - (bets[0] * 2);
		cout << "Now betting $" << bets[0] << " on each hand" << endl;
		player.Split();
	}
	else
	{
		cout << "Insuficient credits to split. Please choose another play." << endl;
		GetPlay(&beginningRound, &splitable, 0);
	}

	int i{0};
	for (vector<Card> hand : player.GetHands())
	{
		Hit(&player, i);
		i++;
	}
}

void Match::DoubleDown()
{
	if (player.ValidateBet(bets[0], 2))
	{
		bets[0] *= 2;
		cout << "Bet of $" << bets[0] / 2 << " doubled. Current bet is $" << bets[0] << endl;
		Hit(&player);
		player.Stay();
	}
	else
	{
		cout << "Insuficient credits to double. Please choose another play." << endl;
		GetPlay(&beginningRound, &splitable, 0);
	}
}

void Match::FinishRound(bool surrender)
{
	cout << "------------ Finishing Round ---------------" << endl;
	if (!surrender)
	{
		cout << "--------- House ---------" << endl;
		if (dealer.GetCard(0, 0)->GetFaceUp() == false)
		{
			dealer.GetCard(0, 0)->Flip();
		}
		ViewPlayerGame(&dealer, ((dealerPlayed || CheckPlayerCards(&dealer, &beginningRound) == 2) ? true : false));

		cout << "---------- You ----------" << endl;
		int i{ 0 };
		int dealerRoundResult = dealer.GetHandScore();
		for (vector<Card> hand : player.GetHands())
		{
			ViewPlayerGame(&player, true, i);
			int handRoundResult = player.GetHandScore(i);
			int handSize = player.GetSingleHand(i).size();
			int handResultCheck{ 0 };
			if (handRoundResult > 21)
			{
				handResultCheck = 0; // player busted
			}
			else if (dealerRoundResult > 21)
			{
				handResultCheck = 1; // dealer busted
			}
			else if (handRoundResult == 21 && handSize == 2)
			{
				handResultCheck = 2; // player's blackjack
			}
			else if (handRoundResult == 21 && handSize > 2)
			{
				handResultCheck = 3; // player's long 21
			}
			else if (handRoundResult > dealerRoundResult)
			{
				handResultCheck = 4; // player got closer to 21
			}
			else if (handRoundResult < dealerRoundResult)
			{
				handResultCheck = 5; // dealer got closer to 21
			}
			else if (handRoundResult == dealerRoundResult)
			{
				handResultCheck = 6; // tie
			}
			else
			{
				handResultCheck = 100; // something wrong happened
			}
			PayBet(handResultCheck, i);
			i++;
			cout << "-------------------------" << endl;
		}
		if (insuranceApplied)
		{
			dealerRoundResult == 21 ? PayBet(8) : PayBet(9);
		} 
	}
	else
	{
		PayBet(7);
	}

	// reset round controls
	roundCredits = 0;
	bets = *(new vector<int>(1));
	for (Player* currentPlayer : players)
	{
		currentPlayer->FinishRound();
	}
	dealerPlayed = false;
	finishedRound = true;
	insuranceApplied = false;
}

void Match::FinishGame()
{
	gameStatus = over;
	cout << "Thanks for playing!" << endl;
}

void Match::CalculatePlayerScore(Player * currentPlayer, int hand)
{
	string TEMP;
	for (Card card : currentPlayer->GetSingleHand(0))
	{
		TEMP = (card.GetFaceValue() == 11 ? TEMP + card.GetFace() : TEMP);
		TEMP = (card.GetFaceValue() == 10 ? TEMP + card.GetFace() : TEMP);
	}
	if (TEMP.size() > 3)
	{
		cout << "TEMP: " << TEMP << endl;
	}
	
	int handScore{ 0 };
	int i{ 0 };
	int As{ 0 };
	for (Card card : currentPlayer->GetSingleHand(hand))
	{
		// loop through regular cards first to assess how As should behave
		if (card.GetFace() != "A")
		{
			handScore += card.GetFaceValue();
		}
		else
		{
			As++;
		}
		i++;
	}

	// loop through As
	for (int j{ 0 }; j < As; j++)
	{
		handScore += DecideAValue(handScore);
	}
	
	// set player's score to the determined value
	currentPlayer->SetHandScore(handScore, hand);
}

int Match::CheckPlayerCards(Player* currentPlayer, bool beginningRound, int hand)
{
	int handScore = currentPlayer->GetHandScore(hand);
	int handSize = currentPlayer->GetSingleHand(hand).size();

	if (handScore >= 21)
	{
		currentPlayer->SetHandStatus(hand, false); // stop that hand from playing any further
		if (handScore > 21 && !beginningRound)
		{
			return 1;
		}
		else //handScore = 21
		{
			if (handSize == 2) // a Blackjack can only be accomplished by 2 cards
			{
				return 2;
			}
			else
			{
				return 3;
			}
		}
	}
	else
	{
		return 0;
	}
}

void Match::ViewPlayerGame(Player* currentPlayer, bool showScore, int hand)
{
	currentPlayer->GetHands().size() > 1 ? currentPlayer->ViewSingleHand(hand, true) : currentPlayer->ViewSingleHand(hand);
	
	if (showScore)
	{
		cout << "Hand total: " << currentPlayer->GetHandScore(hand) << endl;
	}
	cout << "-------------------------" << endl;
}

void Match::PayBet(int playerResult, int hand)
{
	switch (playerResult)
	{
		case 0: // player busted
		case 5: // dealer closer to 21
		{
			cout << "Collecting $" << bets[hand] << endl;
			player.AdjustCredits(-bets[hand]);
			cout << "Current Credits: $" << player.GetCredits() << endl;
			break; 
		}
		case 2: // player's blackjack
		{
			int pay{ (int)round(bets[hand] * 1.5) };
			cout << "Receiving $" << abs(pay) << endl;
			player.AdjustCredits(pay);
			cout << "Current Credits: $" << player.GetCredits() << endl;
			break; 
		}
		case 1: // dealer busted
		case 3: // player's long 21
		case 4: // player closer to 21
		{
			int pay{ (int)round(bets[hand] * 2.5) };
			cout << "Receiving $" << abs(pay) << endl;
			player.AdjustCredits(pay);
			cout << "Current Credits: $" << player.GetCredits() << endl; 
			break;
		}
		case 6: // tie
		{
			cout << "Tie. No credits collected or received." << endl;
			cout << "Current Credits: $" << player.GetCredits() << endl;
			break;
		}
		case 7: // surrender
		{
			int pay{ -(int)round(bets[0] / 2) };
			player.AdjustCredits(pay);
			cout << "Receiving $" << abs(pay) << " back" << endl;
			cout << "Current Credits: $" << player.GetCredits() << endl;
			break;
		}
		case 8: // insurance applied & dealer got BlackJack
		{	
			int pay{ (int)(insuranceValue * 2)  };
			player.AdjustCredits(pay);
			cout << "Receiving $" << abs(pay) << " from insurance" << endl;
			cout << "Current Credits: $" << player.GetCredits() << endl;
			break; 
		}
		case 9: // insurance applied and dealer didn't get a Blackjack
		{
			int pay{ (int)-insuranceValue };
			player.AdjustCredits(pay);
			cout << "Collecting $" << abs(pay) << " from insurance" << endl;
			cout << "Current Credits: $" << player.GetCredits() << endl;
			break;
		}
		case 100: // error
		default:
		{
			cout << "Couldn't resolve bet payment" << endl;
			break; 
		}
	}
}

int Match::DecideAValue(int baseScore)
{
	return (baseScore + 11 > 21 ? 1 : 11);
}

