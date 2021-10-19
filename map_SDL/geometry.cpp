#include "geometry.h"

Vector2::Vector2()
{
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
}

Vector2::~Vector2()
{
}

Vector2 Vector2::operator+(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Vector2 Vector2::operator/(const Vector2& v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

Vector2 Vector2::operator=(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
	return *this;
}

Vector2 Vector2::operator+=(const Vector2& v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vector2 Vector2::operator*=(const Vector2& v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Vector2 Vector2::operator/=(const Vector2& v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

bool Vector2::operator==(const Vector2& v)
{
	return this->x == v.x && this->y == v.y;
}

bool Vector2::operator!=(const Vector2& v)
{
	return this->x != v.x || this->y != v.y;
}

bool Vector2::operator<(const Vector2& v)
{
	return this->x * this->x + this->y * this->y < v.x * v.x + v.y * v.y;
}

bool Vector2::operator<=(const Vector2& v)
{
	return this->x * this->y <= v.x* v.y;
}

bool Vector2::operator>(const Vector2& v)
{
	return this->x * this->y > v.x* v.y;
}

bool Vector2::operator>=(const Vector2& v)
{
	return this->x * this->y >= v.x* v.y;
}

Transform::Transform()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;

	this->scale.x = 1;
	this->scale.y = 1;
}

Transform::Transform(const Vector3 position, const Vector2 scale)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;

	this->scale.x = scale.x;
	this->scale.y = scale.y;
}

Transform::Transform(const float x, const float y, const float z, const float h, const float w)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;

	this->scale.x = w;
	this->scale.y = h;
}

Transform::Transform(const Transform& t)
{
	this->position.x = t.position.x;
	this->position.y = t.position.y;
	this->position.z = t.position.z;

	this->scale.x = t.scale.x;
	this->scale.y = t.scale.y;
}

Transform::~Transform()
{
}

bool Transform::Collide(const Transform& t)
{
	bool isColliding = false;

	if (
		(this->position.x - this->scale.x / 2 > t.position.x - t.scale.x / 2 && this->position.x - this->scale.x / 2 < t.position.x + t.scale.x / 2 &&
		this->position.y - this->scale.y / 2 > t.position.y - t.scale.y / 2 && this->position.y - this->scale.y / 2 < t.position.y + t.scale.y / 2)
		||
		(this->position.x + this->scale.x / 2 > t.position.x - t.scale.x / 2 && this->position.x + this->scale.x / 2 < t.position.x + t.scale.x / 2 &&
		this->position.y - this->scale.y / 2 > t.position.y - t.scale.y / 2 && this->position.y - this->scale.y / 2 < t.position.y + t.scale.y / 2)
		||
		(this->position.x - this->scale.x / 2 > t.position.x - t.scale.x / 2 && this->position.x - this->scale.x / 2 < t.position.x + t.scale.x / 2 &&
		this->position.y + this->scale.y / 2 > t.position.y - t.scale.y / 2 && this->position.y + this->scale.y / 2 < t.position.y + t.scale.y / 2)
		||
		(this->position.x + this->scale.x / 2 > t.position.x - t.scale.x / 2 && this->position.x + this->scale.x / 2 < t.position.x + t.scale.x / 2 &&
		this->position.y + this->scale.y / 2 > t.position.y - t.scale.y / 2 && this->position.y + this->scale.y / 2 < t.position.y + t.scale.y / 2)
		)
		isColliding = true;

	return isColliding;
}

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

Vector3 Vector3::operator/(const Vector3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

Vector3 Vector3::operator=(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

Vector3 Vector3::operator+=(const Vector3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Vector3 Vector3::operator*=(const Vector3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

Vector3 Vector3::operator/=(const Vector3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

bool Vector3::operator==(const Vector3& v)
{
	return this->x == v.x && this->y == v.y;
}

bool Vector3::operator!=(const Vector3& v)
{
	return this->x != v.x || this->y != v.y;
}

bool Vector3::operator<(const Vector3& v)
{
	return this->x * this->x + this->y * this->y < v.x* v.x + v.y * v.y;
}

bool Vector3::operator<=(const Vector3& v)
{
	return this->x * this->x + this->y * this->y <= v.x* v.x + v.y * v.y;
}

bool Vector3::operator>(const Vector3& v)
{
	return this->x * this->x + this->y * this->y > v.x* v.x + v.y * v.y;
}

bool Vector3::operator>=(const Vector3& v)
{
	return this->x * this->x + this->y * this->y >= v.x* v.x + v.y * v.y;
}
