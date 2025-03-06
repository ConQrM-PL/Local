#include "Vec2D.h"
#include<cmath>
#include<iostream>
#include<cassert>

Vec2D::Vec2D(double a, double b){
    x = a;
    y = b;
}

void Vec2D::set_x(double a){
    x = a;
}

void Vec2D::set_y(double b){
    y = b;
}

double Vec2D::get_x(){
    return x;
}

double Vec2D::get_y(){
    return y;
}

Vec2D Vec2D::operator+(Vec2D v){
    return Vec2D(this->x+v.x,this->y+v.y);
}
Vec2D Vec2D::operator-(Vec2D v){
    return Vec2D(this->x-v.x,this->y-v.y);
}
Vec2D Vec2D::operator*(double u){
    return Vec2D(this->x*u,this->y*u);
}
double Vec2D::length(){
    return sqrt(x*x+y*y);
}

