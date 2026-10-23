#pragma once
#include "Vector3D.h"
class ForceGenerator
{
public:
	ForceGenerator(Vector3D f) : force(f) {}
	~ForceGenerator();

	Vector3D const getForce() { return force; }

protected:
	Vector3D force;
};

