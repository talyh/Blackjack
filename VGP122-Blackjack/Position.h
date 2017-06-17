#ifndef POSITION_H
#define POSITION_H

struct Position
{
	int xPos{ 0 };
	int yPos{ 0 };

	Position& Position::operator+= (const int rhs)
	{
		xPos += rhs;
		yPos += rhs;
		return *this;
	}
	friend Position operator+(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z += rhs;
		return z;
	}

	Position& Position::operator-= (const int rhs)
	{
		xPos -= rhs;
		yPos -= rhs;
		return *this;
	}
	friend Position operator-(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z -= rhs;
		return z;
	}

	Position& Position::operator*= (const int rhs)
	{
		xPos *= rhs;
		yPos *= rhs;
		return *this;
	}
	friend Position operator*(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z *= rhs;
		return z;
	}

	Position& Position::operator/= (const int rhs)
	{
		xPos /= rhs;
		yPos /= rhs;
		return *this;
	}
	friend Position operator/(const Position & lhs, const int & rhs)
	{
		Position z = lhs;
		z /= rhs;
		return z;
	}

	Position& Position::operator=(const Position & rhs)
	{
		xPos = rhs.xPos;
		yPos = rhs.yPos;
		return *this;
	}

	friend bool operator==(const Position & lhs, const Position & rhs)
	{
		if (lhs.xPos == rhs.xPos && lhs.yPos == rhs.yPos)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	friend bool operator!=(const Position & lhs, const Position & rhs)
	{
		return !(rhs == lhs);
	}
};

#endif // !POSITION_H
