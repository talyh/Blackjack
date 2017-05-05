
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
	void Shuffle(size_t shuffles)
	{
		/*std::cout << "deck size:" << cards.size() << std::endl;
		std::cout << "Shuffling" << std::endl;*/

		for (size_t i{ 0 }; i < shuffles; i++)
		{
			int temp1 = rand() % 52;
			int temp2 = rand() % 52;

			cards[temp1] = temp2;
			cards.at(temp2) = temp1;
		}
	}
	int DealCard()
	{
		int selected = cards[rand() % cards.size()];
		cards.erase(cards.begin() + cards.at(selected));
		return selected;
	}

	// TODO Remove at the end
	void TEMP_ShowDeck()
	{
		int i{ 0 };
		for (int card : cards)
		{
			std::cout << i++ << ". " << card << std::endl;
		}
	}

private:
	std::vector<int> cards;
};
