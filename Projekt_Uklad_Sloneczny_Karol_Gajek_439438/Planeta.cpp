#include "Planeta.h"
#include "Stale.h"
#include "Vec2D.h"
#include<string>
#include<iostream>
#include<cmath>

using namespace std;

Planeta::Planeta(Vec2D pos, Vec2D vel, string text) : r(pos), v(vel){
    name = text;
}

void Planeta::set_r(Vec2D pos){
    r = pos;
}

void Planeta::set_v(Vec2D vel){
    v = vel;
}

Vec2D Planeta::get_r(){
    return r;
}

Vec2D Planeta::get_v(){
    return v;
}

string Planeta::get_name(){
    return name;
}

void Planeta::move(double dt){
    r = r+(v*dt);
    v = v-(r*(dt*G*M/pow(r.length(),3)));
}

double Planeta::get_x(){
    return this->r.get_x();
}

double Planeta::get_y(){
    return this->r.get_y();
}