#include "Vector2.h"

Vector2::Vector2() : X(0), Y(0) {}

Vector2::Vector2(float x, float y) : X(x), Y(y) {}

Vector2::Vector2(int x, int y) : X(x), Y(y) {}

Vector2::Vector2(float x, int y) : X(x), Y(y) {}

Vector2::Vector2(int x, float y) : X(x), Y(y) {}

Vector2::Vector2(const Vector2& vec) : X(vec.X), Y(vec.Y) {}

Vector2::~Vector2() {}

Vector2 Vector2::Normal(const Vector2 vec) const {
	return Normal(*this, vec);
}

Vector2 Vector2::Normalise() {
	Vector2 vec = Normalised(*this);
	this->X = vec.X; this->Y = vec.Y;

	return *this;
}

float Vector2::Dot(const Vector2 vec) const {
	return Dot(*this, vec);
}

float Vector2::Distance(const Vector2 vec) const {
	return 0.0f; // TO DO
}

float Vector2::Magnitude() const {
	return Magnitude(*this);
}

Vector2 Vector2::Normal(const Vector2 vec1, const Vector2 vec2) {
	float x = vec2.X - vec1.X;
	float y = vec2.Y - vec1.Y;

	return Vector2(y, -x);
}

Vector2 Vector2::Normalised(const Vector2 vec) {
	float mag = Magnitude(vec);
	return Vector2(vec.X / mag,vec.Y / mag);
}

float Vector2::Dot(const Vector2 vec1, const Vector2 vec2) {
	return vec1.X * vec2.X + vec1.Y * vec2.Y;
}

float Vector2::Distance(const Vector2 vec1, const Vector2 vec2) {
	float x = vec1.X - vec2.X;
	float y = vec1.Y - vec2.Y;
	return sqrt(x * x + y * y);
}

float Vector2::Magnitude(const Vector2 vec) {
	return sqrt((vec.X * vec.X) + (vec.Y * vec.Y));
}

void Vector2::operator=(const Vector2 other) {
	this->X = other.X;
	this->Y = other.Y;
}

void Vector2::operator+=(const Vector2 other) {
	this->X += other.X;
	this->Y += other.Y;
}

void Vector2::operator*=(const Vector2 other) {
	this->X *= other.X;
	this->Y *= other.Y;
}

void Vector2::operator*=(const float other) {
	this->X *= other;
	this->Y *= other;
}

Vector2 Vector2::operator*(const float other) const {
	return Vector2(this->X * other, this->Y * other);
}

Vector2 Vector2::operator/(const float other) const {
	if (other == 0) return *this;
	return Vector2(this->X / other, this->Y / other);
}

Vector2 Vector2::operator+(const float other) const {
	return Vector2(this->X + other, this->Y + other);
}

Vector2 Vector2::operator/(const Vector2 other) const {
	return Vector2(this->X / (other.X == 0) ? 1 : other.X, this->Y / (other.Y == 0) ? 1 : other.Y);
}

Vector2 Vector2::operator+(const Vector2 other) const {
	return Vector2(this->X + other.X, this->Y + other.Y);
}

Vector2 Vector2::operator-(const Vector2 other) const {
	return Vector2(this->X - other.X, this->Y - other.Y);
}

Vector2 operator*(const float scalar, const Vector2 & vec) {
	return Vector2(vec.X * scalar, vec.Y * scalar);
}
