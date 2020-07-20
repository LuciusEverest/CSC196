#include "Projectile.h"
#include <fstream>
#include <Math\Math.h>

bool Projectile::Load(const std::string& filename)
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
		std::getline(stream, shapename);
		m_shape.Load(shapename);
		
	}

	return success;
}

void Projectile::Update(float dt)
{
	bleh::Vector2 direction = bleh::Vector2::Rotate(bleh::Vector2::forward, m_transform.angle);
	bleh::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);

	m_transform.Update();
}

void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;
	}
}
