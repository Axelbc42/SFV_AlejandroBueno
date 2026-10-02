#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3D Pos, Vector3D Vel, float m, double Damping) : vel(Vel), pose(Pos), mass(m), damping(Damping) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void Particle::integrateEuler(double t) {
	pose.p.x = pose.p.x + t * vel.x;
	pose.p.y = pose.p.y + t * vel.y;
	pose.p.z = pose.p.z + t * vel.z;

	vel.x = vel.x + (t * acc.x);
	vel.y = vel.y + (t * acc.y);
	vel.z = vel.z + (t * acc.z);

	double d = std::pow(damping, t);
	vel.x *= d;
	vel.y *= d;
	vel.z *= d;
}

void Particle::integrateEulerSI(double t) {
	pose.p.x = pose.p.x + t * vel.x;
	pose.p.y = pose.p.y + t * vel.y;
	pose.p.z = pose.p.z + t * vel.z;

	double d = std::pow(damping, t);
	vel.x *= d;
	vel.y *= d;
	vel.z *= d;

	pose.p.x = pose.p.x + (t * vel.x);
	pose.p.y = pose.p.y + (t * vel.y);
	pose.p.z = pose.p.z + (t * vel.z);
}

void Particle::integrateVerlet(double t) {
	Vector3D currentPos = pose.p;
	double d = std::pow(damping, t);

	if (firstVerletStep) {
		integrateEulerSI(t);
	}
	else {
		pose.p.x = currentPos.x + (currentPos.x - prevPos.x) * d + t * t * acc.x;
		pose.p.y = currentPos.y + (currentPos.y - prevPos.y) * d + t * t * acc.y;
		pose.p.z = currentPos.z + (currentPos.z - prevPos.z) * d + t * t * acc.z;
	}
	prevPos = currentPos;
}
