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
};

#endif // !POSITION_H
