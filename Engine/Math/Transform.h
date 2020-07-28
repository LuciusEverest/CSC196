#pragma once
#include "Matrix33.h"

namespace bleh
{
	struct Transform
	{
		Vector2 position;
		float scale{ 1 };
		float angle{ 0 };

		Matrix33 matrix;

		Transform() : position{ 0,0 }, scale{ 1 }, angle{ 0 }, matrix{} {}
		Transform(Vector2 position, float scale = 1, float angle = 0) : position{ position }, scale{ scale }, angle{ angle }, matrix{} {}
	
		void Update();
		void Update(const Matrix33& mx);

		friend std::istream& operator >> (std::istream& stream, Transform& transform);
	};

}