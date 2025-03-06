#include "context_setup.h"
#include "body.h"
#include "Vec2D.h"
#include "systemClass.h"
#include "constants.h"
#include <iostream>
#include <vector>

int main(int, char**)
{
    int n, k;
    std::cin >> n >> k;

    std::vector<int> tracking = generate_random_tracking_targets(n,k);

    systemClass N_Body_Problem(n, DT, tracking);
    for (int i = 0; i < N_Body_Problem.bodies.size(); i++){
        N_Body_Problem.get_first_halfstep_velocity(i);
    }

    ImGuiContext_OGL context;
    context.setup_and_show();

    while (!glfwWindowShouldClose(context.window)){

        context.new_frame();

        N_Body_Problem.set_window();

        context.render_frame();
    }
    return 0;
}