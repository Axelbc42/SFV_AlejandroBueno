#pragma once
#include "Particle.h"

constexpr float EARTH_GRAVITY = 98;

class Projectile : public Particle
{
public:
	Projectile(Vector3D Pos, Vector3D vS, Vector3D vR, float mR, double damping = 0.99f);
	~Projectile();

	void scaleMass(float mR);
	void scaleGravity(float gR = EARTH_GRAVITY);
	void changeMass(float mR);

	void update(double t);

private:
	float gravity;
	Vector3D velReal;
};
