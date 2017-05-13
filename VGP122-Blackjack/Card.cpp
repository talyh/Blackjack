#include "Card.h"

Card::Card()
{
	faceUp = true;
}

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

void Card::Flip()
{
	faceUp == !faceUp;
}

const string Card::GetFace()
{
	return face;
}

const string Card::GetSuit()
{
	return suit;
}

const int Card::GetFaceValue()
{
	return faceValue;
}

const bool Card::GetFaceUp()
{
	return faceUp;
}

void Card::ViewCard()
{
	cout << GetFace() << " of " << GetSuit() << " (worth " << (face == "A" ? "1 / 11" : to_string(GetFaceValue())) << ")" << endl;
}
