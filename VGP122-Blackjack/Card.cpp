#include "Card.h"

Card::Card()
{
	faceUp = true;
	image = nullptr;
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

void Card::SetImage()
{
	image = new Sprite(SPRITESHEET.c_str(), 0, 0, SIZE.width, SIZE.height);
	if (suit == "Clubs")
	{
		image->setRow(0);
	}
	else if (suit == "Spades")
	{
		image->setRow(1);
	}
	else if (suit == "Hearts")
	{
		image->setRow(2);
	}
	else if (suit == "Diamonds")
	{
		image->setRow(3);
	}
	else
	{
		cout << "Couldn't resolve card spritesheet row" << endl;
	}

	if (face == "A")
	{
		image->setCurrentFrame(0);
	}
	else if (face == "2")
	{
		image->setCurrentFrame(1);
	}
	else if (face == "3")
	{
		image->setCurrentFrame(2);
	}
	else if (face == "4")
	{
		image->setCurrentFrame(3);
	}
	else if (face == "5")
	{
		image->setCurrentFrame(4);
	}
	else if (face == "6")
	{
		image->setCurrentFrame(5);
	}
	else if (face == "7")
	{
		image->setCurrentFrame(6);
	}
	else if (face == "8")
	{
		image->setCurrentFrame(7);
	}
	else if (face == "9")
	{
		image->setCurrentFrame(8);
	}
	else if (face == "10")
	{
		image->setCurrentFrame(9);
	}
	else if (face == "J")
	{
		image->setCurrentFrame(10);
	}
	else if (face == "Q")
	{
		image->setCurrentFrame(11);
	}
	else if (face == "K")
	{
		image->setCurrentFrame(12);
	}
}

void Card::DeleteImage()
{
	delete image;
	image = nullptr;
}

void Card::Flip()
{
	faceUp = !faceUp;
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

Sprite* Card::GetImage()
{
	return image;
}

void Card::ViewCard()
{
	cout << GetFace() << " of " << GetSuit() << " (worth " << (face == "A" ? "1 / 11" : to_string(GetFaceValue())) << ")" << endl;
}
