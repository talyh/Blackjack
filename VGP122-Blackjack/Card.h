#include "Common.h"

#ifndef CARD_H
#define CARD_H

class Card
{
public:
	const enum class SUITS {Hearts = 0, Diamonds, Clubs, Spades };
	const enum class FACES {A = 0, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, J, Q, K};

	void SetFace(FACES face);
	void SetSuit(SUITS suit);
	void SetFaceValue(FACES face);

	FACES GetFace();
	SUITS GetSuit();
	int GetFaceValue();

	void ViewCard();

	SUITS suit;
	FACES face;
	int faceValue;

	string GetStringFace(FACES face)
	{
		//string value = facesString[face];
			return facesString[face];
	}

private:
	static map<FACES, string> facesString;
		
	static void GenerateFacesMap()
	{
		if (facesString.size() == 0) 
		{
			facesString.insert(pair<FACES, string>(FACES::A, "A"));
			facesString.insert(pair<FACES, string>(FACES::Two, "2"));
			facesString.insert(pair<FACES, string>(FACES::Three, "3"));
			facesString.insert(pair<FACES, string>(FACES::Four, "4"));
			facesString.insert(pair<FACES, string>(FACES::Five, "5"));
			facesString.insert(pair<FACES, string>(FACES::Six, "6"));
			facesString.insert(pair<FACES, string>(FACES::Seven, "7"));
			facesString.insert(pair<FACES, string>(FACES::Eight, "8"));
			facesString.insert(pair<FACES, string>(FACES::Nine, "9"));
			facesString.insert(pair<FACES, string>(FACES::Ten, "10"));
			facesString.insert(pair<FACES, string>(FACES::J, "J"));
			facesString.insert(pair<FACES, string>(FACES::Q, "Q"));
			facesString.insert(pair<FACES, string>(FACES::K, "K"));
		}
	}
};

#endif




