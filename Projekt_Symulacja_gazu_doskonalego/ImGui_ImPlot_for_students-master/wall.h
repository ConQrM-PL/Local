#pragma once

#include<iostream>
#include<vector>

class wall{
private:
    double (*function) (double);
    double range_min;
    double range_max;
    bool is_x;
    double thickness;
public:
    wall(double (*f)(double), double min, double max, bool type, double thicc);
    double value(double point);
    bool check_is_x();
    void generate_points_to_draw(std::vector<double> & xdata, std::vector<double> & ydata);
    double get_thickness();
};

std::vector<wall> setup_container();