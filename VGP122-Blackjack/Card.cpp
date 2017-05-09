#include "Card.h"

void Card::SetFace(string face)
{
	this->face = face;
}

void Card::SetSuit(string suit)
{
	this->suit = suit;
}

void Card::SetFaceValue(string face)
{
	faceValue = face == "A" ? 11 : (face == "J" || face == "Q" || face == "K") ? 10 : stoi(face);
}

string Card::GetFace()
{
	return face;
}

string Card::GetSuit()
{
	return suit;
}


int Card::GetFaceValue()
{
	return faceValue;
}

void Card::ViewCard()
{
	cout << GetFace() << " of " << GetSuit() << " (worth " << GetFaceValue() << ")" << endl;
}
