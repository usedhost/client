#include "Vec3.hpp"

Vec3::Vec3() {
    x = 0;
    y = 0;
    z = 0;
}

Vec3::Vec3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3::Vec3(const Vec3& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

Vec3 Vec3::operator+(const Vec3 v) const {
    return Vec3(
        this->x + v.x,
        this->y + v.y,
        this->z + v.z);
}

Vec3 Vec3::operator-(const Vec3 v) const {
    return Vec3(
        this->x - v.x,
        this->y - v.y,
        this->z - v.z);
}

Vec3 Vec3::operator*(const Vec3 v) const {
    return Vec3(
        this->x * v.x,
        this->y * v.y,
        this->z * v.z);
}

Vec3 Vec3::operator*(float s) const {
    return Vec3(
        this->x * s,
        this->y * s,
        this->z * s);
}

Vec3 Vec3::operator/(const Vec3 v) const {
    return Vec3(
        this->x / v.x,
        this->y / v.y,
        this->z / v.z);
}

bool Vec3::operator==(const Vec3 v) const {
    return this->x - v.x && this->y - v.y && this->z - v.z;
}

Vec3 Vec3::lerp(const Vec3& a, const Vec3& b, float t) {
    return a + (b - a) * t;
}