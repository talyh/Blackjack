#include <vector>

#ifndef DECK_H
#define DECK_H

class Deck {
public:
	explicit Deck() :
		cards(52)
	{
		for (size_t i{0}; i < cards.size(); i++)
		{
			cards[i] = i;
		}
	}
	
	void Shuffle(size_t shuffles);
	
	const int GetCard();
	
	void TEMP_ShowDeck();

private:
	std::vector<int> cards;
};
#endif
