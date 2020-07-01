#pragma once

#include <cmath>

namespace bleh
{
	struct Vector2
	{
		float x, y;

		Vector2() : x{ 0 }, y{0} {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) } {}

		float& operator[] (size_t index) { return (&x)[index]; }
		const float& operator[] (size_t index) const { return (&x)[index]; }

		void set(float x, float y) { this->x = x; this->y = y; }

		Vector2 operator + (const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

		Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
		Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
		Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
		Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

		Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }

		Vector2& operator += (float s) { x += s; y += s; return *this; }
		Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
		Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
		Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

		Vector2 operator - () 
		{
			return Vector2{ -x, -y };
		}

		float Length() const;
		float LengthSqr() const;

		Vector2 Normalized() const;
		void Normalize();
	};

	float Vector2::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	float Vector2::LengthSqr() const
	{
		return ((x * x) + (y * y));
	}

	Vector2 Vector2::Normalized() const
	{
		float length = Length();
		Vector2 n = (length == 0.0f) ? Vector2{ 0.0f, 0.0f } : *this / length;

		return n;
	}

	void Vector2::Normalize()
	{
		float length = Length();
		if (length == 0.0f)
		{
			x = y = 0.0f;
		}
		else
		{
			*this /= length;
		}
	}
}

