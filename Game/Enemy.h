#pragma once
#include "Object/Actor.h"

class Enemy : public bleh::Actor
{
public:
	Enemy() {}

	virtual eType GetType() override { return eType::ENEMY; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

	void SetTarget(Actor* actor) { m_target = actor; }
	void SetSpeed(float speed) { m_speed = speed; }

protected:
	float m_speed{ 200.0f };
	Actor* m_target{ nullptr };
};