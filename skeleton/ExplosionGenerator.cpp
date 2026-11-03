#include "ExplosionGenerator.h"
#include <cmath>

ExplosionGenerator::ExplosionGenerator(const Vector3D& center, float R, float K, float tau)
	: center(center), radius(R), K(K), tau(tau) {}

void ExplosionGenerator::update(double dt) {
	if (active) {
		t += dt;
		if (t > tau)
			active = false;
	}
}

void ExplosionGenerator::updateForce(Particle* p, double dt) {
    if (active) {
		Vector3D d = p->getPos() - center;
		float r2 = d.x * d.x + d.y * d.y + d.z * d.z;

		if (r2 < radius * radius)
			p->addForce(d * (K / r2 * std::exp(-t / tau)));
    }
}
