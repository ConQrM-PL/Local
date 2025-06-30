#pragma once

#include<iostream>
#include"Vec2D.h"
#include"wall.h"

class particle{
private:
    int ID;
    Vec2D position;
    Vec2D velocity;
    double mass;
public:
    particle(Vec2D pos, Vec2D vel, double m, int identifier);
    Vec2D get_position();
    Vec2D get_velocity();
    double get_mass();
    void set_position(Vec2D newpos);
    void set_velocity(Vec2D newvel);
    friend std::ostream& operator<<(std::ostream& os, const particle& par);
    void move(double dt);
    int get_ID();
};

particle generate_random_particle(int identifier);

Vec2D RK_4_for_move(Vec2D v, double dt);