#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel) : vel(Vel), pose(Pos) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

Particle::~Particle() {}

void Particle::integrateEuler(double t) {
	pose.p.x = pose.p.x + (t * vel.x);
	pose.p.y = pose.p.y + (t * vel.y);
	pose.p.z = pose.p.z + (t * vel.z);

	vel.x = vel.x + (t * acc.x);
	vel.y = vel.y + (t * acc.y);
	vel.z = vel.z + (t * acc.z);
}
void Particle::integrateEulerSI(double t) {
	vel.x = vel.x + (t * acc.x);
	vel.y = vel.y + (t * acc.y);
	vel.z = vel.z + (t * acc.z);

	pose.p.x = pose.p.x + (t * vel.x);
	pose.p.y = pose.p.y + (t * vel.y);
	pose.p.z = pose.p.z + (t * vel.z);
}
void Particle::integrateVerlet(double t) {

}