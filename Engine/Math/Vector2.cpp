#include "pch.h"
#include "Math/Vector2.h"
#include <string>

namespace bleh
{
	Vector2 const Vector2::left		= Vector2{ -1,0 };
	Vector2 const Vector2::right	= Vector2{ 1,0 };
	Vector2 const Vector2::up		= Vector2{ 0,-1 };
	Vector2 const Vector2::down		= Vector2{ 0,1 };
	Vector2 const Vector2::forward	= Vector2{ 0,-1 };


	std::istream& operator >> (std::istream& stream, Vector2& v)
	{

		std::string line;
		std::getline(stream, line);//"{0,-3}"

		//check if line begins with "{"
		if (line.find("{") != std::string::npos)
		{
			//x
			std::string vx = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			v.x = std::stof(vx);
			//y
			std::string vy = line.substr(line.find(",") + 1, line.find("{") - line.find(",") - 1);
			v.y = std::stof(vy);
		}

		return stream;
	}
}