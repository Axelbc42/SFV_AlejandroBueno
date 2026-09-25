#pragma once
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel);
	~Particle();

	void integrateEuler(double t);
	void integrateEulerSI(double t);
	void integrateVerlet(double t);

private:
	Vector3D vel;
	Vector3D acc;
	Vector3D damping;
	physx::PxTransform pose;	// A renderItem le pasaremos la direccion de este pose, para que se actualice automaticamente
	physx::PxVec3 prevPos;		// Solo necesario para Verlet
	RenderItem* renderItem = nullptr;
};
