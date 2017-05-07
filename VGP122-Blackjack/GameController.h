#include "Match.h"
#include "Player.h"
#include "Dealer.h"

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class GameController
{
public:
	const Match getMatch();

	const Player getPlayer();

	const Dealer getDealer();

private:
	const Match match;
	const Player player;
	const Dealer dealer;
};
#endif

