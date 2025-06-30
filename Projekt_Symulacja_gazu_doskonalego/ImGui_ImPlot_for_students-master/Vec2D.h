#pragma once

#include<iostream>

class Vec2D{
private:
    double x;
    double y;
public:
    Vec2D();
    Vec2D(double xin, double yin);
    Vec2D operator+(Vec2D other);
    Vec2D operator-(Vec2D other);
    Vec2D operator*(double scalar);
    friend std::ostream& operator<<(std::ostream& os, const Vec2D& vec);
    double get_x();
    double get_y();
    double magnitude();
};