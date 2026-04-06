#include "math/vetor.h"
#include <cmath>

Vec2::Vec2(float x, float y){
    this->x = x;
    this->y = y;
}

// =====================================================
// Basic vector arithmetic
// =====================================================

Vec2 Vec2::operator+(const Vec2& other) const {
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator/(float scalar) const {
    if (scalar == 0) return Vec2(0,0);
    return Vec2(x/scalar,y/scalar);
}

// Creates a scaled vector
Vec2 Vec2::operator*(float scalar) const {
    return Vec2(x * scalar, y * scalar);
}

// =====================================================
// Vector analysis
// =====================================================

// Returns scalar projection relation between two vectors
float Vec2::dot(const Vec2& other) const {
    return (x * other.x) + (y * other.y);
}

// Returns 2D cross product scalar (orientation / signed area)
float Vec2::cross(const Vec2& other) const {
    return x * other.y - y * other.x;
}

// Gets vector magnitude (length)
float Vec2::magnitude() const {
    return sqrt((x * x) + (y * y));
}

// Gets vector angle relative to x-axis
float Vec2::angle() const {
    return std::atan2(y, x);
}

// Returns unit vector preserving direction
Vec2 Vec2::normalize() const {
    float mag = magnitude();
    if (mag == 0) return Vec2(0.0f,0.0f);

    return *this / mag;
}

// Takes distance between two vectors
float Vec2::distance(const Vec2& other) const {
    return (*this - other).magnitude();
}

float Vec2::magnitudeSquared() const {
    return (x * x) + (y * y);
}

// =====================================================
// Geometric transformations
// =====================================================

// Reflects vector using surface normal
Vec2 Vec2::reflect(const Vec2& normal) const {
    Vec2 n = normal.normalize();
    return *this - n * (2.0f * this->dot(n));
}

// Rotates vector by angle in degrees
Vec2 Vec2::rotate(const float angle) const {
    float rad = angle * M_PI / 180.0f;
    return Vec2(x * cos(rad) - y *sin(rad), x * sin(rad) + y * cos(rad));
}

// Returns perpendicular vector (90° left rotation)
Vec2 Vec2::perpendicular() const {
    return Vec2(-y,x);
} 

// Linearly interpolates between current vector and target
Vec2 Vec2::lerp(const Vec2& target, float t) const {
    return *this + (target - *this) * t;
}

