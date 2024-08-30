#pragma once

#include "Actor.h"

class Skill abstract : public Actor
{
public:
	enum class Type
	{
		FlowerBomb,
		Bee,
		Sowbug,
		Cosmos2,
		Cosmos,
		Flower,
		BadyBug2,
		BadyBug,
	};

	Skill(Skill::Type const type) : Type(type)
	{
	}

	Skill::Type GetType() const
	{
		return Type;
	}

private:
	Skill::Type const Type;
};