#include "Vec2D.h"
#include <iostream>

Vec2D::Vec2D(){
    x = 0;
    y = 0;
}

Vec2D::Vec2D (double a, double b){
    x = a;
    y = b;
}

void Vec2D::show(){
    std::cout << "(" << x << ", " << y << ")"; 
}

Vec2D Vec2D::operator+(Vec2D other){
    return Vec2D(this->x+other.x,this->y+other.y);
}

Vec2D Vec2D::operator-(Vec2D other){
    return Vec2D(this->x-other.x,this->y-other.y);
}

Vec2D Vec2D::operator*(double scalar){
    return Vec2D(this->x*scalar, this->y*scalar);
}