#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float m, double Damping) : vel(Vel), acc(Acc), pose(Pos), mass(m), damping(Damping) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrateEuler(double t) {
	pose.p = pose.p + vel * t;
	vel = (vel + acc * t) * std::pow(damping, t);
}

void Particle::integrateEulerSI(double t) {
	vel = (vel + acc * t) * std::pow(damping, t);
	pose.p = pose.p + vel * t;
}

void Particle::integrateVerlet(double t) {
	physx::PxVec3 currentPos = pose.p;

	if (firstVerletStep) {
		integrateEulerSI(t);
		firstVerletStep = false;
	}
	else {
		pose.p = currentPos + (currentPos - prevPos) * std::pow(damping, t) + acc * t * t;
		vel = (pose.p - prevPos) / (2.0 * t);
	}
	prevPos = currentPos;
}
