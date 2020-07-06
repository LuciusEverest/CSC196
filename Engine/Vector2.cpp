#include "pch.h"
#include "Math/Vector2.h"

namespace bleh
{
	Vector2 const Vector2::left		= Vector2{ -1,0 };
	Vector2 const Vector2::right	= Vector2{ 1,0 };
	Vector2 const Vector2::up		= Vector2{ 0,-1 };
	Vector2 const Vector2::down		= Vector2{ 0,1 };
	Vector2 const Vector2::forward	= Vector2{ 0,-1 };
}