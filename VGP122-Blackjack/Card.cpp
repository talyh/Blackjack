#include "Card.h"

//Card::Card()
//{
//}

void Card::SetFaceValue(FACES face)
{
	switch (face)
	{
		case FACES::A : 
		{
			faceValue = 0;
			break; 
		}
		case FACES::Two :
		case FACES::Three :
		case FACES::Four :
		case FACES::Five :
		case FACES::Six :
		case FACES::Seven :
		case FACES::Eight :
		case FACES::Nine :
		{
			faceValue = (int)face + 1;
			break; 
		}
		case FACES::Ten :
		case FACES::J :
		case FACES::Q :
		case FACES::K :
		{
			faceValue = 10;
			break;
		}
	}
}

Card::FACES Card::GetFace()
{
	return face;
}

Card::SUITS Card::GetSuit()
{
	return suit;
}


int Card::GetFaceValue()
{
	return faceValue;
}

void Card::ViewCard()
{
	//cout << face << " of " << suit << " (worth " << faceValue << ")" << endl;
	//cout << Card::GetFace() << " of " << GetSuit() << " (worth " << GetFaceValue() << ")" << endl;
	//cout << GetStringFace(face) << " " << GetFaceValue() << ")" << endl;
	//cout << facesString[FACES::A];
}
