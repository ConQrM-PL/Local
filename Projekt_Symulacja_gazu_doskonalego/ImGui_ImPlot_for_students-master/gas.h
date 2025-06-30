#pragma once

#include<iostream>
#include<vector>
#include"particle.h"
#include"imgui.h"
#include"implot.h"

class gas{
private: 
    int N;
    int mass;
    std::vector<particle> particles;
    std::vector<double> xpoints;
    std::vector<double> ypoints;
public:
    gas(int num, double m);
    int get_N();
    particle get_particle(size_t i);
    void set_particle(particle p, size_t i);
    std::vector<double> get_xpoints();
    std::vector<double> get_ypoints();
    void update_points();
    void move(double dt);
};
