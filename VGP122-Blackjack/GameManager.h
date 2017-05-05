#include "Deck.h"

class GameManager
{
public:
	explicit GameManager() : gameStatus{ notStarted } {}
	int GetGameStatus()
	{
		return gameStatus;
	}
	
	void StartGame()
	{
		system("cls");
		gameStatus = running ;
		
		deck.Shuffle(SHUFFLES);
		deck.TEMP_ShowDeck();

		StartRound();
	}

	void StartRound()
	{
		size_t TEMP_cardsToDeal{ 1 };

		for (size_t i{ 0 }; i < TEMP_cardsToDeal; i++)
		{
			int selected = deck.DealCard();
			std::cout << "selected: " << selected << std::endl;
		}

		deck.TEMP_ShowDeck();
	}

	const enum GAMESTATUS {notStarted, running, over};
private: 
	GAMESTATUS gameStatus;
	Deck deck;
	const size_t SHUFFLES{100};
};
