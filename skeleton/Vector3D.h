#include "foundation/PxVec3.h"

class Vector3D
{
public:
	float x, y, z;

	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(physx::PxVec3);

	float magnitude() const;
	Vector3D normalize() const;

	float dot(const Vector3D& v) const;
	Vector3D cross(const Vector3D& v) const;

	Vector3D& operator=(const Vector3D&);
	Vector3D operator+(const Vector3D&) const;
	Vector3D operator-(const Vector3D&) const;
	Vector3D operator*(float) const;
	Vector3D& operator+=(const Vector3D&);

private:

};

