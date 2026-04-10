#pragma once

class Vec2{
    private:
        float x;
        float y;
    
    public:
        Vec2(float x = 0, float y = 0);

        // =====================================================
        // Getters and Setters
        // =====================================================

        float getX() const ;
        float getY() const ;
        void setX(float x);
        void setY(float y);


        // =====================================================
        // Basic vector arithmetic
        // =====================================================
        Vec2 operator+(const Vec2& other) const;
        Vec2 operator-(const Vec2& other) const;
        Vec2 operator*(float scalar) const;
        Vec2 operator/(float scalar) const;
        Vec2& operator+=(const Vec2& other);
        

        // =====================================================
        // Vector analysis
        // =====================================================
        float dot(const Vec2& other) const;
        float cross(const Vec2& other) const;

        float magnitude() const;
        float angle() const;
        Vec2 normalize() const;
        float magnitudeSquared() const;

        // =====================================================
        // Geometric transformations
        // =====================================================
        Vec2 reflect(const Vec2& normal) const;
        Vec2 rotate(const float angle) const;
        float distance( const Vec2& other) const;
        Vec2 perpendicular() const;
        Vec2 lerp(const Vec2& target, float t) const;

};