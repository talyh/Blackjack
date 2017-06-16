#ifndef MATCH_H
#define  MATCH_H

#include "Common.h"
#include "CollisionDetection.h"
#include "GameRender.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Human.h"


class Match
{
public:
	Match();

	int GetGameStatus();

	void PlayGame();

	void PlayRound();

	Card DrawCard();

	void DealInitialHands();

	void GetBet(bool listening);

	void OfferSurrender();

	void ApplyInsurance();

	void LetPlayerPlay(bool* all21, bool* allBusted);

	void LetHousePlay();

	void GetPlay(bool* beginningRound, bool splitable);

	void Hit(Player* currentPlayer, int hand = 0);

	void Split();

	void DoubleDown();

	void FinishRound(bool surrender = false);

	void FinishGame();

	void CalculatePlayerScore(Player* currentPlayer, int hand = 0);

	int CheckPlayerCards(Player* currentPlayer, bool beginningRound, int hand = 0); // returns 0 for Keep Playing
			// returns 1 for Busted
			// returns 2 for Natural Blackjack
			// returns 3 for 21 points

	//void ViewPlayerGame(Player* currentPlayer, bool showScore = true, int hand = 0);

	void PayBet(int playerResult, int hand = 0);

	int DecideAValue(int baseScore); // determines whether A should be counted as 1 or 11 and returns that value

	const enum GAMESTATUS { notStarted, running, over };
	
	static const int numberOfPlayers{ 2 };

	const int initialBet { 10 };
	const int betIncrement { 10 };

private:	
	const size_t SHUFFLES{ 100 }; // to determine how many times a deck should be shuffled on start
	GAMESTATUS gameStatus; // to keep track of the game status and flow
	Deck* deck; // to represent the deck of cards in use, can be replaced if the deck finishes
	Deck currentDeck; // to represent the deck currently in play
	vector<int> bets;	// to store the bets in play
							// 0 represents the player's basic bet
							// 1 represents an additional bet from a Split so each bet can be paid or collected separately
	int roundCredits; // to be able to show the player's credits as affected by the round choices
	array<Player*, numberOfPlayers> players; // to be able to list through the Player objects in the game
	Human player;
	Dealer dealer;

	bool beginningRound; // to determine if we're in the first dealing of a round
	bool dealerPlayed; // to determine whether to show the dealer's score at the end of a round
	bool finishedRound; // to determine whether the round is stll ongoing
	bool insuranceApplied; // to indicate whether the player has insurance for that round
	int insuranceValue; // to store the value of the insurance
	
	vector <void*> itemsCreated;
};

#endif
