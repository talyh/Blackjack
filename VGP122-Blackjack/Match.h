#ifndef MATCH_H
#define  MATCH_H

#include "Common.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Human.h"

class Match
{
public:
	Match();

	int GetGameStatus();

	void StartGame();

	void PlayRound();

	Card DrawCard();

	void DealInitialHands();

	void GetBet();

	void OfferInsurance();

	void OfferSurrender();

	void GetPlay(int hand = 0, bool beginningRound = false, bool splitable = false);

	void Hit(Player* currentPlayer, int hand = 0);

	void Split();

	/*void DoubleDown(); {double bet, hit, stay} */

	void FinishRound();

	void FinishGame();

	void CalculatePlayerScore(Player* currentPlayer, int hand = 0);

	int CheckPlayerCards(Player* currentPlayer, bool beginningRound, int hand = 0); // returns 0 for Keep Playing
			// returns 1 for Busted
			// returns 2 for Natural Blackjack
			// returns 3 for 21 points

	void ViewPlayerGame(Player* currentPlayer, bool showScore = true, int hand = 0);

	void PayBet(int playerResult, int hand = 0);

	static const enum GAMESTATUS { notStarted, running, over };
	
	static const int numberOfPlayers{ 2 };
private:
	const size_t SHUFFLES{ 100 }; // to determine how many times a deck should be shuffled on start
	GAMESTATUS gameStatus; // to keep track of the game status and flow
	Deck deck; // to represent the deck of cards in use
	vector<int> bets;	// to store the bets in play
							// 0 represents the player's basic bet
							// 1 represents an additional bet from a Split so each bet can be paid or collected separately
	int roundCredits; // to be able to show the player's credits as affected by the round choices
	array<Player*, numberOfPlayers> players; // to be able to list through the Player objects in the game
	Human player;
	Dealer dealer;

	bool beginningRound; // to determine if we're in the first dealing of a round
	bool finishedRound; // to determine if we should continue offering plays for this round
	bool risky; // to determine if the player should be allowed to take Insurance or Surrender
	bool splitable; // to determine if the hand can be split
};

#endif
