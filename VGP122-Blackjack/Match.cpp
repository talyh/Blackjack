#include "Match.h"

// initialize timer variables
int				deltaT = 75;	// defines delay in time for updating game loop
int				updatedTime = 0;	// used to determine if frame rate interval has elapsed

// initialize Event Variables
SDL_Event matchEvent;

// define overal layout elements
// avatar
Sprite *avatar = NULL;
const Size AVATAR_SIZE{ 72, 72 };
const string AVATAR_IMAGE = "imgs/avatar.png";
const Position AVATAR_POSITION { 
	PADDING , 
	SCREEN_HEIGHT - AVATAR_SIZE.height - PADDING 
};

// credits
Textbox lblCredits {
	"lblCredits",
	AVATAR_POSITION.xPos + AVATAR_SIZE.width + PADDING, 
	AVATAR_POSITION.yPos, 
	0, 
	0, 
	"Credits: " 
};
Textbox txtCredits { "txtCredits" };

// bets
const int LBL_BET_INITIAL_WIDTH = 50;
Textbox lblBet1 {
	"lblBet1",
	SCREEN_WIDTH / 6 - LBL_BET_INITIAL_WIDTH,
	SCREEN_HEIGHT - AVATAR_SIZE.height - PADDING * 5,
	0,
	0,
	"Bet: "
};
Textbox txtBet1 {};
Textbox lblBet2 {
	"lblBet2",
	SCREEN_WIDTH / 6 - LBL_BET_INITIAL_WIDTH,
	SCREEN_HEIGHT - AVATAR_SIZE.height - PADDING * 5,
	0,
	0,
	"Bet: "
};
Textbox txtBet2 {};
Button btnBetUp1{
	"btnBetUp1",
	{
		SCREEN_WIDTH / 6 + 50,
		lblBet1.position.yPos - BET_BUTTON_SIZE.height / 2 - 8
	},
	BET_BUTTON_SIZE,
	BTN_BET_UP_IMAGE,
	new Sprite(BTN_BET_UP_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
};
Button btnBetDown1 {
	"btnBetDown1",
	{
		SCREEN_WIDTH / 6 + 50,
		lblBet1.position.yPos + BET_BUTTON_SIZE.height / 2 + 8
	},
	BET_BUTTON_SIZE,
	BTN_BET_DOWN_IMAGE,
	new Sprite(BTN_BET_DOWN_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
};
Button btnBetConfirm1 {
	"btnConfirm1",
	{
		btnBetUp1.position.xPos + BET_BUTTON_SIZE.width + 8,
		lblBet1.position.yPos + BET_BUTTON_SIZE.height / 2
	},
	BET_BUTTON_SIZE,
	BTN_BET_CONFIRM_IMAGE,
	new Sprite(BTN_BET_CONFIRM_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
};
Button btnHit {
	"btnHit",
	{ 
		PADDING,
		SCREEN_HEIGHT / 2
	},
	PLAY_BUTTON_SIZE,
	BTN_HIT_IMAGE,
	new Sprite(BTN_HIT_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
	SFX_HIT,
	{ 40, 23 },
	BTN_HIT_TOOLTIP,
	new Sprite(BTN_HIT_TOOLTIP.c_str(), 0, 0, 0, 0, nullptr)
};
Button btnStay{
	"btnStay",
	{
		btnHit.position.xPos,
		btnHit.position.yPos + btnHit.size.height + BUTTON_PADDING,
	},
	PLAY_BUTTON_SIZE,
	BTN_STAY_IMAGE,
	new Sprite(BTN_STAY_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
	SFX_STAY,
	{ 50, 23 },
	BTN_STAY_TOOLTIP,
	new Sprite(BTN_STAY_TOOLTIP.c_str(), 0, 0, 0, 0, nullptr)
};
Button btnDoubleDown {
	"btnDoubleDown",
	{
		btnStay.position.xPos,
		btnStay.position.yPos + btnHit.size.height + BUTTON_PADDING,
	},
	PLAY_BUTTON_SIZE,
	BTN_DOUBLE_DOWN_IMAGE,
	new Sprite(BTN_DOUBLE_DOWN_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
	SFX_DOUBLE_DOWN,
	{ 113, 23 },
	BTN_DOUBLE_DOWN_TOOLTIP,
	new Sprite(BTN_DOUBLE_DOWN_TOOLTIP.c_str(), 0, 0, 0, 0, nullptr)
};
Button btnSplit {
	"btnSplit",
	{
		btnDoubleDown.position.xPos,
		btnDoubleDown.position.yPos + btnHit.size.height + BUTTON_PADDING,
	},
	PLAY_BUTTON_SIZE,
	BTN_SPLIT_IMAGE,
	new Sprite(BTN_SPLIT_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
	SFX_DOUBLE_DOWN,
	{ 50, 23 },
	BTN_SPLIT_TOOLTIP,
	new Sprite(BTN_SPLIT_TOOLTIP.c_str(), 0, 0, 0, 0, nullptr)
};
Button btnSurrender {
	"btnSurrender",
	{
		btnSplit.position.xPos,
		btnSplit.position.yPos + btnHit.size.height + BUTTON_PADDING,
	},
	PLAY_BUTTON_SIZE,
	BTN_SURRENDER_IMAGE,
	new Sprite(BTN_SURRENDER_IMAGE.c_str(), 0, 0, 0, 0, nullptr),
	"",
	{ 93, 23 },
	BTN_SURRENDER_TOOLTIP,
	new Sprite(BTN_SURRENDER_TOOLTIP.c_str(), 0, 0, 0, 0, nullptr)
};


// hands
const int CARD_PADDING { 15 };
const Position DEALER_HAND { SCREEN_WIDTH / 2 - CARD_WIDTH , PADDING };
const Position PLAYER_HAND { SCREEN_WIDTH / 2 - CARD_WIDTH, SCREEN_HEIGHT - CARD_HEIGHT - PADDING * 4 };

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

void Match::PlayGame()
{
	gameStatus = running;
	GameRender::ClearScreen();

	// shuflle deck
	deck->Shuffle(SHUFFLES);

	// game runs while player has creddits
	// if cards run out, a new deck is used
	while (player.GetCredits() > initialBet)
	{
		PlayRound();
	}
	FinishGame();
}

void Match::PlayRound()
{
	beginningRound = true;
	finishedRound = false;

	while (!finishedRound)
	{
		GameRender::ClearScreen(true);
		// show avatar
		GameRender::DrawElement(AVATAR_IMAGE, AVATAR_POSITION.xPos, AVATAR_POSITION.yPos, AVATAR_SIZE.width, AVATAR_SIZE.height, &avatar);

		// show credits
		GameRender::PrintText(&lblCredits, true);
		txtCredits.value = to_string(player.GetCredits());
		txtCredits.position.xPos = lblCredits.position.xPos + lblCredits.size.width + PADDING;
		txtCredits.position.yPos = lblCredits.position.yPos,
		GameRender::PrintText(&txtCredits);

		// get bet
		bool betting = true;
		GetBet(&betting);

		// redraw screen
		GameRender::ClearScreen();
		GameRender::DrawElement(AVATAR_IMAGE, AVATAR_POSITION.xPos, AVATAR_POSITION.yPos, AVATAR_SIZE.width, AVATAR_SIZE.height, &avatar);
		GameRender::PrintText(&lblCredits, true);
		GameRender::PrintText(&txtCredits);

		// deal cards
		DealInitialHands();
		// TODO - hide first card

		// TODO
		// check for immediate blackjacks
		//for (Player* p : players)
		//{
		//	CalculatePlayerScore(p);
		//}

		// show options
		GameRender::DrawElement(&btnHit);
		GameRender::DrawElement(&btnStay);
		if (beginningRound)
		{
			GameRender::DrawElement(&btnDoubleDown);
			if (player.GetSplitable())
			{
				GameRender::DrawElement(&btnSplit);
			}
			if (dealer.GetHandRisk())
			{
				GameRender::DrawElement(&btnSurrender);
				// TODO - add call to insurance
			}
		}
		
		// get play
		bool gettingPlay = true;
		//GetPlay();
	}
	
	//for (Player* p : players)
	//{
	//	CalculatePlayerScore(p);
	//}
	///* -----------------------------------------------------------------------------------------*/
	//// ------------------------------------- REVIEW --------------------------------------------
	//// if the two first cards in the player's main hand have the same face, they can be split
	////splitable = (player.GetSingleHand(0)[0].GetFace() == player.GetSingleHand(0)[1].GetFace());
	///* -----------------------------------------------------------------------------------------*/

	//// show cards
	//cout << "House: " << endl;
	//ViewPlayerGame(&dealer, false);
	//cout << "You: " << endl;
	//ViewPlayerGame(&player);
	//
	//// if dealer has a risky hand
	//if (dealer.GetHandRisk())
	//{
	//	OfferSurrender();
	//}	
	//// if any of the players got a natural blackjack, jump to Finish Round
	//if (CheckPlayerCards(&dealer, &beginningRound) == 2 || CheckPlayerCards(&player, &beginningRound) == 2)
	//{
	//	FinishRound();
	//}	
	//// if not, play as usual
	//else
	//{
	//	// player's turn
	//	cout << "---------------- Your Turn ------------------" << endl;
	//	
	//	if (!finishedRound)
	//	{
	//		bool all21{ true };
	//		bool allBusted{ true };
	//		LetPlayerPlay(&all21, &allBusted);


	//		if (!all21 && !allBusted)
	//		{
	//			// house's turn
	//			cout << "-------------- House Turn ------------------" << endl;
	//			LetHousePlay();
	//		}

	//		// finish round
	//		FinishRound();
	//	}
	//}
	//cout << "----------------------------------------------" << endl;	
}

Card* Match::DrawCard() {
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
			Card* c = DrawCard();
			dealer.DealCard(c, players[i]);
			GameRender::DrawElement(c, (i == 0 ? DEALER_HAND : PLAYER_HAND) + (CARD_PADDING * j));
		}
	}
}

void Match::GetBet(bool listening)
{
	bets[0] = initialBet;
	roundCredits = player.GetCredits() - bets[0];
	txtCredits.value = to_string(roundCredits);
	txtBet1.value = to_string(bets[0]);
	
	GameRender::ClearScreen(true);
	GameRender::PrintText(&lblBet1, true);
	GameRender::DrawElement(&btnBetUp1);
	GameRender::DrawElement(&btnBetDown1);
	GameRender::DrawElement(&btnBetConfirm1);

	while (listening)
	{
		if (SDL_GetTicks() - updatedTime >= deltaT)
		{
			txtBet1.position = { lblBet1.position.xPos + lblBet1.size.width + PADDING , lblBet1.position.yPos }; 
			GameRender::PrintText(&txtCredits);
			GameRender::PrintText(&txtBet1);
			
			while (SDL_PollEvent(&matchEvent))
			{
				switch (matchEvent.type)
				{
					// Check if user tries to quit the window
					case SDL_QUIT:
					{
						// Break out of loop to end game
						listening = false;
						exit(1);
						break;
					}
					//	Check if the ESC key was pressed
					case SDL_KEYDOWN:
					{
						//	Check if 'ESC' was pressed
						if (matchEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						{
							// Break out of loop to end game
							listening = false;
							exit(1);
						}
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						GameRender::PlaySound(SFX_BUTTON_CLICK);

						if (CollisionDetection::isColliding(matchEvent.motion.x, matchEvent.motion.y, btnBetUp1.image))
						{
							if (player.ValidateBet(bets[0] + betIncrement))
							{
								bets[0] += betIncrement;
								roundCredits = player.GetCredits() - bets[0];
							}
							else
							{	
								// print error message
							}
						}
						else if (CollisionDetection::isColliding(matchEvent.motion.x, matchEvent.motion.y, btnBetDown1.image))
						{
							if (bets[0] - betIncrement >= initialBet)
							{
								bets[0] -= betIncrement;
								roundCredits = player.GetCredits() - bets[0];
							}
							else
							{
								// print error message
							}
						}
						else if (CollisionDetection::isColliding(matchEvent.motion.x, matchEvent.motion.y, btnBetConfirm1.image))
						{
							listening = false;
						}

						GameRender::ClearScreen(true);
						txtCredits.value = to_string(roundCredits);
						txtBet1.value = to_string(bets[0]);
						break;
					}
				}
			}
			// update time
			updatedTime = SDL_GetTicks();
		}
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
				GetPlay(&beginningRound, player.GetSplitable() , i);
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
	dealer.ShowHiddenCards();
	dealer.ViewSingleHand();
	while (dealer.GetHandScore() < 17)
	{
		Hit(&dealer);
	}
}

void Match::GetPlay(bool* beginningRound, bool splitable, int hand)
{
	// get the player's choice of play
	cout << "Please enter an option" << (player.GetHands().size() > 1 ? " for Hand " + to_string(hand + 1) + ":" : ":") << endl;
	if (*beginningRound) 
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
		if ((option == 'P' || option == 'p') && *beginningRound && splitable)
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
		GetPlay(&beginningRound, player.GetSplitable(), 0);
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
		GetPlay(&beginningRound, player.GetSplitable(), 0);
	}
}

void Match::FinishRound(bool surrender)
{
	cout << "------------ Finishing Round ---------------" << endl;
	if (!surrender)
	{
		cout << "--------- House ---------" << endl;
		dealer.ShowHiddenCards();
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

	// clean items created
	for (void* item : itemsCreated)
	{
		delete item;
		item = nullptr;
	}
}

void Match::FinishGame()
{
	gameStatus = over;
	cout << "Thanks for playing!" << endl;
}

void Match::CalculatePlayerScore(Player * currentPlayer, int hand)
{
	int handScore{ 0 };
	int i{ 0 };
	int aces{ 0 };
	for (Card card : currentPlayer->GetSingleHand(hand))
	{
		// loop through regular cards first to assess how As should behave
		if (card.GetFace() != "A")
		{
			handScore += card.GetFaceValue();
		}
		else
		{
			aces++;
		}
		i++;
	}


	// if the accumulated Aces would bust the player's hand, count them as 1
	if (handScore + aces * 11 > 21)
	{
		handScore += aces;
	}
	else // loop through Aces, determining a value for each
	{
		for (int j{ 0 }; j < aces; j++)
		{
			handScore += DecideAValue(handScore);
		}
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

