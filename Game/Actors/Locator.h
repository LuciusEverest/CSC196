#pragma once
#include "Object/Actor.h"

class Locator : public bleh::Actor
{
public:
	virtual eType GetType() override { return eType::LOCATOR; }

	virtual void Update(float dt) override;

};
