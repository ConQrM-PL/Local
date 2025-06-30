#include"wall.h"
#include"constants.h"
#include<cmath>

wall::wall(double (*f)(double), double min, double max, bool type, double thicc){
    function = f;
    is_x = type;
    range_max = max;
    range_min = min;
    thickness = thicc;
}

double wall::value(double point){
    return function(point);
}

bool wall::check_is_x(){
    return is_x;
}

void wall::generate_points_to_draw(std::vector<double> & xdata, std::vector<double> & ydata){
    xdata.clear();
    ydata.clear();
    double step = (range_max - range_min)/(WALL_RESOLUTION-1);
    if (is_x){
        for (int i = 0; i < WALL_RESOLUTION; i++){
            xdata.push_back(range_min + i * step);
            ydata.push_back(function(range_min + i * step));
        }
    } else {
        for (int i = 0; i < WALL_RESOLUTION; i++){
            ydata.push_back(range_min + i * step);
            xdata.push_back(function(range_min + i * step));
        }
    }
}

double wall::get_thickness(){
    return thickness;
}


double f1x(double x){
    return FUNCTION_WALL_UP;
}

double f2x(double x){
    return FUNCTION_WALL_DOWN;
}

double f1y(double y){
    return FUNCTION_WALL_RIGHT;
}

double f2y(double y){
    return FUNCTION_WALL_LEFT;
}

std::vector<wall> setup_container(){
    wall wallup(f1x, WALL_UP_RANGE_MIN, WALL_UP_RANGE_MAX, true, WALL_THICKNESS);
    wall walldown(f2x, WALL_DOWN_RANGE_MIN, WALL_DOWN_RANGE_MAX, true, WALL_THICKNESS);
    wall wallright(f1y, WALL_RIGHT_RANGE_MIN, WALL_RIGHT_RANGE_MAX, false, WALL_THICKNESS);
    wall wallleft(f2y, WALL_LEFT_RANGE_MIN, WALL_LEFT_RANGE_MAX, false, WALL_THICKNESS);
    return {wallup, wallright, walldown, wallleft};
}