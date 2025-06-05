#pragma once

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x, float y, float z);
    Vec3(const Vec3& v);

    Vec3 operator+(const Vec3 v) const;
    Vec3 operator-(const Vec3 v) const;
    Vec3 operator*(const Vec3 v) const;
    Vec3 operator*(float s) const;
    Vec3 operator/(const Vec3 v) const;
    bool operator==(const Vec3 v) const;

    static Vec3 lerp(const Vec3& a, const Vec3& b, float t);
};