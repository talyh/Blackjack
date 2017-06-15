#ifndef SIZE_H
#define SIZE_H

struct Size
{
	int width{ 0 };
	int height{ 0 };

	Size& Size::operator+= (const int rhs)
	{
		width += rhs;
		height += rhs;
		return *this;
	}
	friend Size operator+(const Size & lhs, const int & rhs)
	{
		Size z = lhs;
		z += rhs;
		return z;
	}

	Size& Size::operator-= (const int rhs)
	{
		width -= rhs;
		height -= rhs;
		return *this;
	}
	friend Size operator-(const Size & lhs, const int & rhs)
	{
		Size z = lhs;
		z -= rhs;
		return z;
	}

	Size& Size::operator*= (const int rhs)
	{
		width *= rhs;
		height *= rhs;
		return *this;
	}
	friend Size operator*(const Size & lhs, const int & rhs)
	{
		Size z = lhs;
		z *= rhs;
		return z;
	}

	Size& Size::operator/= (const int rhs)
	{
		width /= rhs;
		height /= rhs;
		return *this;
	}
	friend Size operator/(const Size & lhs, const int & rhs)
	{
		Size z = lhs;
		z /= rhs;
		return z;
	}
};

#endif // !SIZE_H
