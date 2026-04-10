#pragma once
#include "vec2/vec2.h"
#include <cmath>

class Rect{
    public:

        Rect();
        Rect(float x, float y, float w, float h);

        float getX() const;
        float getY() const;
        float getW() const;
        float getH() const;
        Vec2 getCenter();
        float getCenterDistance(Rect other);

        bool contains(Vec2& point);

        bool intersects(const Rect& other) const;

        Rect operator+(Vec2& vec) const;

    private:
        float x;
        float y;
        float w;
        float h;
};