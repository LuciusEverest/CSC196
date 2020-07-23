#pragma once
#include "Object/Actor.h"

class Projectile : public bleh::Actor
{
public:
	Projectile() {}

	virtual eType GetType() override { return eType::PROJECTILE; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

	//void SetTarget(Actor* actor) { m_target = actor; }
	void SetSpeed(float speed) { m_speed = speed; }

protected:
	float m_speed{ 300.0f };
	float m_lifetime{ 3 };
	//Actor* m_target{ nullptr };
};