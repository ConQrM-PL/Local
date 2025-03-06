#ifndef Planeta_H
    #define Planeta_H

#include "Vec2D.h"
#include<string>

using namespace std;

class Planeta{
    private:
        Vec2D r;
        Vec2D v;
        string name;
    public:
        Planeta(Vec2D pos, Vec2D vel, string text);
        void set_r(Vec2D pos);
        void set_v(Vec2D vel);
        Vec2D get_r();
        Vec2D get_v();
        string get_name();
        void move(double dt);
        double get_x();
        double get_y();
};

#endif