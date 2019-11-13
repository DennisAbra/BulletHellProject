#pragma once
#include <math.h>

#define PI 3.14159265
#define degToRad PI / 180.0f

struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y)
	{ }

	float MagnitudeSqr()
	{
		return x * x + y * y;
	}

	float Magnitude()
	{
		return sqrtf(x*x +y*y);
	}

	Vector2 Normalized()
	{
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	Vector2& operator+= (const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2& operator-= (const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
};

inline Vector2 operator +(const Vector2& lefthandSide, const Vector2& righthandSide)
{
	return Vector2(lefthandSide.x + righthandSide.x, lefthandSide.y + righthandSide.y);
}

inline Vector2 operator -(const Vector2& lefthandSide, const Vector2& righthandSide)
{
	return Vector2(lefthandSide.x - righthandSide.x, lefthandSide.y - righthandSide.y);
}

inline Vector2 operator *(const Vector2& lefthandSide, const float& righthandSide)
{
	return Vector2(lefthandSide.x * righthandSide, lefthandSide.y * righthandSide);
}

inline Vector2 RotateVector(Vector2& vec, float angle)
{
	float radAngle = (float)(angle * degToRad);
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

const Vector2 Vec2_Zero = { 0.0f, 0.0f };
const Vector2 Vec2_One = { 1.0f, 1.0f };
const Vector2 Vec2_Up = { 0.0f, 1.0f };
const Vector2 Vec2_Down = { 0.0f, -1.0f };
const Vector2 Vec2_Right = { 1.0f, 0.0f };
const Vector2 Vec2_Left = { -1.0f, 0.0f };