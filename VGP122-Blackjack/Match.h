#include "Common.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"
#include "Human.h"

#ifndef MATCH_H
#define  MATCH_H

class Match
{
public:
	Match();

	int GetGameStatus();

	void StartGame();

	void PlayRound();

	Card GetCard();

	void DealCard(Card card, Player* player);

	void DealInitialHands();

	void GetBet();

	void GetPlay();

	void Split();

	void FinishRound();

	void CheckPoints(Player* currentPlayer, int hand = 0);

	void TEMP_ShowBets();

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
};

#endif
