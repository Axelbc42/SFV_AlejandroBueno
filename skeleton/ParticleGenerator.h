#pragma once
#include "Particle.h"

#include <random>

class ParticleGenerator {
public:
	ParticleGenerator(Vector3D pos, Vector3D posVar, bool gauss, Vector3D MeanOrMin, Vector3D MeanOrMax,
		float pMean, float pVar, float lMean, float lVar,
		float r, double d, Vector4 c);

	int numToEmit();
	void setup(Particle& p, const Vector3D& g);
	Vector3D getPos() { return position; }

private:
	// Generador:
	Vector3D position;
	Vector3D positionVar;
 
	bool gaussianVel;
	Vector3D speedVar, speedMean;
	Vector3D minSpeed, maxSpeed;		// Esto es igual a la media +/- la varianza

	float particlesMean, particlesVar;	// partículas por frame
	float lifeMean, lifeVar;			// tiempo de vida

	// Particula:
	float radius;
	double damping;
	Vector4 color = Vector4(1, 0, 0, 1);

	// Cositas de la clase
	std::mt19937 rng;

	Vector3D gaussVel();
	Vector3D uniformVel();
};

