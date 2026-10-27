#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "ParticleForceRegistry.h"

class ParticleSystem {
public:
	ParticleSystem(int maxParticles, float maxDist = 100.0f);

	void update(double t);
	void addEmitter(const ParticleGenerator& gen);
	void addForceGenerator(std::shared_ptr<ForceGenerator> fg);

private:
	bool outOfBounds(const Vector3D& p) const;

	std::vector<std::unique_ptr<Particle>> pool;
	int aliveCount = 0;
	std::unique_ptr<ParticleGenerator> emitter;
	float maxDistance;
	Vector3D gravity;

	std::vector<std::shared_ptr<ForceGenerator>> generators;
	ParticleForceRegistry registry;
};

