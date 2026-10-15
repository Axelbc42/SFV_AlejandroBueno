#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(size_t maxParticles, float maxDist)
	: maxDistance(maxDist), gravity(0, -10.0, 0) {
	pool.reserve(maxParticles);
	for (size_t i = 0; i < maxParticles; ++i)
		pool.push_back(std::make_unique<Particle>());
}

void ParticleSystem::addEmitter(const ParticleGenerator& gen) {
	emitter = std::make_unique<ParticleGenerator>(gen);
}

bool ParticleSystem::outOfBounds(const Vector3D& p) const {
	Vector3D oOB = p - emitter->getPos();
	return oOB.x * oOB.x + oOB.y * oOB.y + oOB.z * oOB.z > maxDistance * maxDistance;
}

void ParticleSystem::update(double t) {
	int n = emitter->numToEmit();
	for (int i = 0; i < n && aliveCount < pool.size(); ++i) {
		emitter->setup(*pool[aliveCount], gravity);
		++aliveCount;
	}

	// 2) Actualización y reciclaje de las muertas
	for (int i = 0; i < aliveCount; ) {
		Particle& p = *pool[i];
		bool dead = !p.updateLife(t) || outOfBounds(p.getPos());

		if (dead) {
			p.deactivate();
			--aliveCount;
			swap(pool[i], pool[aliveCount]);   // la muerta pasa a la zona libre
		}
		else 
			++i;
	}
}