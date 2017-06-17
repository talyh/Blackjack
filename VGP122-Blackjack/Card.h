#include "Common.h"
#include "Sprite.h"
//#include "GameRender.h"

#ifndef CARD_H
#define CARD_H

const array<string, 13> FACES{ "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
const array<string, 4> SUITS{ "Hearts", "Diamonds", "Clubs", "Spades" };

const string SPRITESHEET = CARDS_IMAGE;

class Card
{
public:
	Card();
	
	void SetFace(string face);
	void SetSuit(string suit);
	void SetFaceValue(string face);
	void SetImage();
	void DeleteImage();
	void Flip();

	const string GetFace();
	const string GetSuit();
	const int GetFaceValue();
	const bool GetFaceUp();
	Sprite* GetImage();

	void ViewCard();

private:
	string face;
	string suit;
	int faceValue;
	bool faceUp;
	Sprite* image;
};

#endif




