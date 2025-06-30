#include"gas.h"
#include"constants.h"

gas::gas(int num, double m){
    N = num;
    mass = m;
    for (size_t i = 0; i < N; i++){
        particles.push_back(generate_random_particle(i));
    }
}

int gas::get_N(){
    return N;
}

particle gas::get_particle(size_t i){
    if (i >= N){
        std::cout <<"error: invalid table range\n";
        return particle(Vec2D(),Vec2D(),0, 0);
    } else {
        return particles[i];
    }

}

void gas::set_particle(particle p, size_t i){
    particles[i] = p;
}

void gas::update_points(){
    xpoints.clear();
    ypoints.clear();
    for (size_t i = 0; i < N; i++){
        xpoints.push_back(particles[i].get_position().get_x());
        ypoints.push_back(particles[i].get_position().get_y());
    }
}

std::vector<double> gas::get_xpoints(){
    return xpoints;
}

std::vector<double> gas::get_ypoints(){
    return ypoints;
}

void gas::move(double dt){
    for (size_t i = 0; i < N; i++){
        particles[i].move(dt);
    }
}