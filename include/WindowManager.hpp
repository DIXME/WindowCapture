#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <print>

// single file beacuse this will not have recursive dependencies

class WindowManager {
public:
    GLFWwindow* window;
    int width, height;
    std::string title;
    
    ImGuiIO& getIO(){
        return ImGui::GetIO();
    }

    bool isOpen(){
        return !glfwWindowShouldClose(this->window);
    }

    void terminate(){
        if (this->window) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            glfwDestroyWindow(this->window);
            glfwTerminate();
            this->window = nullptr;
        } else {
            glfwTerminate();
        }
    }

    void currentContext(){
        glfwMakeContextCurrent(this->window);
    }

    bool isCurrentContext(){
        return glfwGetCurrentContext() == this->window;
    }

    void renderImGui(){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool init(){
        if (!glfwInit()){
            std::println("[-] Failed to initialize GLFW");
            return false;
        }
        this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        if (!this->window) {
            std::println("[-] Failed to create GLFW window");
            this->terminate();
            return false;
        }
        this->currentContext();
        ImGui::CreateContext();
        this->getIO();
        ImGui_ImplGlfw_InitForOpenGL(this->window,true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::println("[-] GLAD init error");
            this->terminate();
            return false;
        }
        return true;
    }

    WindowManager(std::string title, int width = 960, int height = 540) : title(title), width(width), height(height){};
    ~WindowManager(){this->terminate();};
};