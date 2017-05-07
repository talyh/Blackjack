#include <iostream>
#include "GameController.h"

const Match GameController::getMatch()
{
return match;
}

const Player GameController::getPlayer()
{
	return player;
}

const Dealer GameController::getDealer()
{
	return dealer;
}