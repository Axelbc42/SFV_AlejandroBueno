#pragma once
#include "Particle.h"

class Boat : public Particle
{
public:
	Boat(Vector3D Pos, Vector3D Vel, float mVel = 10.0f, Vector3D Acc = Vector3D(0, 0, 0), float m = 0.1f, float r = 1, float lifeTime = 0.0f, Vector4 color = Vector4(1, 0, 0, 1), double damping = 0.99);
	Boat();
	~Boat();

	void integrateEulerSI(double t) override;
	void rotateBoat(float angle);
	Vector3D getRotDir() const { return pose.q.rotate(physx::PxVec3(0, 0, -1));
	}

private:
	float maxVel;
	RenderItem* Wood = nullptr;
	RenderItem* Sail = nullptr;

	physx::PxTransform wPos;
	physx::PxTransform sPos;
};

