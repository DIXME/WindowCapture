#include <print>
#include "Source.hpp"
#include "WindowManager.hpp"
#include <glad/glad.h>

int main(){
    std::println("Hello, World!");
    WindowManager wm("Hello, World!", 960, 540);
    wm.init();
    while(wm.isOpen()){
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Helluzz");
        ImGui::Text("Hello");
        ImGui::End();
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        wm.renderImGui();
        glfwSwapBuffers(wm.window);
    }
    return 0;
}