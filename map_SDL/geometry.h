#pragma once

class Vector2 {
public:
	float x;
	float y;

	// Builder
	Vector2();
	Vector2(const float x, const float y);

	// Copier
	Vector2(const Vector2& v);

	// Destroyer
	~Vector2();

	// Operators
	Vector2 operator+(const Vector2& v);
	Vector2 operator-(const Vector2& v);
	Vector2 operator*(const Vector2& v);
	Vector2 operator/(const Vector2& v);
	Vector2 operator=(const Vector2& v);

	Vector2 operator+=(const Vector2& v);
	Vector2 operator-=(const Vector2& v);
	Vector2 operator*=(const Vector2& v);
	Vector2 operator/=(const Vector2& v);

	bool operator==(const Vector2& v);
	bool operator!=(const Vector2& v);

	bool operator<(const Vector2& v);
	bool operator<=(const Vector2& v);

	bool operator>(const Vector2& v);
	bool operator>=(const Vector2& v);
};

class Vector3 : public Vector2 {
public:
	float z;

	// Builder
	Vector3();
	Vector3(const float x, const float y, const float z);

	// Copier
	Vector3(const Vector3& v);

	// Destroyer
	~Vector3();

	// Operators
	Vector3 operator+(const Vector3& v);
	Vector3 operator-(const Vector3& v);
	Vector3 operator*(const Vector3& v);
	Vector3 operator/(const Vector3& v);
	Vector3 operator=(const Vector3& v);

	Vector3 operator+=(const Vector3& v);
	Vector3 operator-=(const Vector3& v);
	Vector3 operator*=(const Vector3& v);
	Vector3 operator/=(const Vector3& v);

	bool operator==(const Vector3& v);
	bool operator!=(const Vector3& v);

	bool operator<(const Vector3& v);
	bool operator<=(const Vector3& v);

	bool operator>(const Vector3& v);
	bool operator>=(const Vector3& v);
};

class Transform {
public:
	Vector3 position;
	Vector2 scale;

	// Builders
	Transform();
	Transform(const Vector3 position, const Vector2 scale);
	Transform(const float x, const float y, const float z, const float h, const float w);

	// Copier
	Transform(const Transform& t);

	// Destroyer
	~Transform();

	// Physic
	bool Collide(const Transform& t);
};
