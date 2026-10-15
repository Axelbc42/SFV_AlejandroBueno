#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3D pos, Vector3D posVar, bool gauss, Vector3D MeanOrMin, Vector3D VarOrMax,
	float pMean, float pVar, float lMean, float lVar,
	float r, double d, float g, Vector4 c) :
	position(pos), positionVar(posVar), gaussianVel(gauss), 
	particlesMean(pMean), particlesVar(pVar), lifeMean(lMean), lifeVar(lVar),
	radius(r), damping(d), color(c) {
	if (gaussianVel) {
		speedVar = VarOrMax;
		speedMean = MeanOrMin;
	}
	else {
		minSpeed = MeanOrMin;
		maxSpeed = VarOrMax;
	}
}

Vector3D ParticleGenerator::gaussVel() {
	std::normal_distribution<float> vx(speedMean.x, speedVar.x);
	std::normal_distribution<float> vy(speedMean.y, speedVar.y);
	std::normal_distribution<float> vz(speedMean.z, speedVar.z);
	return Vector3D(vx(rng), vy(rng), vz(rng));
}

Vector3D ParticleGenerator::uniformVel() {
	std::uniform_real_distribution<float> vx(minSpeed.x, maxSpeed.x);
	std::uniform_real_distribution<float> vy(minSpeed.y, maxSpeed.y);
	std::uniform_real_distribution<float> vz(minSpeed.z, maxSpeed.z);
	return Vector3D(vx(rng), vy(rng), vz(rng));
}

int ParticleGenerator::numToEmit() {
	std::uniform_real_distribution<float> U(-1.f, 1.f);
	return lround(particlesMean + U(rng) * particlesVar);
}

void ParticleGenerator::setup(Particle& p, const Vector3D& g) {
	std::uniform_real_distribution<float> U(-1.f, 1.f);
	std::normal_distribution<float> lifeDist(lifeMean, lifeVar);

	Vector3D pos(position.x + U(rng) * positionVar.x,
				 position.y + U(rng) * positionVar.y,
				 position.z + U(rng) * positionVar.z);

	Vector3D v;
	if (gaussianVel)
		v = gaussVel();
	else
		v = uniformVel();

	p.activate(pos, v, g, 1.0f, radius, damping, lifeDist(rng), color);
}
