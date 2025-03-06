#include "body.h"
#include "constants.h"
#include "Vec2D.h"
#include "RandomGenerator.h"
#include <iostream>
#include <cmath>

#define _USE_MATH_DEFINES


body::body(int identifier, double r, double m, Vec2D initial_pos, Vec2D initial_vel){
    ID = identifier;
    radius = r;
    mass = m;
    position = initial_pos;
    velocity = initial_vel;

    volume = get_volume(radius);

    std::cout << "New body: \n"<< ID << " " << radius << " " << mass << " (" << position.x << ", " << position.y << ") (" << velocity.x << ", " << velocity.y << ")\n";  
}

void body::history_update(){
    hist.update(position.x, position.y);
}

body generate_random_body(int ID){
    double r, m, pos_x, pos_y, vel_x, vel_y;
    r = MIN_RADIUS + RandomGenerator::getRandomNumber()*(MAX_RADIUS-MIN_RADIUS);
    m = MIN_MASS + RandomGenerator::getRandomNumber()*(MAX_MASS-MIN_MASS);
    pos_x = MAX_INIT_POSITION*(2*RandomGenerator::getRandomNumber()-1);
    pos_y = MAX_INIT_POSITION*(2*RandomGenerator::getRandomNumber()-1);
    vel_x = MAX_INIT_VELOCITY*(2*RandomGenerator::getRandomNumber()-1);
    vel_y = MAX_INIT_VELOCITY*(2*RandomGenerator::getRandomNumber()-1);
    Vec2D pos (pos_x,pos_y);
    Vec2D vel (vel_x,vel_y);
    return body(ID, r, m, pos, vel);
}

double get_volume(double radius){
    return 4.0/3.0*M_PI*pow(radius, 3);
}

double get_radius(double volume){
    return pow(3*volume/(4*M_PI), 1.0/3.0);
}

void body::history_inherit(std::vector<double> x, std::vector<double> y){
    history temp (x,y);
    hist = temp;
}