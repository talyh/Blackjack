#include <iostream>
#include "Match.h"

int Match::GetGameStatus()
{
	return gameStatus;
}

void Match::StartGame()
{
	system("cls");
	gameStatus = running;
	deck.Shuffle(SHUFFLES);
	StartRound();
}

void Match::StartRound()
{
	std::cout << "Enter the amount you'd like to bet" << std::endl;
	std::cin >> bets[0];
	player.Bet();
	DealCard();
}

void Match::DealCard() {
	int selected = deck.GetCard();
	//std::cout << "selected: " << selected << std::endl;
}

void Match::PlaceBet(int credits)
{
	// TODO need to acd credit limit check on Player
	bets.push_back(credits);
}

void Match::Split()
{
	// TODO need to acd credit limit check on Player
	bets[0] *= 2;
	bets.push_back(bets[0]);
}

void Match::FinishRound()
{
	// resolve payment

	//  delete all items from bets
}

void Match::TEMP_ShowBets()
{
	int i{ 0 };
	for (int bet : bets)
	{
		std::cout << i++ << ". " << bet << std::endl;
	}
}

