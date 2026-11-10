#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) :
	_k(k), _resting_length(resting_length), _other(other) {}

void SpringForceGenerator::updateForce(Particle* particle, double dt) {
	// Particle es la particula a la que se le aplicara la fuerza
	Vector3D relativePosVec = _other->getPos() - particle->getPos();
	Vector3D force;

	// Normalizamos la posicion relativa y devolvemos su length
	float length = relativePosVec.magnitude();
	float deltaX = length - _resting_length;

	force = relativePosVec * deltaX * _k;

	particle->addForce(force);
}