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
		deck.Shuffle();
	}

	static enum GAMESTATUS {notStarted, running, over};
private: 
	/*bool gameOver = true;*/
	GAMESTATUS gameStatus;
	Deck deck;
};
