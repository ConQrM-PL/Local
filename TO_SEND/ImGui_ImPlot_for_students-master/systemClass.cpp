#include "systemClass.h"
#include "body.h"
#include "constants.h"
#include "Vec2D.h"
#include "imgui.h"
#include "implot.h"
#include "RandomGenerator.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <string>

systemClass::systemClass(int n, double delta_t, std::vector<int> track){
    for (int i = 0; i < n; i++){
        bodies.push_back(generate_random_body(i));
    }
    dt = delta_t;
    for (int i = 0; i < track.size(); i++){
        bodies[track[i]].tracked = true;
    }
}

Vec2D systemClass::get_acceleration(int body_ID){
    Vec2D temp (0,0);
    for (int i = 0; i < bodies.size(); i++){
        temp = temp + get_force(bodies[body_ID], bodies[i]);
    }
    temp = temp*(1/bodies[body_ID].mass);
    return temp;
}

void systemClass::get_first_halfstep_velocity(int body_ID){
    Vec2D acceleration = get_acceleration(body_ID);
    bodies[body_ID].velocity.x += dt/2*acceleration.x;
    bodies[body_ID].velocity.y += dt/2*acceleration.y;
}

void systemClass::update_body(int body_ID){
    Vec2D acceleration = get_acceleration(body_ID);
    bodies[body_ID].velocity.x += dt*acceleration.x;
    bodies[body_ID].velocity.y += dt*acceleration.y;
    bodies[body_ID].position.x += dt*bodies[body_ID].velocity.x;
    bodies[body_ID].position.y += dt*bodies[body_ID].velocity.y;
    
    if (bodies[body_ID].tracked){
        bodies[body_ID].history_update();
    }
}

bool test_collision(body body1, body body2){
    if (body1.ID == body2.ID) {
        return false;
    }
    double collision_distance = body1.radius + body2.radius;
    if (distance(body1, body2) > collision_distance){
        return false;
    }
    return true;
}

void systemClass::merge_history(body & alive, body dead){
    if (dead.tracked){
        if (!alive.tracked){
            alive.tracked = true;
            alive.history_inherit(dead.hist.x, dead.hist.y);
        } else {
            history temp (dead.hist.x, dead.hist.y);
            legacy.push_back(temp);
        }
    }
}

void systemClass::collide(body & body1, body  & body2){
    double px, py;
    px = body1.mass*body1.velocity.x + body2.mass*body2.velocity.x;
    py = body1.mass*body1.velocity.y + body2.mass*body2.velocity.y;
    if (body1.radius >= body2.radius){
        body1.mass += body2.mass;
        body1.volume += body2.volume;
        body1.radius = get_radius(body1.volume);
        body1.velocity.x = px/body1.mass;
        body1.velocity.y = py/body1.mass;
        body2.destroy_mark = true;
        merge_history(body1, body2);
    } else {
        body2.mass += body1.mass;
        body2.volume += body1.volume;
        body2.radius = get_radius(body2.volume);
        body2.velocity.x = px/body2.mass;
        body2.velocity.y = py/body2.mass;
        body1.destroy_mark = true;
        merge_history(body2, body1);
    }
    
    for (int i = 0; i < bodies.size(); i++){
        if (bodies[i].destroy_mark){
            bodies.erase(bodies.begin() + i);
        }
    }
}

bool new_number_is_unique(int n, std::vector<int> table){
    for (int i = 0; i < table.size(); i++){
        if (n == table[i]){
            return false;
        }
    }
    return true;
}

std::vector<int> generate_random_tracking_targets(int n, int k){
    std::cout << "tracking: ";
    std::vector<int> temp;
    float r;
    int i = 0;
    while (i < k){
        r = RandomGenerator::getRandomNumber()*n;
        r = std::floor(r);
        if (new_number_is_unique((int) r, temp)){
            temp.push_back(r);
        std::cout << temp[i] << " ";
        i++;
        }
    }
    std::cout << std::endl;
    return temp;
}

double distance(body first, body second){
    double x,y;
    x = second.position.x - first.position.x;
    y = second.position.y - first.position.y;

    if (abs(x) < EPSILON){
        x = 0;
    }
    if (abs(y) < EPSILON){
        y = 0;
    }

    return sqrt(pow(x, 2)+ pow(y, 2));
}

Vec2D get_force(body first, body second){
    if (first.ID == second.ID){
        return Vec2D (0,0);
    }

    double x, y, z, F, Fx, Fy;
    z = distance(first, second);
    if (z == 0) {
        return Vec2D(0,0);
    }
    F = G_CONSTANT*first.mass*second.mass/pow(z, 2);
    x = second.position.x - first.position.x;
    y = second.position.y - first.position.y;

    Fx = F*x/z;
    Fy = F*y/z;

    return Vec2D (Fx,Fy);
}

void systemClass::update(){
    for (int i = 0; i < bodies.size(); i++){
        for (int j = bodies.size()-1; j > i; j--){
            if (test_collision(bodies[i], bodies[j])){
                collide(bodies[i], bodies[j]);
            }
        }
    }

    for (int i = 0; i < bodies.size(); i++){
        if (bodies[i].tracked){
            bodies[i].history_update();
        }
    }

    for (int i = 0; i < bodies.size(); i++){
        update_body(i);
    }
}

void systemClass::draw_circle(body circle, std::vector<double> & tempx, std::vector<double> & tempy){
    tempx.clear();
    tempy.clear();
    double phi;
    for (int i = 0; i <= CIRCLE_RESOLUTION; i++){
        phi = i;
        tempx.push_back(circle.position.x+circle.radius*cos(phi/CIRCLE_RESOLUTION*2*M_PI));
        tempy.push_back(circle.position.y+circle.radius*sin(phi/CIRCLE_RESOLUTION*2*M_PI));
    }
}

void systemClass::set_window(){
    ImGui::Begin("N body system");

    std::vector<double> circlex, circley;
    
    if (ImPlot::BeginPlot("Simulation", ImVec2(1000, 1000), ImPlotFlags_NoLegend ) ) {

            ImPlot::SetupAxes("x", "y");
            //ImPlot::SetNextLineStyle(line_color, line_width);
            for (int i = 0; i < bodies.size(); i++){
                draw_circle(bodies[i], circlex, circley);
                ImPlot::PlotLine("ID " + bodies[i].ID, circlex.data(), circley.data(), circlex.size());
                if (bodies[i].tracked){
                    ImPlot::PlotLine("history " + bodies[i].ID, bodies[i].hist.x.data(), bodies[i].hist.y.data(), bodies[i].hist.x.size());
                }
            }
            for (int i = 0; i < legacy.size(); i++){
                ImPlot::SetNextLineStyle(ImVec4(1.0f, 1.0f, 1.0f, 0.17f));
                ImPlot::PlotLine("History Legacy", legacy[i].x.data(), legacy[i].y.data(), legacy[i].x.size());
            }
            ImPlot::EndPlot();
        }


    ImGui::End();
    update();
}