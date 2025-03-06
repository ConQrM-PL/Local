#pragma once

#include <vector>
#include "body.h"
#include "Vec2D.h"
#include "history.h"
#include <random>

class systemClass{
public:
    std::vector<body> bodies;
    double dt;

    std::vector<history> legacy;

    systemClass(int n, double delta_t, std::vector<int> track);
    Vec2D get_acceleration(int body_ID);
    void get_first_halfstep_velocity(int body_ID);
    void update_body(int body_ID);
    void collide(body & body1, body & body2);
    void set_window();
    void update();
    void merge_history(body & alive, body dead);
    void draw_circle(body circle, std::vector<double> & tempx, std::vector<double> & tempy);
};

std::vector<int> generate_random_tracking_targets(int n, int k);

Vec2D get_force(body first, body second);

double distance(body first, body second);

bool new_number_is_unique(int n, std::vector<int> table);

bool test_collision(body body1, body body2);



