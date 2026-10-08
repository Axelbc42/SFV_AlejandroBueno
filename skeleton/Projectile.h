#pragma once
#include "Particle.h"

constexpr float EARTH_GRAVITY = 9.8f;

class Projectile : public Particle
{
public:
	Projectile(Vector3D Pos, Vector3D vS, Vector3D vR, float mR, float rR = 1.0f, double damping = 0.99f);
	~Projectile() = default;

	void scaleMass(float mR);
	void scaleGravity(float gR = EARTH_GRAVITY);
	void changeMass(float mR);

	void update(double t);

private:
	float gravity;
	Vector3D velReal;
};
