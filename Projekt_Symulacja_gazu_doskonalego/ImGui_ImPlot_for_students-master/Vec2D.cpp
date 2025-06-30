#include "Vec2D.h"
#include<cmath>


Vec2D::Vec2D(){
    x = 0.0;
    y = 0.0;
}

Vec2D::Vec2D(double xin, double yin){
    x = xin;
    y = yin;
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

std::ostream& operator<<(std::ostream& os, const Vec2D& vec){
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

double Vec2D::get_x(){
    return x;
}

double Vec2D::get_y(){
    return y;
}

double Vec2D::magnitude(){
    return std::sqrt(x*x + y*y);
}

