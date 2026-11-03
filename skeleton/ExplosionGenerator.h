#pragma once
#include "ForceGenerator.h"

class ExplosionGenerator : public ForceGenerator
{
public:
	ExplosionGenerator(const Vector3D& center, float R, float K, float tau);
	void explode() { t = 0.0f; active = true; }

	void update(double dt) override;
	void updateForce(Particle* p, double dt) override;
	
private:
	Vector3D center;
	float radius, K, tau;
	float t = 0.0f;
	bool active = false;
};
