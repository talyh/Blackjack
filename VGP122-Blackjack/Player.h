#include "Common.h"
#include "Card.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	Player();

	virtual void ReceiveCard(Card card, int hand = 0); // puts a card in the player's hand

	Card GetCard(int hand, int position);

	vector<Card> GetSingleHand(int hand); // returns the raw vector of one of the player's hands

	vector<vector<Card>> GetHands(); // returns the raw vector of hands

	bool GetHandStatus(int hand); // returns the status of a hand
									// FALSE for a hand that has finished playing
									// TRUE for a hand that is still playing
									// the hand integer parameter corresponds to the hand position in the Hands vector

	void SetHandStatus(int hand, bool handStatus); // sets the status of a hand
												   // FALSE for a hand that has finished playing
												   // TRUE for a hand that is still playing
												   // the hand integer parameter corresponds to the hand position in the Hands vector

	void ViewHands(); // Shows all cards in all hands in a text format

	static const int INITIAL_HANDS{ 1 };
	static const int INITIAL_HAND_SIZE{ 2 };

	char TEMPname = 'p';
protected:
	vector<vector<Card>> hands;
	vector<bool> handsActive;
};

#endif