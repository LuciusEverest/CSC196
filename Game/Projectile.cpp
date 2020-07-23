#include "Projectile.h"
#include "Graphics/ParticleSystem.h"
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
	m_lifetime -= dt;
	if (m_lifetime <= 0)
	{
		m_destroy = true;
	}

	bleh::Vector2 direction = bleh::Vector2::Rotate(bleh::Vector2::forward, m_transform.angle);
	bleh::Vector2 velocity = direction * m_speed;
	m_transform.position = m_transform.position + (velocity * dt);

	g_particleSystem.Create(m_transform.position, m_transform.angle + bleh::PI, 10, 1, 0.5f, bleh::Color::white, 100, 200);

	m_transform.Update();
}

void Projectile::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::ENEMY)
	{
		m_destroy = true;
	}
}
