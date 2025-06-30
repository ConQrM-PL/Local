#include"systemClass.h"
#include"constants.h"
#include<cmath>

systemClass::systemClass(std::vector<gas> gas_data, std::vector<wall> wall_data){
    gases = gas_data;
    container = wall_data;
}

void systemClass::solve_collisions(){
    //particle [i] j
    particle temp1(Vec2D(), Vec2D(),0,0);
    particle temp2(Vec2D(), Vec2D(),0,0);
    for (size_t i = 0; i < gases.size(); i++){
        for (size_t j = 0; j < gases[i].get_N(); j++){
            //checking walls
            for (size_t w = 0; w < container.size(); w++){
                temp1 = gases[i].get_particle(j);
                if (check_wall_collision(temp1, container[w])){
                    wall_collision(temp1, container[w]);
                    gases[i].set_particle(temp1, j);
                }
            }
            //checking same gas
            for (size_t k = j+1; k < gases[i].get_N(); k++){
                temp1 = gases[i].get_particle(j);
                temp2 = gases[i].get_particle(k);
                if (check_particle_collision(temp1, temp2, true)){
                    particle_collision(temp1,temp2);
                    gases[i].set_particle(temp1, j);
                    gases[i].set_particle(temp2, k);
                }
            } 
            // checking diff gas
            for (size_t l = i+1; l < gases.size(); l++){
                for (size_t m = 0; m < gases[l].get_N(); m++){
                    temp1 = gases[i].get_particle(j);
                    temp2 = gases[l].get_particle(m);
                    if (check_particle_collision(temp1, temp2, false)){
                        particle_collision(temp1, temp2);
                        gases[i].set_particle(temp1, j);
                        gases[i].set_particle(temp2, m);
                    }
                }
            }
        }
    }
}

void systemClass::simulate_step(){
    for (size_t i = 0; i < gases.size(); i++){
        gases[i].move(dt);
    }
}

void systemClass::update(){
    solve_collisions();
    simulate_step();
}

void systemClass::set_window(){
    ImGui::Begin("Symulacja Gazu");
    
        if (ImPlot::BeginPlot("Simulation", ImVec2(600, 600), ImPlotFlags_NoLegend ) ) {
            ImPlot::SetupAxes("x", "y");
            std::vector<double> wallx, wally;
            for (size_t i = 0; i < container.size(); i++){
                container[i].generate_points_to_draw(wallx, wally);
                ImPlot::PlotLine("sciana", wallx.data(), wally.data(), wallx.size());
            }
            
            for (size_t i = 0; i < gases.size(); i++){
                gases[i].update_points();
                ImPlot::PlotScatter("gaz", gases[i].get_xpoints().data(), gases[i].get_ypoints().data(), gases[i].get_xpoints().size());
            }



            ImPlot::EndPlot();
        }

    ImGui::End();
    update();

}


//////

double distance_to_wall(particle p, wall w){
    double result;
    if (w.check_is_x()){
        result = p.get_position().get_y() - w.value(p.get_position().get_x());
    } else {
        result = p.get_position().get_x() - w.value(p.get_position().get_y());
        
    }
    return fabs(result);
}



bool check_wall_collision(particle p, wall w){
    return (distance_to_wall(p, w) < w.get_thickness() + PARTICLE_THICKNESS);
}

void wall_collision(particle & p, wall w){
    if (w.check_is_x()){
        p.set_velocity(Vec2D(p.get_velocity().get_x(), -p.get_velocity().get_y()));
    } else {
        p.set_velocity(Vec2D(-p.get_velocity().get_x(), p.get_velocity().get_y()));
    }
}

double distance_to_particle(particle p1, particle p2){
    Vec2D d = p1.get_position()-p2.get_position();
    return d.magnitude();
}

bool check_particle_collision(particle p1, particle p2, bool is_same_gas){
    if (is_same_gas && p1.get_ID() == p2.get_ID()) {
        return false;
    }
    return (fabs(distance_to_particle(p1,p2) < 2*PARTICLE_THICKNESS));
}
void particle_collision(particle & p1, particle & p2){
    Vec2D v1 = p1.get_velocity(), v2 = p2.get_velocity();
    double m1 = p1.get_mass(), m2 = p2.get_mass();
    p1.set_velocity((v1*(m1-m2) + v2*(2*m2))*(1/(m1+m2)));
    p2.set_velocity((v2*(m2-m1) + v1*(2*m1))*(1/(m1+m2)));
}