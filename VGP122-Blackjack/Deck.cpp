#include "Deck.h"

Deck::Deck() : cards(FACES.size() * SUITS.size())
{
	for (size_t i{ 0 }; i < cards.size(); i++)
	{
		cards[i].SetFace(FACES[i % FACES.size()]);
		cards[i].SetSuit(SUITS[i / FACES.size()]);
		cards[i].SetFaceValue(cards[i].GetFace());
	}
}

void Deck::Shuffle(size_t shuffles)
{
	for (size_t i{ 0 }; i < shuffles; i++)
	{
		size_t j = (i >= FACES.size() * SUITS.size() ? shuffles % (FACES.size() * SUITS.size()) : i);
		size_t r{ rand() % (FACES.size() * SUITS.size()) };

		Card temp = cards[j];
		cards[j] = cards[r];
		cards[r] = temp;
	}
}

const Card Deck::GetCard()
{
	Card selected = cards[0];
	cards.erase(cards.begin() + 0);
	return selected;
}

// TODO Remove at the end
void Deck::TEMP_ShowDeck()
{
	cout << "Deck Size: " << cards.size() << endl;
	for (Card card : cards)
	{
		card.ViewCard();
	}
}
