#pragma once
#include <cmath>

#define PI 3.141592f

class Vector2 {
public:
	float X;
	float Y;

	Vector2();
	Vector2(int x, int y);
	Vector2(float x, int y);
	Vector2(int x, float y);
	Vector2(float x, float y);
	Vector2(const Vector2& vec);
	~Vector2();

	// Functions

	Vector2 Normal(const Vector2 vec) const;
	Vector2 Normalise();
	float Dot(const Vector2 vec) const;
	float Distance(const Vector2 vec) const;
	float Magnitude() const;
	
	// Static functions

	static Vector2 Normal(const Vector2 vec1, const Vector2 vec2);
	static Vector2 Normalised(const Vector2 vec);
	static float Dot(const Vector2 vec1, const Vector2 vec2);
	static float Distance(const Vector2 vec1, const Vector2 vec2);
	static float Magnitude(const Vector2 vec);

	// Operator Overloads

	void operator =(const Vector2 other);
	void operator +=(const Vector2 other);
	void operator *=(const Vector2 other);
	void operator *=(const float other);

	
	Vector2 operator *(const float other) const;
	Vector2 operator /(const float other) const;
	Vector2 operator +(const float other) const;
	Vector2 operator /(const Vector2 other) const;
	Vector2 operator +(const Vector2 other) const;
	Vector2 operator -(const Vector2 other) const;

};

Vector2 operator *(const float scalar, const Vector2& vec);
