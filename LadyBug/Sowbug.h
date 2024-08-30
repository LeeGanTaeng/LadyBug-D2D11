#pragma once

#include "Skill.h"

class Sowbug : public Skill
{
public:
	Sowbug(Vector<2> const & player);

	void Validate(Vector<2> const & location) override;

	void Update() override;
	void Render() override;

private:
	Vector<2> const & Player;

	Vector<2> Velocity;

	int       Count  = { 0 };
	int const Bounce = { 5 };

	float       Current  = { 0.0f };
    float const Limit    = { 7.5f };
};