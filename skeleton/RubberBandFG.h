#pragma once
#include "SpringForceGenerator.h"

class RubberBandFG : public SpringForceGenerator {
public:
	RubberBandFG(double k, double resting, Particle* other) :
		SpringForceGenerator(k, resting, other) {
	}

	void updateForce(Particle* particle, double dt) override {
		// Particle es la particula a la que se le aplicara la fuerza
		Vector3D relativePosVec = _other->getPos() - particle->getPos();
		Vector3D force;

		// Normalizamos la posicion relativa y devolvemos su length
		float length = relativePosVec.magnitude();
		float deltaX = length - _resting_length;

		if (length > _resting_length) {
			force = relativePosVec * deltaX * _k;
			particle->addForce(force);
		}
	}
};