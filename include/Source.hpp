#include "WindowManager.hpp"
#include <glad/glad.h>
#include <print>
#include <Windows.h>
#include <string>
#include "Utillity.hpp"
#include "WindowStream.hpp"

void buildGUI(GLuint textureID){
    ImGui::NewFrame();
    ImGui::Begin("Helluzz");
    ImGui::Text("Hello");
    ImGui::Image(textureID,ImVec2(480,270));
    ImGui::End();
}