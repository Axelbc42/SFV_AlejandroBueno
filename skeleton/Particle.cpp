#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float m, float r, float life, Vector4 color, double Damping) :
	vel(Vel), acc(Acc), pose(Pos), mass(m), invMass(1/m), damping(Damping), lifeTime(life) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(r)), &pose, color);
}

Particle::Particle() : vel(0, 0, 0), acc(0, 0, 0), mass(0.1f), invMass(1/ 0.1f), damping(0.99), lifeTime(0.0f) {}

void Particle::activate(Vector3D Pos, Vector3D Vel, Vector3D Acc, float m, float r, double Damping, float Life, Vector4 color) {
	deactivate();                       // por si acaso tenía un RenderItem

	pose = physx::PxTransform(Pos);
	vel = Vel;
	acc = Acc;
	mass = m;
	invMass = 1.0f / m;
	damping = Damping;
	lifeTime = Life;
	life = 0.0f;
	force = Vector3D(0, 0, 0);
	alive = true;

	firstVerletStep = true;
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(r)), &pose, color);
}

void Particle::deactivate() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
	alive = false;
}

Particle::~Particle() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

bool Particle::updateLife(double t) {
	integrateEulerSI(t);
	life += (float)t;
	return life < lifeTime;
}

void Particle::integrateEuler(double t) {
	pose.p = pose.p + vel * t;
	vel = (vel + acc * t) * std::pow(damping, t);
}

void Particle::integrateEulerSI(double t) {
	acc = force * invMass;
	vel = (vel + acc * t) * std::pow(damping, t);
	pose.p = pose.p + vel * t;
	force = Vector3D(0, 0, 0);	// Se reinicia para el siguiente frame
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
