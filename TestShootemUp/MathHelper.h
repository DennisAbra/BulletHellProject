#pragma once
#include <math.h>

#define PI 3.14159265
#define degToRad PI / 180.0f
#define radToDeg 180.0f / PI

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
		return sqrtf(x * x + y * y);
	}

	Vector2 Normalized()
	{
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	Vector2& operator+= (const Vector2& vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}

	Vector2& operator-= (const Vector2& vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
};

inline Vector2 operator +(const Vector2& x, const Vector2& y)
{
	return Vector2(x.x + y.x, x.y + y.y);
}

inline Vector2 operator -(const Vector2& x, const Vector2& y)
{
	return Vector2(x.x - y.x, x.y - y.y);
}

inline Vector2 operator *(const Vector2& x, const float& y)
{
	return Vector2(x.x * y, x.y * y);
}

inline Vector2 operator *(const float& x, const Vector2& y)
{
	return Vector2(x * y.x, x * y.y);
}

inline Vector2 operator /(const Vector2& x, const float& y)
{
	return Vector2(x.x / y, x.y / y);
}

inline Vector2 operator /(const float& x, const Vector2& y)
{
	return Vector2(x / y.x, x / y.y);
}

inline Vector2 RotateVector(const Vector2& vec, float angle)
{
	float radAngle = (float)(angle * degToRad);
	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}


inline Vector2 Lerp(Vector2& start, Vector2& end, float time)
{
	if (time <= 0.0f)
	{
		return start;
	}
	if (time >= 1.0f)
	{
		return end;
	}

	Vector2 dir = (end - start).Normalized();
	float mag = (end - start).Magnitude();

	return start + dir * mag * time;
}
inline float Dot(const Vector2& vec1, const Vector2& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value > max)
	{
		return max;
	}
	if (value < min)
	{
		return min;
	}
	return value;
}

const Vector2 Vec2_Zero = { 0.0f, 0.0f };
const Vector2 Vec2_One = { 1.0f, 1.0f };
const Vector2 Vec2_Up = { 0.0f, 1.0f };
const Vector2 Vec2_Down = { 0.0f, -1.0f };
const Vector2 Vec2_Right = { 1.0f, 0.0f };
const Vector2 Vec2_Left = { -1.0f, 0.0f };



struct BezierCurve
{
	Vector2 p0;
	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	Vector2 CalculateCurvePoint(float t)
	{
		float u = 1.0f - t;

		Vector2 point = (pow(u, 3) * p0) + (3 * pow(u, 2) * t * p1) + (3 * u * pow(t, 2) * p2) + (pow(t, 3) * p3);
		point.x = round(point.x);
		point.y = round(point.y);
		return point;
	}
};