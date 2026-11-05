#include "Boat.h"
#include <cmath>
#include <iostream>

Boat::Boat(Vector3D Pos, Vector3D Vel, float mVel, Vector3D Acc, float m, float r, float lifeTime, Vector4 color, double damping) :
	Particle(Pos, Vel, Acc, m, r, lifeTime, color, damping), maxVel(mVel) {
	wPos = physx::PxTransform(Pos);
	sPos = physx::PxTransform(Pos);
	Wood = new RenderItem(CreateShape(physx::PxBoxGeometry(2.0f, 0.25f, 2.0f)), &wPos, Vector4(0.45f, 0.25f, 0.15f, 1.0f));
	Sail = new RenderItem(CreateShape(physx::PxBoxGeometry(0.1f, 2.0f, 1.0f)), &sPos, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

Boat::Boat() : Particle() {
	Wood = new RenderItem(CreateShape(physx::PxBoxGeometry(2.0f, 0.25f, 2.0f)), &pose, Vector4(0.45f, 0.25f, 0.15f, 1.0f));
	Sail = new RenderItem(CreateShape(physx::PxBoxGeometry(0.1f, 2.0f, 1.0f)), &pose, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

Boat::~Boat() {
	if (Wood) {
		Wood->release();
		Wood = nullptr;
	}
	if (Sail) {
		Sail->release();
		Sail = nullptr;
	}
}

void Boat::integrateEulerSI(double t) {
	acc = force * invMass;
	vel = (vel + acc * t) * std::pow(damping, t);
	if (vel.magnitude() > maxVel)
		vel = vel.normalize() * maxVel;

	pose.p = pose.p + vel * t;
	wPos.p = pose.p - Vector3D(0, 2, 0);
	sPos.p = pose.p;

	force = Vector3D(0, 0, 0);
}

void Boat::rotateBoat(float angle){
	physx::PxQuat rot(angle, physx::PxVec3(0, 1, 0));
	pose.q = (rot * pose.q).getNormalized();

	wPos.q = pose.q;
	sPos.q = pose.q;

	std::cout << "Boat rotation: " << pose.q.x << ", " << pose.q.y << ", " << pose.q.z << ", " << pose.q.w << std::endl;
}
