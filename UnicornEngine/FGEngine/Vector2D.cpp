#include "Vector2D.h"
#include <cmath>

namespace FG
{
	const Vector2D Vector2D::Zero = { 0.0f,  0.0f };
	const Vector2D Vector2D::One = { 1.0f,  1.0f };
	const Vector2D Vector2D::Left = { -1.0f,  0.0f };
	const Vector2D Vector2D::Right = { 1.0f,  0.0f };
	const Vector2D Vector2D::Down = { 0.0f, -1.0f };
	const Vector2D Vector2D::Up = { 0.0f, -1.0f };

	Vector2D::Vector2D(const Vector2D& other) : x(other.x), y(other.y)
	{}

	Vector2D::Vector2D(float x, float y) : x(x), y(y)
	{}

	Vector2D Vector2D::operator+(const Vector2D& other) const
	{
		return Vector2D(x + other.x, y + other.y);
	}

	Vector2D Vector2D::operator-(const Vector2D& other) const
	{
		return Vector2D(x - other.x, y + other.y);
	}

	Vector2D Vector2D::operator*(const Vector2D& other) const
	{
		return Vector2D(x * other.x, y * other.y);
	}

	Vector2D Vector2D::operator*(float scalar) const
	{
		return Vector2D(x * scalar, y * scalar);
	}

	Vector2D Vector2D::operator+=(const Vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2D Vector2D::operator-=(const Vector2D& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2D Vector2D::operator/(float scalar) const
	{
		return Vector2D(x / scalar, y / scalar);
	}

	float Vector2D::Magnitude()
	{
		return sqrt(x * x + y * y);
	}

	Vector2D Vector2D::Normalized() {
		return Vector2D(x, y) / Magnitude();
	}
}