#include <vector>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
	explicit Player() : credits{ 500 } {}

	void Bet(int bet);

private:
	std::vector<int> hands;
	int credits;
};

#endif