#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, Vector3D Damping)
	: vel(Vel), pose(Pos), acc(Acc), damping(Damping) {
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

	vel.x = (vel.x + t * acc.x) * damping.x;
	vel.y = (vel.y + t * acc.y) * damping.y;
	vel.z = (vel.z + t * acc.z) * damping.z;
}
void Particle::integrateEulerSI(double t) {
	vel.x = (vel.x + t * acc.x) * damping.x;
	vel.y = (vel.y + t * acc.y) * damping.y;
	vel.z = (vel.z + t * acc.z) * damping.z;

	pose.p.x = pose.p.x + t * vel.x;
	pose.p.y = pose.p.y + t * vel.y;
	pose.p.z = pose.p.z + t * vel.z;
}
void Particle::integrateVerlet(double t) {
	Vector3D currentPos = pose.p;

	if (prevPos == Vector3(0,0,0)) {
		pose.p = pose.p + Vector3D(vel.x * t, vel.y * t, vel.z * t);
	}
	else {
		pose.p.x = currentPos.x + damping.x * (currentPos.x - prevPos.x) + t * t * acc.x;
		pose.p.y = currentPos.y + damping.y * (currentPos.y - prevPos.y) + t * t * acc.y;
		pose.p.z = currentPos.z + damping.z * (currentPos.z - prevPos.z) + t * t * acc.z;
	}
	prevPos = currentPos;
}

void Particle::setVel(Vector3D Vel) { vel = Vel; }
void Particle::setAcc(Vector3D Acc) { acc = Acc; }
void Particle::setdamping(Vector3D Damping) { damping = Damping; }