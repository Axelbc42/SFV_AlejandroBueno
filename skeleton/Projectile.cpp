#include "Projectile.h"

Projectile::Projectile(Vector3D Pos, Vector3D vS, Vector3D vR, float mR, double damping) : Particle(Pos, vS, Vector3D(0, 0, 0), damping), velReal(vR){
	scaleMass(mR);
	scaleGravity();
}

void Projectile::scaleMass(float mR) {
	float vRM = velReal.magnitude();
	float vSM = vel.magnitude();
	mass = (mR * vRM * vRM) / (vSM * vSM);
}

void Projectile::scaleGravity(float gR) {
	float vRM = velReal.magnitude();
	float vSM = vel.magnitude();
	gravity = (vSM * vSM * gR) / (vRM * vRM);
	acc = Vector3D(0, -gravity, 0);
}

void Projectile::changeMass(float mR) {
	scaleMass(mR);
	scaleGravity(gravity);
}

void Projectile::update(double t) {
	integrateEulerSI(t);
}
