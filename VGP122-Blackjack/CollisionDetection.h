#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "Common.h"
#include "Sprite.h"

class Sprite;

class CollisionDetection
{
public:
	/** Bounding Box collision detection.
		returns true if there is a collision
		returns false if there is no collision
		*/
	static bool isColliding(Sprite*, Sprite*);
	
	/** Point inside rectangle collision detection.
		returns true if there is a collision
		returns false if there is no collision
		*/
	static bool isColliding(int, int, Sprite*);
};


#endif 
