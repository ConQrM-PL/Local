#ifndef Rysowanie_H
    #define Rysowanie_H
#include "matplotlibcpp.h"
#include "Planeta.h"
#include<string>
#include<vector>
#include "Vec2D.h"

namespace plt = matplotlibcpp;


void draw_planet(double t, Planeta planeta){
    plt::figure_size(800, 800);
    vector<double> x_last = {planeta.get_x()/149597871000.0};
    vector<double> y_last = {planeta.get_y( )/149597871000.0};
    plt::scatter(x_last, y_last, 30) ;
    vector<double> sx;
    vector<double> sy;
    sx.push_back(0);
    sy.push_back(0);
    plt::scatter(sx, sy, 10);
    plt::title("Dzien "+to_string(int(t)));
    plt::xlabel("x [AU]");
    plt::ylabel("y [AU]");
    plt::xlim(-40, 40);
    plt::ylim(-40, 40);
    plt::save("plots/t="+to_string(int(t))+".png");
    plt::close();
}


#endif