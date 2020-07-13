#pragma once
#include "Object/Actor.h"

class Player : public bleh::Actor
{
public:
	Player() {}
	virtual ~Player() {}

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

protected:
	float m_thrust{ 200.0f };
	bleh::Vector2 m_velocity;
	float m_rotation{ 360.0f };
};