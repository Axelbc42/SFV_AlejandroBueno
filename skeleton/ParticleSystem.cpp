#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int maxParticles, float maxDist)
	: maxDistance(maxDist), gravity(0, -10.0, 0) {
	pool.reserve(maxParticles);
	for (int i = 0; i < maxParticles; ++i)
		pool.push_back(std::make_unique<Particle>());
}

void ParticleSystem::addEmitter(const ParticleGenerator& gen) {
	emitter = std::make_unique<ParticleGenerator>(gen);
}

void ParticleSystem::addForceGenerator(std::shared_ptr<ForceGenerator> fg) {
	generators.push_back(fg);
	for (auto& p : pool)
		registry.add(p.get(), fg.get());
}

bool ParticleSystem::outOfBounds(const Vector3D& p) const {
	Vector3D oOB = p - emitter->getPos();
	return oOB.x * oOB.x + oOB.y * oOB.y + oOB.z * oOB.z > maxDistance * maxDistance;
}

void ParticleSystem::update(double t) {
	// 0) generadores dinámicos (explosivos)
	for (auto& g : generators) g->update(t);

	// 1) emisión
	int n = emitter->numToEmit();
	for (int i = 0; i < n && aliveCount < pool.size(); ++i) {
		emitter->setup(*pool[aliveCount], gravity);
		++aliveCount;
	}

	// 2) acumular fuerzas de todos los generadores
	registry.updateForces(t);

	// 3) Actualización y reciclaje de las muertas
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