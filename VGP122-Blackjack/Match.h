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

	void Bet(int bet);

	void GetPlay();

	void Split();

	void FinishRound();

	void TEMP_ShowBets();

	const enum GAMESTATUS { notStarted, running, over };
private:
	const size_t SHUFFLES{ 100 }; // to determine how many times a deck should be shuffled on start
	GAMESTATUS gameStatus; // to keep track of the game status and flow
	Deck deck; // to represent the deck of cards in use
	vector<int> bets;	// to store the bets in play
							// 0 represents the player's basic bet
							// 1 represents an additional bet from a Split
	array<Player*, 2> players;
	Human player;
	Dealer dealer;
};

#endif
