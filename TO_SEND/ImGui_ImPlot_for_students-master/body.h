#pragma once

#include "Vec2D.h"
#include "history.h"
#include <vector>


class body{
public:
    int ID;
    double radius;
    double mass;
    double volume;
    Vec2D position;
    Vec2D velocity;

    bool destroy_mark = false;
    bool tracked = false;
    history hist;
    

    body(int identifier, double r, double m, Vec2D initial_pos, Vec2D initial_vel);
    void history_update();
    void history_inherit(std::vector<double> x, std::vector<double> y);
};

body generate_random_body(int ID);

double get_volume(double radius);

double get_radius(double volume);