#include <WindowStream.hpp>
#include "Utillity.hpp"

void WindowStream::loop(){
    LoadTextureFromHBITMAP(CaptureWindow(this->hwnd), this->textureID);
}

WindowStream::WindowStream(HWND hwnd): hwnd(hwnd) {
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
};