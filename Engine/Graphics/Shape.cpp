#include "pch.h"
#include "Shape.h"

void bleh::Shape::Draw(Core::Graphics& graphics, bleh::Vector2 position, float scale, float angle)
{
	graphics.SetColor(m_color);
	for (size_t i = 0; i < m_points.size() - 1; i++)
	{
		// local / object space points
		bleh::Vector2 p1 = m_points[i];
		bleh::Vector2 p2 = m_points[i + 1];
		//transform points
		p1 = p1 * scale;
		p2 = p2 * scale;
		//rotate
		p1 = bleh::Vector2::Rotate(p1, angle);
		p2 = bleh::Vector2::Rotate(p2, angle);
		//translate
		p1 = p1 + position;
		p2 = p2 + position;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}
