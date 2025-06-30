#include"particle.h"
#include"random_generator.h"
#include"constants.h"
#include<cmath>

particle::particle(Vec2D pos, Vec2D vel, double m, int identifier){
    position = pos;
    velocity = vel;
    mass = m;
    ID = identifier;
}

Vec2D particle::get_position(){
    return position;
}

Vec2D particle::get_velocity(){
    return velocity;
}

double particle::get_mass(){
    return mass;
}

void particle::set_position(Vec2D newpos){
    position = newpos;
}

void particle::set_velocity(Vec2D newvel){
    velocity = newvel;
}

std::ostream& operator<<(std::ostream& os, const particle& par){
    os << par.position << ", " << par.velocity << " mass: " << par.mass << " ID: " << par.ID; 
    return os;
}

particle generate_random_particle(int identifier){
    double tempx, tempy, tempm;
    tempx = INIT_POSITION_RANGE_X_MIN + (INIT_POSITION_RANGE_X_MAX-INIT_POSITION_RANGE_X_MIN)*RandomGenerator::getRandomNumber();
    tempy = INIT_POSITION_RANGE_Y_MIN + (INIT_POSITION_RANGE_Y_MAX-INIT_POSITION_RANGE_Y_MIN)*RandomGenerator::getRandomNumber();
    Vec2D pos(tempx, tempy);
    tempx = INIT_VELOCITY_RANGE_X_MIN + (INIT_VELOCITY_RANGE_X_MAX-INIT_VELOCITY_RANGE_X_MIN)*RandomGenerator::getRandomNumber();
    tempy = INIT_VELOCITY_RANGE_Y_MIN + (INIT_VELOCITY_RANGE_Y_MAX-INIT_VELOCITY_RANGE_Y_MIN)*RandomGenerator::getRandomNumber();
    Vec2D vel(tempx, tempy);
    tempm = DEFAULT_MASS - MASS_VARIATION + (2*MASS_VARIATION*RandomGenerator::getRandomNumber());
    return particle(pos, vel, tempm, identifier);
}

Vec2D RK_4_for_move(Vec2D v, double dt){
    Vec2D k1, k2, k3, k4;
    k1 = v;
    k2 = v + k1*(dt/2.0);
    k3 = v + k2*(dt/2.0);
    k4 = v + k3*dt;
    return v+(k1+k2+k2+k3+k3+k4)*(dt/6.0);
}

void particle::move(double dt){
    position = position + RK_4_for_move(velocity, dt);
}

int particle::get_ID(){
    return ID;
}