#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include "Common.h"
#include "CollisionDetection.h"

class GameControl
{
public:
	GameControl();
	~GameControl();

	static void ListenForGameEvents(bool listening);

	static void ReceiveButtonnInfo(Sprite* button);

private:

};

#endif

