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
	PlayRound();
}

void Match::PlayRound()
{
	bets.push_back(0);
	GetBet();
	int selected = DealCard();
	std::cout << "Hand: " << selected << std::endl;
	GetPlay();

}

int Match::DealCard() {
	//std::cout << "selected: " << selected << std::endl;
	return deck.GetCard();
}

void Match::GetBet()
{
	std::cout << "Enter the amount you'd like to bet" << std::endl;

	if (std::cin >> bets[0])
	{
		Bet(bets[0]);
	}
	else
	{
		std::cout << "Invalid bet." << std::endl;
		Common::FlushInput();
		GetBet();
	}
}

void Match::Bet(int credits)
{
	// TODO need to acd credit limit check on Player
	if (player.Bet(credits) > 0)
	{
		bets[0] = credits;
		std::cout << "Betting " << bets[0] << std::endl;
	}
	else
	{
		std::cout << "Insuficient credits." << std::endl;
		GetBet();
	}
}

void Match::GetPlay()
{
	std::cout << "Please enter an option" << std::endl;
}

void Match::Split()
{
	// TODO need to acd credit limit check on Player
	if (player.Split(bets[0]) > 0)
	{
		bets[0] *= 2;
		bets.push_back(bets[0]);
	}
	else
	{
		std::cout << "Insuficient credits to split. Please choose another play." << std::endl;
	}
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

