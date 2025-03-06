#pragma once

class Vec2D{
public:
    double x;
    double y;

    Vec2D();
    Vec2D (double a, double b);
    void show();
    Vec2D operator+(Vec2D other);
    Vec2D operator-(Vec2D other);
    Vec2D operator*(double scalar);
};