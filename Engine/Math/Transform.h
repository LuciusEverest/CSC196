#pragma once
#include "Matrix33.h"

namespace bleh
{
	struct Transform
	{
		Vector2 position;
		float scale;
		float angle;

		Matrix33 matrix;

		Transform() : position{ 0,0 }, scale{ 0 }, angle{ 0 } {}
		Transform(Vector2 position, float scale = 1, float angle = 0) : position{ position }, scale{ scale }, angle{ angle } {}
	
		void Update();

		friend std::istream& operator >> (std::istream& stream, Transform& transform);
	};

}