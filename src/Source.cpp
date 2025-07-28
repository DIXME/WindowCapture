#include "Source.hpp"

int main(){
    std::println("Hello, World!");
    WindowManager wm("Hello, World!", 960, 540);
    wm.init();
    HWND hwnd = GetDesktopWindow();
    WindowStream ws(hwnd);
    std::println("[+] Window inited");
    while(wm.isOpen()){
        glfwPollEvents();
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ws.loop();
        buildGUI(ws.textureID);
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        wm.renderImGui();
        glfwSwapBuffers(wm.window);
    }
    return 0;
}