#pragma once
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc = Vector3D(0, 0, 0), Vector3D Damping = Vector3D(1, 1, 1));
	~Particle();

	void integrateEuler(double t);
	void integrateEulerSI(double t);
	void integrateVerlet(double t);		// Ns porq va mas rapido

	void setVel(Vector3D Vel);
	void setAcc(Vector3D Acc);
	void setdamping(Vector3D Damping);

private:
	Vector3D vel;
	Vector3D acc;
	Vector3D damping;						// Ni idea  de que es o para que sirve
	physx::PxTransform pose;					// A renderItem le pasaremos la direccion de este pose, para que se actualice automaticamente
	physx::PxVec3 prevPos = Vector3D(0,0,0);	// Solo necesario para Verlet
	RenderItem* renderItem = nullptr;
};
