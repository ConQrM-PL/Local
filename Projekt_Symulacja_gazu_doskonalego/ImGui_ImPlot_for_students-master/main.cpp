#include "context_setup.h"
#include"Vec2D.h"
#include"particle.h"
#include"gas.h"
#include"wall.h"
#include"systemClass.h"

int main(int, char**)
{
    int N;
    std::cin >> N;
    gas g1 (N, 1);
    for (int i = 0; i < N; i++){
        std::cout << g1.get_particle(i) << "\n";
    }
    std::vector<gas> gases = {g1};

    std::vector<wall> tempcontainer = setup_container();

    systemClass sim(gases, tempcontainer);

    ImGuiContext_OGL context;
    context.setup_and_show();

    while (!glfwWindowShouldClose(context.window))
    {
        context.new_frame();

        sim.set_window();

        context.render_frame();
    }
    return 0;
}
