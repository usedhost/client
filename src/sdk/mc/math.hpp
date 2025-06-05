#pragma once

template <typename T>
struct Vec2 {
public:
	T x = 0, y = 0;
public:
	explicit Vec2(T x = 0, T y = 0) {
		this->x = x;
		this->y = y;
	};

	auto operator+(const Vec2<T> Vec) {
		return Vec2(this->x + Vec.x, this->y + Vec.y);
	};

	auto operator==(const Vec2<T> Vec) {
		return this->x == Vec.x && this->y == Vec.y;
	};

	auto operator-(const Vec2<T> Vec) {
		return Vec2(this->x - Vec.x, this->y - Vec.y);
	};
};