#include "Vector3D.h"

	Vector3D::Vector3D() : x(0), y(0), z(0) {}

	Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	Vector3D::Vector3D(physx::PxVec3 PxV3) : x(PxV3.x), y(PxV3.x), z(PxV3.z) {}

	float Vector3D::magnitude() const {
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3D Vector3D::normalize() const {
		float mag = magnitude();
		if (mag == 0.0f)  return Vector3D(0, 0, 0);
		return Vector3D(x / mag, y / mag, z / mag);
	}

	float Vector3D::dot(const Vector3D& v) const {
		return (x * v.x + y * v.y + z * v.z);
	}

	Vector3D Vector3D::cross(const Vector3D& v) const {
		float _x = y * v.z - z * v.y;
		float _y = z * v.x - x * v.z;
		float _z = x * v.y - y * v.x;
		return Vector3D(_x, _y, _z);
	}

	Vector3D& Vector3D::operator=(const Vector3D& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3D Vector3D::operator+(const Vector3D& other) const {
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	Vector3D Vector3D::operator-(const Vector3D& other) const {
		return Vector3D(x - other.x, y - other.y, z - other.z);
	}

	Vector3D Vector3D::operator*(float scalar) const {
		return Vector3D(x * scalar, y * scalar, z * scalar);
	}

	Vector3D& Vector3D::operator+=(const Vector3D& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
