#include "Projectile.h"

Projectile::Projectile(Vector3D Pos, Vector3D vS, Vector3D vR, float mR, float rR, float rG, double damping) :
	Particle(Pos, vS, Vector3D(0, 0, 0), 0, rR, damping), velReal(vR){
	scaleMass(mR);
	scaleGravity(rG);
}

void Projectile::scaleMass(float mR) {
	float vRM = velReal.magnitude();
	float vSM = vel.magnitude();
	mass = (mR * vRM * vRM) / (vSM * vSM);
}

void Projectile::scaleGravity(float gR) {
	float vRM = velReal.magnitude();
	float vSM = vel.magnitude();
	gravity = (gR *vSM * vSM) / (vRM * vRM);
	acc = Vector3D(0, -gravity, 0);
}

void Projectile::update(double t) {
	integrateEulerSI(t);
}
