#include <vector>
#include "Deck.h"

#ifndef MATCH_H
#define  MATCH_H

class Match
{
public:
	explicit Match() : gameStatus{ notStarted } {}

	int GetGameStatus();

	void StartGame();

	void StartRound();

	void DealCard();

	void PlaceBet(int credits);

	void Split();

	void FinishRound();

	void TEMP_ShowBets();

	const enum GAMESTATUS { notStarted, running, over };
private:
	const size_t SHUFFLES{ 100 }; // to determine how many times a deck should be shuffled on start
	GAMESTATUS gameStatus; // to keep track of the game status and flow
	Deck deck; // to represent the deck of cards in use
			   /*std::vector<std::vector<int>> hands;*/ // to store the hands of the dealer and player and which cards are being held. 
														// vector 0 represent the dealer
														// 1 repreent the player's basic hand
														// 2 represent an additional hand from a Split
	std::vector<int> bets;	// to store the bets in play
							// 0 represents the player's basic bet
							// 1 represents an additional bet from a Split
};

#endif
