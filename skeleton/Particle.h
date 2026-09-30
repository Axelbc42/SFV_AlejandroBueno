#pragma once
#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, double damping = 0.99);
	~Particle();

	void integrateEuler(double t);
	void integrateEulerSI(double t);
	void integrateVerlet(double t);		// Ns porq va mas rapido

	void setVel(Vector3D Vel);
	void setAcc(Vector3D Acc);
	void setdamping(float Damping);

private:
	Vector3D vel;
	Vector3D acc;
	double damping;
	bool firstVerletStep = true;

	physx::PxTransform pose;	// A renderItem le pasaremos la direccion de este pose, para que se actualice automaticamente
	physx::PxVec3 prevPos;		// Solo necesario para Verlet
	RenderItem* renderItem = nullptr;
};
