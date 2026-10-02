#pragma once
#include "Particle.h"

constexpr float EARTH_GRAVITY = 9.8;

class Projectile : public Particle
{
public:
	Projectile(Vector3D Pos, Vector3D vS, Vector3D vR, float mR);
	~Projectile();

	void scaleMass(float mR);
	void scaleGravity(float gR = EARTH_GRAVITY);
	void changeMass(float mR);

private:
	float gravity;
	Vector3D velReal;
};
