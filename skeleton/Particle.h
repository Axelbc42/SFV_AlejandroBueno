#pragma once
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc = Vector3D(0,0,0), float m = 0, float r = 1, float lifeTime = 0.0f, Vector4 color = Vector4(1, 0, 0, 1), double damping = 0.99);
	Particle();
	~Particle();

	void activate(Vector3D Pos, Vector3D Vel, Vector3D Acc, float m, float r, double Damping, float life, Vector4 color);
	void deactivate();

	Particle(const Particle&) = delete;
	Particle& operator=(const Particle&) = delete;

	void integrateEuler(double t);
	void integrateEulerSI(double t);
	void integrateVerlet(double t);		// Ns porq va mas rapido

	bool updateLife(double t);
	Vector3D getPos() const { return Vector3D(pose.p.x, pose.p.y, pose.p.z); }

protected:
	Vector3D vel;
	Vector3D acc;
	float mass;
	double damping;
	bool firstVerletStep = true;
	float lifeTime;
	float life = 0.0f;

	physx::PxTransform pose;	// A renderItem le pasaremos la direccion de este pose, para que se actualice automaticamente
	physx::PxVec3 prevPos;		// Solo necesario para Verlet
	RenderItem* renderItem = nullptr;
};
