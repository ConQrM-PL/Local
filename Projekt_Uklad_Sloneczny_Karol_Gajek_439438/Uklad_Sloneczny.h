#ifndef Uklad_Sloneczny_H
    #define Uklad_Sloneczny_H

#include<vector>
#include "Planeta.h"

class Uklad_Sloneczny{
    private:
        double t;
        double dt;
        vector<Planeta> uklad;
    public:
        Uklad_Sloneczny(double krok);
        void draw();
        void step();
        void save_step();
        void read();
        double get_t();
        vector<Planeta> get_planets(); //do debugu
};

#endif