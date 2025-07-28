#include <WindowStream.hpp>
#include "Utillity.hpp"

void WindowStream::loop(){
    HBITMAP bitmap = CaptureWindow(this->hwnd);
    LoadTextureFromHBITMAP(bitmap, this->textureID);
}

WindowStream::WindowStream(HWND hwnd): hwnd(hwnd) {
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
};