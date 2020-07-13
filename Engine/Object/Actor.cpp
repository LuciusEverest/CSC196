#include "pch.h"
#include "Actor.h"

namespace bleh
{
    bool Actor::Load(const std::string& filename)
    {
		bool success = false;

		// open stream
		// check if stream is open
		std::ifstream stream(filename);
		if (stream.is_open())
		{
			success = true;

			// set success to true
			stream >> m_transform;

			std::string shapename;
			stream >> shapename;
			m_shape.Load(shapename);

		}

		return success;
    }

	void Actor::Load(std::istream& stream)
	{
		stream >> m_transform;

		std::string shapename;      
		stream >> shapename;       
		m_shape.Load(shapename);
	}

    void Actor::Update(float dt)
    {
        // nothing
    }

    void Actor::Draw(Core::Graphics& graphics)
    {
        m_shape.Draw(graphics, m_transform); // draw shape using transform
    }
}