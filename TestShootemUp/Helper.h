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
		return (float)sqrt(x * x + y * y);
	}

	Vector2 Normalized()
	{
		float mag = Magnityde();
		return Vector2(x / mag, y / mag);
	}
};

inline Vector2 operator +(const Vector2& lefthandSide, const Vector2& righthandSide)
{
	return Vector2(lefthandSide.x + righthandSide.x, lefthandSide.y + righthandSide.y)
}

inline Vector2 operator -(const Vector2& lefthandSide, const Vector2& righthandSide)
{
	return Vector2(lefthandSide.x - righthandSide.x, lefthandSide.y - righthandSide.y)
}

Vector2 RotateVector(Vector2& vec, float angle)
{
	float radAngle = (float)(angle * degToRad);
	return Vector2(float) (vec.x * cos(radAngle) - vec.y * sin(radAngle), (float)(vec.x * sin(radAngle)) + vec.y * cos(radAngle)));
}