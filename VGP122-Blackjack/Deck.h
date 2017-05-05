
class Deck {
public:
	explicit Deck() :
		/*test1{ 0 },
		test2{},*/
		cards(52)
	{
		// TEST - WHEN working, chance to foreach syntax
		for (size_t i{0}; i < cards.size(); i++)
		{
			cards[i] = i;
		}
	
		/*if (test2 == 0) { test2 = 50; }
		if (test1 == 0) { test1 = 25; }*/
	}
	void Shuffle()
	{
		std::cout << "deck size:" << cards.size() << std::endl;

		size_t shuffles{ 100 };
		for (size_t i{ 0 }; i < shuffles; i++)
		{
			int temp1 = rand() % 52;
			int temp2 = rand() % 52;

			cards[temp1] = temp2;
			cards.at(temp2) = temp1;
		}

		std::cout << "Shuffling" << std::endl;
		for (int card : cards)
		{
			std::cout << card << std::endl;
		}
	}


private:
	std::vector<int> cards;
	/*int test1;
	int test2;*/
};
