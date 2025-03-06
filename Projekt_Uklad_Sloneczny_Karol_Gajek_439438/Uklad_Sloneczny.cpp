#include "Planeta.h"
#include "Vec2D.h"
#include<vector>
#include<string>
#include "matplotlibcpp.h"
#include "Uklad_Sloneczny.h"
#include<fstream>

namespace plt = matplotlibcpp;

using namespace std;

Uklad_Sloneczny::Uklad_Sloneczny(double krok){
    t = 0.0;
    dt = krok;
}

void Uklad_Sloneczny::draw(){
    plt::figure_size(800, 800);
    for(int i=0; i<(int) uklad.size(); i++ ) {
        ifstream iplik ("data/"+uklad[i].get_name()+".txt", std::ios_base::app);
        vector<double> T;
        vector<double> X;
        vector<double> Y;
        while(true){
            double tt, x, y;
            iplik >> tt >> x >> y;
            if(iplik.fail()) break;
            x = x/149597871000.0;
            y = y/149597871000.0;
            // c o u t << x << y << e n dl ;
            X.push_back(x);
            Y.push_back(y);
        }
        iplik.close();
        vector<double> x_last={X.back()};
        vector<double> y_last={Y.back()};
        plt::scatter (x_last, y_last, 20); // p l o t l a s t p o s t i o n as a p o i n t
        plt::plot(X,Y); // p l o t a l l p r e v i o u s p o s t i o n s as l i n e
    }
    vector<double> sx;
    vector<double> sy;
    sx.push_back(0);
    sy.push_back(0);
    plt::scatter(sx, sy, 5);
    plt::title("Dzien "+to_string(int(t/24/60/60)));
    plt::xlabel("x [AU]");
    plt::ylabel("y [AU]");
    plt::xlim(-40, 40);
    plt::ylim(-40, 40);
    plt::save("plots/t="+to_string(int(t/24/60/60))+".png");
    plt::close();
}

void Uklad_Sloneczny::step(){
    for(int i=0; i<(int) uklad.size();i++){
        (uklad.at(i)).move(dt);
    }
    t += dt;
}

void Uklad_Sloneczny::save_step(){
    for(int i=0; i<(int)uklad.size();i++){
        ofstream oplik;
        string currentfile = "data/"+uklad[i].get_name()+".txt";
        if (!t){
            ofstream oplik(currentfile, std::ios_base::out);
            oplik << t << " " << uklad[i].get_x() << " " << uklad[i].get_y() << "\n";
        } else {
            ofstream oplik(currentfile, std::ios_base::app);
            oplik << t << " " << uklad[i].get_x() << " " << uklad[i].get_y() << "\n";
        }
        oplik.close();
    }
}

void Uklad_Sloneczny::read(){
    ifstream iplik("planety.txt");
    while(!iplik.eof()){
        double rx,ry,vx,vy;
        string name;
        iplik >> name >> rx >> ry >> vx >> vy;
        Vec2D r(rx,ry);
        Vec2D v(vx,vy);
        Planeta planet(r,v,name);
        uklad.push_back(planet);
    }
    uklad.pop_back();
    iplik.close();
}

double Uklad_Sloneczny::get_t(){
    return t;
}

vector<Planeta> Uklad_Sloneczny::get_planets(){
    return uklad;
}