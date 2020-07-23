#include "pch.h"
#include "Shape.h"
#include <fstream>
#include <Math\Matrix33.h>

namespace bleh
{
	bool Shape::Load(const std::string& filename)
	{
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			//read color
			stream >> m_color;
			
			// read the number of points
			std::string line;
			std::getline(stream, line);
			size_t size = stoi(line);
			
			//read points
			for (size_t i = 0; i < size; i++)
			{
				Vector2 point;
				stream >> point;

				m_points.push_back(point);
			}

			stream.close();
		}

		//compute radius from point lengths
		m_radius = 0;
		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			bleh::Vector2 p1 = m_points[i];
			float length = p1.Length();

			if (length > m_radius) m_radius = length;
		}

		return success;
	}

	void Shape::Draw(Core::Graphics& graphics, Vector2 position, float scale, float angle)
	{
		graphics.SetColor(m_color);

		Matrix33 mxs;
		mxs.Scale(scale);
		Matrix33 mxr;
		mxr.Rotate(angle);
		Matrix33 mxt;
		mxt.Translate(position);

		Matrix33 mx = mxs * mxr * mxt;

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			// local / object space points
			bleh::Vector2 p1 = m_points[i];
			bleh::Vector2 p2 = m_points[i + 1];

			//transform
			// scale / rotate / translate
			p1 = p1 * mx;
			p2 = p2 * mx;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Shape::Draw(Core::Graphics& graphics, const Transform& transform)
	{
		graphics.SetColor(m_color);

		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			// local / object space points
			bleh::Vector2 p1 = m_points[i];
			bleh::Vector2 p2 = m_points[i + 1];

			//transform
			// scale / rotate / translate
			p1 = p1 * transform.matrix;
			p2 = p2 * transform.matrix;

			graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
}

