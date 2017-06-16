#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"
#include "GameRender.h"
#include "Card.h"

class Player
{
public:
	Player();

	virtual void ReceiveCard(Card* card, int hand = 0); // puts a card in the player's hand
	
	void Stay(int hand = 0);

	Card* GetCard(int hand, int position);

	vector<Card*> GetSingleHand(int hand); // returns the raw vector of one of the player's hands

	vector<vector<Card*>> GetHands(); // returns the raw vector of hands

	vector<bool> GetHandsStatus();	// returns the status of all the player's hands
									// FALSE for a hand that has finished playing
									// TRUE for a hand that is still playing

	bool GetFirstHandStatus();

	bool GetSecondHandStatus();

	int GetHandScore(int hand = 0); // returns the current points accumulated for a given hand
	
	void SetHandStatus(int hand, bool handStatus); // sets the status of a hand
												   // FALSE for a hand that has finished playing
												   // TRUE for a hand that is still playing
												   // the hand integer parameter corresponds to the hand position in the Hands vector

	void SetHandScore(int score, int hand = 0); // sets the hand score for a given hand

	void ViewSingleHand(int hand = 0, bool showHandNumber = false); // shows all cards in a single hand in a text format

	void FinishRound(); // resets the player's hands and hands controls

	void ShowHiddenCards();

	static const int INITIAL_HANDS{ 1 };
	static const int INITIAL_HAND_SIZE{ 2 };

protected:
	virtual void AdditionalTasksOnReceiveCard();
	
	vector<vector<Card*>> hands; // to store the Cards the player is holding, allowing for multiple hands at the same time
	vector<bool> handsActive; // to control whether each hand is active or not
	vector<int> handsScore; // to control the accumulated score for each hand
	string type; // to store the type of player (guest or dealer)
};

#endif