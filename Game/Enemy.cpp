#include "Enemy.h"
#include <fstream>
#include <Math\Math.h>

bool Enemy::Load(const std::string& filename)
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

void Enemy::Update(float dt)
{
	bleh::Vector2 direction = m_target-> GetTransform().position - m_transform.position;
	direction.Normalize();
	bleh::Vector2 enemyVelocity = direction * m_speed;
	m_transform.position = m_transform.position + (enemyVelocity * dt);
	m_transform.angle = std::atan2(direction.y, direction.x) + bleh::DegreesToRadians(90.0f);

	m_transform.Update();
}
