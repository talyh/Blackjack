#include "CollisionDetection.h"

bool CollisionDetection::isColliding(Sprite * s1, Sprite * s2)
{
	/** bottom of sprite 1 is above top of sprite 2 */
	if( (s1->getYPos() + s1->getHeight()) < s2->getYPos() )
		return false;

	/** top of sprite 1 is below bottom of sprite 2 */
	if( s1->getYPos() > (s2->getYPos() + s2->getHeight()) )
		return false;

	/** right of sprite 1 is less than left of sprite 2 */
	if( (s1->getXPos() + s1->getWidth()) < s2->getXPos() )
		return false;

	/** left of sprite 1 is greater than right of sprite 2 */
	if( s1->getXPos() > (s2->getXPos() + s2->getWidth()) )
		return false;

	return true;
}

bool CollisionDetection::isColliding(int xpos, int ypos, Sprite * s)
{
	if( (xpos > s->getXPos()) && (xpos < (s->getXPos() + s->getWidth())) )
		if( (ypos > s->getYPos()) && (ypos < (s->getYPos() + s->getHeight())) )
			return true;

	return false;
}
