#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"

class ParticleSystem {
public:
	ParticleSystem(size_t maxParticles, float maxDist = 100.0f);

	void update(double t);
	void addEmitter(const ParticleGenerator& gen);

private:
	bool outOfBounds(const Vector3D& p) const;

	std::vector<std::unique_ptr<Particle>> pool;
	size_t aliveCount = 0;
	std::unique_ptr<ParticleGenerator> emitter;
	float maxDistance;
	Vector3D gravity;
};

