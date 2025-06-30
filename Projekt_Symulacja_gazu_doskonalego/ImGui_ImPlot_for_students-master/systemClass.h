#pragma once

#include<iostream>
#include<vector>
#include"gas.h"
#include"wall.h"
#include"constants.h"

class systemClass{
private:
    std::vector<gas> gases;
    std::vector<wall> container;
    double time;
    double dt = TIME_DIFFERENTIAL;
public:
    systemClass(std::vector<gas> gas_data, std::vector<wall> wall_data);
    void set_window();
    void simulate_step();
    void solve_collisions();
    void update();
};


double distance_to_wall(particle p, wall w);
bool check_wall_collision(particle p, wall w);
void wall_collision(particle & p, wall w);
double distance_to_particle(particle p1, particle p2);
bool check_particle_collision(particle p1, particle p2, bool is_same_gas);
void particle_collision(particle & p1, particle & p2);
