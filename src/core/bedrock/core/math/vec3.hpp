#pragma once

namespace bedrock {
	class Vec3 {
	public:
		float x;
		float y;
		float z;

		Vec3() : x(0), y(0), z(0) {}
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		Vec3 operator+(const Vec3& other) const {
			return Vec3(x + other.x, y + other.y, z + other.z);
		}

		Vec3& operator+=(const Vec3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vec3 operator-(const Vec3& other) const {
			return Vec3(x - other.x, y - other.y, z - other.z);
		}

		Vec3& operator-=(const Vec3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vec3 operator*(float scalar) const {
			return Vec3(x * scalar, y * scalar, z * scalar);
		}

		Vec3& operator*=(float scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		Vec3 operator/(float scalar) const {
			return Vec3(x / scalar, y / scalar, z / scalar);
		}

		Vec3& operator/=(float scalar) {
			x /= scalar;
			y /= scalar;
			z /= scalar;
			return *this;
		}

		bool operator==(const Vec3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator!=(const Vec3& other) const {
			return !(*this == other);
		}

		Vec3 operator-() const {
			return Vec3(-x, -y, -z);
		}
	};
}
