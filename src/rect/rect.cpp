#include "rect/rect.h"

Rect::Rect(){
    x = 0; y = 0; w = 0; h = 0;
}

Rect::Rect(float x, float y, float w, float h ){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

// =====================================================
// Getters and Setters
// =====================================================

float Rect::getX() const  {return x;}
float Rect::getY() const { return y;}
float Rect::getW() const {return w;}
float Rect::getH() const {return h;}

// =====================================================
// Center
// =====================================================
Vec2 Rect::getCenter(){
    float xc = x + w / 2;
    float yc = y + h / 2;
    return Vec2(xc,yc);
}

float Rect::getCenterDistance(Rect other){
    Vec2 otherCenter = other.getCenter();
    Vec2 center = getCenter();
    float deltaX = (center.getX() - otherCenter.getX()) * (center.getX() - otherCenter.getX());
    float deltaY = (center.getY() - otherCenter.getY()) * (center.getY() - otherCenter.getY()) ;
    float distance = sqrt(deltaX + deltaY);
    return distance;
}

// =====================================================
// HitBox
// =====================================================

bool Rect::contains(Vec2& point){
    return point.getX() >= x &&
           point.getX() <= x + w &&
           point.getY() >= y &&
           point.getY() <= y + h;
}

bool Rect::intersects(const Rect& other) const{
    return x < other.x + other.w &&
           x + w > other.x &&
           y < other.y + other.h &&
           y + h > other.y;
}

Rect Rect::operator+(Vec2& vec) const{
    return Rect(x + vec.getX(), y + vec.getY(), w, h);
}